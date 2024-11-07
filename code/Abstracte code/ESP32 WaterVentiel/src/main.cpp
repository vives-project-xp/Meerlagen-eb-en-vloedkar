#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN_BUTTON_1 13
#define PIN_BUTTON_2 12
#define PIN_BUTTON_3 14
#define PIN_BUTTON_4 27
#define PIN_BUTTON_5 26

#define PIN_LEDSTRIP 25 // Pin voor LED-strip (NeoPixel)
#define PIN_VALVE_1 33
#define PIN_VALVE_2 32
#define PIN_VALVE_3 23
#define PIN_VALVE_4 22
#define PIN_VALVE_5 21

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN_LEDSTRIP, NEO_GRB + NEO_KHZ800);

unsigned long debounceDelay = 50;
unsigned long valveDelay = 10000; // 10 seconden in milliseconden
unsigned long previousMillis[5] = {0, 0, 0, 0, 0};
int buttonState[5] = {LOW, LOW, LOW, LOW, LOW};
int lastButtonState[5] = {LOW, LOW, LOW, LOW, LOW};
int ledState = 0; // 0 = uit, 1 = rood, 2 = groen

void setup() {
  // Configureer knoppen als ingangen
  for (int i = 0; i < 5; i++) {
    pinMode(PIN_BUTTON_1 + i, INPUT_PULLUP);
  }

  // Configureer ventielen als uitgangen
  for (int i = 0; i < 5; i++) {
    pinMode(PIN_VALVE_1 + i, OUTPUT);
    digitalWrite(PIN_VALVE_1 + i, LOW);  // Alle ventielen dicht
  }

  // LED-strip configureren
  strip.begin();
  strip.show();
}

void loop() {
  // Lees elke knop in een loop
  for (int i = 0; i < 5; i++) {
    int buttonPin = PIN_BUTTON_1 + i;
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

void handleButtonPress(int button) {
  switch (button) {
    case 1:
      openValveForDuration(PIN_VALVE_1, valveDelay);
      break;

    case 2:
      openValveForDuration(PIN_VALVE_5, valveDelay);
      break;

    case 3:
      openValveForDuration(PIN_VALVE_2, valveDelay);
      delay(valveDelay); // Wacht tot ventiel 2 dichtgaat
      openValveForDuration(PIN_VALVE_3, valveDelay);
      openValveForDuration(PIN_VALVE_4, valveDelay);
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

void killSwitch() {
  // Zet alle ventielen uit
  for (int i = 0; i < 5; i++) {
    digitalWrite(PIN_VALVE_1 + i, LOW);
  }
  // Zet de LED-strip uit
  strip.clear();
  strip.show();
  ledState = 0;
}
