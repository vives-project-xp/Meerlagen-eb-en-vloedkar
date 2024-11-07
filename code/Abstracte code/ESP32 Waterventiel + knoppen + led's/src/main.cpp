#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>
#include <TimeAlarms.h>

#define PIN_INPUT_WATERPUMP 13
#define PIN_OUTPUT_WATER 12
#define PIN_INPUT_WATERVALVE 14
#define PIN_LED 27
#define PIN_KILLSWITCH 26

#define PIN_LEDSTRIP 25 // Pin voor LED-strip (NeoPixel)
#define PIN_PUMP_VALVE 33
#define PIN_VALVE_INPUT 32
#define PIN_VALVE_OUTPUT_UPPER 23
#define PIN_VALVE_OUTPUT_LOWER 22
#define PIN_VALVE_OUTPUT 21

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN_LEDSTRIP, NEO_GRB + NEO_KHZ800);

unsigned long debounceDelay = 50;
unsigned long valveDelay = 10000; // 10 seconden in milliseconden
unsigned long valve90Seconds = 90000; // 90 seconden in milliseconden
unsigned long previousMillis[5] = {0, 0, 0, 0, 0};
unsigned long valveTimer = 0;
bool valve2Active = false;
bool valve3And4Active = false;
int buttonState[5] = {LOW, LOW, LOW, LOW, LOW};
int lastButtonState[5] = {LOW, LOW, LOW, LOW, LOW};
int ledState = 0; // 0 = uit, 1 = rood, 2 = groen
bool killswitchActive = false;

void setup() {

  Serial.begin(115200);
  setTime(8, 0, 0, 1, 11, 2024); 

  Alarm.alarmRepeat(8, 0, 0, automaticProcess);
  Alarm.alarmRepeat(20, 0, 0, automaticProcess);  

  // Configureer knoppen als ingangen
  for (int i = 0; i < 5; i++) {
    pinMode(PIN_INPUT_WATERPUMP + i, INPUT_PULLUP);
  }

  // Configureer ventielen als uitgangen
  for (int i = 0; i < 5; i++) {
    pinMode(PIN_PUMP_VALVE + i, OUTPUT);
    digitalWrite(PIN_PUMP_VALVE + i, LOW);  // Alle ventielen dicht
  }

  // LED-strip configureren
  strip.begin();
  strip.show();
}

void loop() {
  checkKillSwitch();
  if (!killswitchActive) {
    Alarm.delay(0);
  for (int i = 0; i < 5; i++) {
    int buttonPin = PIN_INPUT_WATERPUMP + i;
    int reading = digitalRead(buttonPin);

    // Debounce de knop
    if (reading != lastButtonState[i]) {
      previousMillis[i] = millis();
    }
    if ((millis() - previousMillis[i]) > debounceDelay) {
      if (reading != buttonState[i]) {
        buttonState[i] = reading;
        if (buttonState[i] == LOW) { // LOW betekent ingedrukt vanwege INPUT_PULLUP
          handleButtonPress(i + 1);
        }
      }
    }
    lastButtonState[i] = reading;
  }
  }
  updateValveCycle();
}

void handleButtonPress(int button) {
  if (killswitchActive) {
    return;
  }
  switch (button) {
    case 1:
      openValveForDuration(PIN_PUMP_VALVE, valveDelay);
      break;

    case 2:
      openValveForDuration(PIN_VALVE_OUTPUT, valveDelay);
      break;

    case 3:
      valveTimer = millis();
      valve2Active = true;
      digitalWrite(PIN_VALVE_INPUT, HIGH);
      break;

    case 4:
      toggleLEDStrip();
      break;

    case 5:
      killSwitch();
      break;
  }
}

void openValveForDuration(int valvePin, unsigned long duration) {
  digitalWrite(valvePin, HIGH);
  delay(duration);
  digitalWrite(valvePin, LOW);
}

void toggleLEDStrip() {
  switch (ledState) {
    case 0:  // Zet LED-strip rood
      strip.fill(strip.Color(255, 0, 0), 0, strip.numPixels());
      ledState = 1;
      break;
    case 1:  // Zet LED-strip groen
      strip.fill(strip.Color(0, 255, 0), 0, strip.numPixels());
      ledState = 2;
      break;
    case 2:  // Zet LED-strip uit
      strip.clear();
      ledState = 0;
      break;
  }
  strip.show();
}

void checkKillSwitch(){
  int switchState = digitalRead(PIN_KILLSWITCH);
  if (switchState == HIGH && !killswitchActive){
    killswitchActive = true;
  } else if (switchState == LOW && killswitchActive){
    killswitchActive = false;
  }
}

void killSwitch() {
  // Zet alle ventielen uit
  for (int i = 0; i < 5; i++) {
    digitalWrite(PIN_PUMP_VALVE + i, LOW);
  }
  // Zet de LED-strip uit
  strip.clear();
  strip.show();
  ledState = 0;
}

void updateValveCycle() {
  if (valve2Active && millis() - valveTimer >= valve90Seconds) {
    digitalWrite(PIN_VALVE_INPUT, LOW);
    valve2Active = false;
    valveTimer = millis();
    valve3And4Active = true;

    digitalWrite(PIN_VALVE_OUTPUT_UPPER, HIGH);
    digitalWrite(PIN_VALVE_OUTPUT_LOWER, HIGH);
  }
  if (valve3And4Active && millis() - valveTimer > valve90Seconds) {
    digitalWrite(PIN_VALVE_OUTPUT_UPPER, HIGH);
    digitalWrite(PIN_VALVE_OUTPUT_LOWER, LOW);
    valve3And4Active = false;
  }
}

void automaticProcess(){
  if(!killswitchActive){
    handleButtonPress(1);
    handleButtonPress(2);
    handleButtonPress(3);
    handleButtonPress(4);
  }
}

