#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


#define PIN_BUTTON_RED 2
// #define PIN_BUTTON_GREEN 1
// #define PIN_BUTTON_YELLOW 2
#define PIN_LEDSTRIP1 4
// #define PIN_LEDSTRIP2 4

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(60, PIN_LEDSTRIP1, NEO_GRB + NEO_KHZ800);
// Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(60, PIN_LEDSTRIP2, NEO_GRB + NEO_KHZ800);

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
int lastButtonState = LOW;
int buttonState;


void setup() {
  pinMode(PIN_BUTTON_RED, INPUT);

  strip1.begin();
  strip1.show();

}

void loop() {

  int reading = digitalRead(PIN_BUTTON_RED);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
    delay(50);
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        strip1.setPixelColor(0, strip1.Color(0, 0, 255,0));
        strip1.show();
      } else {
        strip1.setPixelColor(0, strip1.Color(0, 255, 0,0));
        strip1.show();
      }
    }
  }

}