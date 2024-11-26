// works for LED

#include <Arduino.h>
#include <FastLED.h>

// Define pins
#define PIN_LEDSTRIP 23
#define NUM_LEDS 180

// Define variables
CRGB leds[NUM_LEDS];
unsigned long previousMillis = 0;
const long interval = 2000; // Interval for each color (2 seconds)
int state = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting setup...");

  // Initialize the LED strip
  FastLED.addLeds<NEOPIXEL, PIN_LEDSTRIP>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
  Serial.println("LED strip initialized");

    for (int i = 0; i < NUM_LEDS; i++) {
      if (i % 4 == 0) {
        leds[i] = CRGB::Red;
        FastLED.show();
        Serial.println("LED strip set to red");
      } else if (i % 4 == 1) {
        leds[i] = CRGB::Blue;
        FastLED.show();
        Serial.println("LED strip set to blue");
      } else if (i % 4 == 3) {
        leds[i] = CRGB::Green;
        FastLED.show();
        Serial.println("LED strip set to green");
      } else{}
    }
  
}

void loop() {
}