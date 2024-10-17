#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN_BUTTON_RED 2
#define PIN_LEDSTRIP1 4

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(60, PIN_LEDSTRIP1, NEO_GRB + NEO_KHZ800);

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int lastButtonState = LOW;
int buttonState;
int currentState = 0; // 0 = off, 1 = red, 2 = blue

void setup() {
  pinMode(PIN_BUTTON_RED, INPUT);
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
        // Cycle through states: off -> red -> blue -> off
        currentState++;
        if (currentState > 2) {
          currentState = 0;
        }
        
        if (currentState == 0) {
          // Turn off the LED
          strip1.setPixelColor(0, strip1.Color(0, 0, 0));
        } else if (currentState == 1) {
          // Set LED to red
          strip1.setPixelColor(0, strip1.Color(255, 0, 0));
        } else if (currentState == 2) {
          // Set LED to blue
          strip1.setPixelColor(0, strip1.Color(0, 0, 255));
        }
        
        strip1.show();
      }
    }
  }

  lastButtonState = reading;
}
