#include "functions.h"

// Define variables
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN_LEDSTRIP, NEO_GRB + NEO_KHZ800);
unsigned long debounceDelay = 50;
unsigned long valveDelay = 10000;
unsigned long valve90Seconds = 90000;
unsigned long previousMillis[5] = {0, 0, 0, 0, 0};
unsigned long valveTimer = 0;
bool valve2Active = false;
bool valve3And4Active = false;
int buttonState[5] = {LOW, LOW, LOW, LOW, LOW};
int lastButtonState[5] = {LOW, LOW, LOW, LOW, LOW};
int ledState = 0;
bool killswitchActive = false;

void setupPins() {
    // Set the pins for the buttons
  for (int i = 0; i < 5; i++) {
    pinMode(PIN_INPUT_WATERPUMP + i, INPUT_PULLUP);
  }
  for (int i = 0; i < 5; i++) {
    pinMode(PIN_PUMP_VALVE + i, OUTPUT);
    digitalWrite(PIN_PUMP_VALVE + i, LOW);
  }
  strip.begin();
  strip.show();
}

void handleButtonPress(int button) {
  if (killswitchActive) {
    return;
  }
  switch (button) {
    case 1:
    // Open the pump valve for 10 seconds
      openValveForDuration(PIN_PUMP_VALVE, valveDelay);
      break;
    case 2:
    // Open the output valve for 10 seconds
      openValveForDuration(PIN_VALVE_OUTPUT, valveDelay);
      break;
    case 3:
    // Open the input valve for 10 seconds
      valveTimer = millis();
      valve2Active = true;
      digitalWrite(PIN_VALVE_INPUT, HIGH);
      break;
    case 4:
    // Toggle the LED strip
      toggleLEDStrip();
      break;
    case 5:
    // Kills all processes
      killSwitch();
      break;
  }
}

void openValveForDuration(int valvePin, unsigned long duration) {
  digitalWrite(valvePin, HIGH);
  delay(duration);
  digitalWrite(valvePin, LOW);
}

// Moet nog aangepast worden
void toggleLEDStrip() {
  switch (ledState) {
    case 0:
    // Set the LED strip to red
      strip.fill(strip.Color(255, 0, 0), 0, strip.numPixels());
      ledState = 1;
      break;
    case 1:
    // Set the LED strip to green
      strip.fill(strip.Color(0, 255, 0), 0, strip.numPixels());
      ledState = 2;
      break;
    case 2:
    // Clear the LED strip
      strip.clear();
      ledState = 0;
      break;
  }
  strip.show();
}

// Check if the killswitch is active
void checkKillSwitch() {
  int switchState = digitalRead(PIN_KILLSWITCH);
  if (switchState == HIGH && !killswitchActive) {
    killswitchActive = true;
  } else if (switchState == LOW && killswitchActive) {
    killswitchActive = false;
  }
}

void killSwitch() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(PIN_PUMP_VALVE + i, LOW);
  }
  strip.clear();
  strip.show();
  ledState = 0;
}

void updateValveCycle() {
  if (valve2Active && millis() - valveTimer >= valve90Seconds) {
    // Close the input valve and open the output valve
    digitalWrite(PIN_VALVE_INPUT, LOW);
    valve2Active = false;
    valveTimer = millis();
    valve3And4Active = true;
    digitalWrite(PIN_VALVE_OUTPUT_UPPER, HIGH);
    digitalWrite(PIN_VALVE_OUTPUT_LOWER, HIGH);
  }
  if (valve3And4Active && millis() - valveTimer > valve90Seconds) {
    // Close the output lower valve and open the upper valve
    digitalWrite(PIN_VALVE_OUTPUT_UPPER, HIGH); //Klopt dit??
    digitalWrite(PIN_VALVE_OUTPUT_LOWER, LOW);
    valve3And4Active = false;
  }
}

// Automatic process
void automaticProcess() {
  if (!killswitchActive) {
    handleButtonPress(1);
    handleButtonPress(2);
    handleButtonPress(3);
    handleButtonPress(4);
  }
}

// Control water pump state (on or off)
void controlWaterPump(bool state) {
    digitalWrite(PIN_PUMP, state ? HIGH : LOW);
}

void readAndSendHumidity() {
  int humidityValue = analogRead(PIN_HUMIDITYSENSOR);
  Serial.print("Humidity: ");
  Serial.println(humidityValue);

  // Set the LED strip to red for indication
  strip.fill(strip.Color(255, 0, 0), 0, strip.numPixels());
  strip.show();
}