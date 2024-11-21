#include "sensor.h"
#include "functions.h"

// Define variables
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN_LEDSTRIP, NEO_GRB + NEO_KHZ800);
unsigned long debounceDelay = 50;
unsigned long valveDelay = 10000;
unsigned long valve90Seconds = 90000;
unsigned long previousMillis[5] = {0, 0, 0, 0, 0};
unsigned long valveTimer = 0;
unsigned long humidityTimer = 0;
const unsigned long humidityInterval = 600000;
bool valve2Active = false;
bool valve3And4Active = false;
int buttonState[5] = {LOW, LOW, LOW, LOW, LOW};
int lastButtonState[5] = {LOW, LOW, LOW, LOW, LOW};
int ledState = 0;
bool killswitchActive = false;

extern HaSensor humSensorUpper("Vochtigheid boven: ", SensorType::HUMIDITY);
extern HaSensor humSensorLower("Vochtigheid beneden: ", SensorType::HUMIDITY);

void setupPins() {
    // Set the pins for the buttons
  for (int i = 0; i < 5; i++) {
    pinMode(PIN_INPUT_WATERPUMP + i, INPUT_PULLUP);
  }  //klopt niet meer???
  for (int i = 0; i < 5; i++) {
    pinMode(PIN_PUMP_VALVE + i, OUTPUT);
    digitalWrite(PIN_PUMP_VALVE + i, LOW);
  }

  pinMode(PIN_LEDSTRIP, OUTPUT);

  pinMode(PIN_LEDSTRIP, OUTPUT);
  pinMode(PIN_VALVE_INPUT, OUTPUT);
  pinMode(PIN_VALVE_OUTPUT_UPPER, OUTPUT);
  pinMode(PIN_VALVE_OUTPUT_LOWER, OUTPUT);
  pinMode(PIN_VALVE_OUTPUT, OUTPUT);
  pinMode(PIN_PUMP, OUTPUT);

  strip.begin();
  strip.show();
}

void updateButtonStates() {
    for (int i = 0; i < 5; i++) {
        int reading = digitalRead(PIN_INPUT_WATERPUMP + i);
        if (reading != lastButtonState[i] && millis() - previousMillis[i] > debounceDelay) {
            previousMillis[i] = millis();
            lastButtonState[i] = reading;
            if (reading == HIGH) {
                handleButtonPress(i + 1);
                logStatus(i + 1); // Log the button press and status
            }
        }
    }
}

void logStatus(int button) {
    switch (button) {
        case 1:
            Serial.println("Status: Pump Valve Opened");
            // std::cout("status: pump valve opened"); //????
            break;
        case 2:
            Serial.println("Status: Output Valve Opened");
            break;
        case 3:
            Serial.println("Status: Input Valve Opened");
            break;
        case 4:
            Serial.println("Status: LED Strip Toggled");
            break;
        case 5:
            Serial.println("Status: Killswitch Activated");
            break;
    }
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
      controlWaterPump(true, 10000);
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
      Serial.println("LED strip ON");
      break;
    case 1:
    // Clear the LED strip
      strip.clear();
      ledState = 0;
      Serial.println("LED strip OFF");
      break;
  }
  strip.show();
}

// Check if the killswitch is active
void checkKillSwitch() {
  int switchState = digitalRead(PIN_KILLSWITCH);
  if (switchState == HIGH && !killswitchActive) {
    killswitchActive = true;
    Serial.println("Killswitch activated");
  } else if (switchState == LOW && killswitchActive) {
    killswitchActive = false;
    Serial.println("Killswitch deactivated");
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
    digitalWrite(PIN_VALVE_OUTPUT_UPPER, LOW);
    digitalWrite(PIN_VALVE_OUTPUT_LOWER, LOW);
    valve3And4Active = false;
  }
}

// Automatic process
// void automaticProcess() {
//   // if (!killswitchActive) {
//   //   handleButtonPress(1);
//   //   handleButtonPress(2);
//   //   handleButtonPress(3);
//   //   handleButtonPress(4);
//   // }
//   digitalWrite(PIN_PUMP_VALVE, HIGH);
//   delay(1000);
//   digitalWrite(PIN_PUMP_VALVE, LOW);
//   delay(1000);
// }

void humidityData(){
  int humidityValue = analogRead(PIN_HUMIDITYSENSOR);
  Serial.print("Humidity: ");
  Serial.println(humidityValue);
}


// Control water pump state (on or off)
void controlWaterPump(bool state, unsigned long duration) {
    if (state) {
        digitalWrite(PIN_PUMP, HIGH);    // Turn on the pump
        Serial.println("Pump on");
        delay(duration);                 // Keep it on for the specified duration
        Serial.println("Pump off");
        digitalWrite(PIN_PUMP, LOW);     // Turn off the pump after the duration
    } else {
        digitalWrite(PIN_PUMP, LOW);     // Immediately turn off the pump if state is false
    }
}

void testLed(){
  digitalWrite(PIN_LEDSTRIP, HIGH);
  strip.fill(strip.Color(255, 0, 0), 0, 60);
  strip.show();
  Serial.println("LED strip on");
  delay(2000);
  digitalWrite(PIN_LEDSTRIP, LOW);
  strip.clear();
  strip.show();
  Serial.println("LED strip off");
}
