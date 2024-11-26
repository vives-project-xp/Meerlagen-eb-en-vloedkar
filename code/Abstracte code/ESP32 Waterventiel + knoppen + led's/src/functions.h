// #pragma once

// #include <Arduino.h>
// #include <Adafruit_NeoPixel.h>
// #include <TimeLib.h>
// #include <TimeAlarms.h>
// #include <FastLED.h>
// #include "sensor.h"

// //define buttons
// #define PIN_INPUT_WATERPUMP 34
// #define PIN_OUTPUT_WATER 32
// #define PIN_INPUT_WATERVALVE 35
// #define PIN_LED 33
// #define PIN_KILLSWITCH 39

// //define LED strip
// #define PIN_LEDSTRIP 22 
// //test
// #define NUM_LEDS 60

// //define valves
// #define PIN_PUMP_VALVE 2
// #define PIN_VALVE_INPUT 0
// #define PIN_VALVE_OUTPUT_UPPER 4
// #define PIN_VALVE_OUTPUT_LOWER 16
// #define PIN_VALVE_OUTPUT 17

// //define pump
// #define PIN_PUMP 15

// //define humiditysensor
// #define PIN_HUMIDITYSENSOR_UPPER 36 
// #define PIN_HUMIDITYSENSOR_LOWER  

// // Define variables
// extern Adafruit_NeoPixel strip;
// //test
// extern CRGB leds[NUM_LEDS];

// extern unsigned long debounceDelay;
// extern unsigned long valveDelay;
// extern unsigned long valve90Seconds;
// extern unsigned long previousMillis[5];
// extern unsigned long valveTimer;
// extern bool valve2Active;
// extern bool valve3And4Active;
// extern int buttonState[5];
// extern int lastButtonState[5];
// extern int ledState;
// extern bool killswitchActive;
// extern HaSensor humSensorUpper;
// extern HaSensor humSensorLower;

// // Function prototypes
// void setupPins();
// void handleButtonPress(int button);
// void openValveForDuration(int valvePin, unsigned long duration);
// void toggleLEDStrip();
// void checkKillSwitch();
// void killSwitch();
// void updateValveCycle();
// void automaticProcess();
// void humidityData();
// void sendHumidityData();
// void testthingy();
// void controlWaterPump(bool state, unsigned long duration);
// void testLed(); 
// void fullTest();
// void logStatus(int button);
// void updateButtonStates();
// void testWLED();
// int humidityValueConverter(int rawValue);