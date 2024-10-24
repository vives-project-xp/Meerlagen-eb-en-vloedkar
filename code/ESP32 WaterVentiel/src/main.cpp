#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN_BUTTON_RED 2
#define PIN_LEDSTRIP1 4
#define PIN_WATER_VALVE 5 // Pin to control water valve (via relay)

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(60, PIN_LEDSTRIP1, NEO_GRB + NEO_KHZ800);

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int lastButtonState = LOW;
int buttonState;

void setup() {
  pinMode(PIN_BUTTON_RED, INPUT);
  pinMode(PIN_WATER_VALVE, OUTPUT);  // Set water valve pin as output
  digitalWrite(PIN_WATER_VALVE, LOW);  // Initially, water valve is closed (LOW)

  strip1.begin();
  strip1.show();
}

void loop() {
  int reading = digitalRead(PIN_BUTTON_RED);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
<<<<<<< HEAD:code/ESP32 Button_LED 2/src/main.cpp
        // Cycle through states: off -> red -> blue -> off
        Serial.println("Button pressed");
        currentState++;
        if (currentState > 1) {
          currentState = 0;
        }
        
        if (currentState == 0) {
          // Turn off the LED
          strip1.setPixelColor(0, strip1.Color(0, 0, 0));
        } else if (currentState == 1) {
          // Set LED to red
          strip1.setPixelColor(0, strip1.Color(100, 30, 25));
        } 
        
=======
        // Turn on the LED and open the water valve
        strip1.setPixelColor(0, strip1.Color(255, 0, 0)); // Red LED on
>>>>>>> 9a2a968f4f2fc149e4e10f2a2459a635ae42a128:code/ESP32 WaterVentiel/src/main.cpp
        strip1.show();
        digitalWrite(PIN_WATER_VALVE, HIGH);  // Open water valve
      } else {
        // Turn off the LED and close the water valve
        strip1.setPixelColor(0, strip1.Color(0, 0, 0)); // LED off
        strip1.show();
        digitalWrite(PIN_WATER_VALVE, LOW);  // Close water valve
      }
    }
  }

  lastButtonState = reading;
}
