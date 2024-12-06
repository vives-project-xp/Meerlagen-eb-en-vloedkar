#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
#include "sensor.h"

//define buttons
#define PIN_INPUT_WATERTANK 36
#define PIN_INPUT_WATERPUMP 34
#define PIN_OUTPUT_WATER 32
#define PIN_OUTPUT_WATERTANK 35
#define PIN_LED 33
#define PIN_KILLSWITCH 39

//define LED strip
#define PIN_LEDSTRIP 23 
#define NUM_LEDS 220

//define valves
#define PIN_PUMP_VALVE 2
#define PIN_VALVE_INPUT 4
#define PIN_VALVE_OUTPUT_UPPER 16
#define PIN_VALVE_OUTPUT_LOWER 17
#define PIN_VALVE_OUTPUT 5

//define pump
#define PIN_PUMP 15

//define humiditysensor
#define PIN_HUMIDITYSENSOR_UPPER 25 
#define PIN_HUMIDITYSENSOR_LOWER 26

// Define variables
extern Adafruit_NeoPixel strip;
extern unsigned long debounceDelay;
extern unsigned long valveDelay;
extern unsigned long valve90Seconds;
extern unsigned long previousMillis[5];
extern unsigned long valveTimer;
extern bool valve2Active;
extern bool valve3And4Active;
extern int buttonState[5];
extern int lastButtonState[5];
extern int ledState;
extern bool killswitchActive;
extern HaSensor humSensorUpper;
extern HaSensor humSensorLower;
extern const int valvePins[5];
extern const int buttonPins[6];

// Function prototypes
void setupPins();
void handleButtonPress(int button);
void openValveForDuration(int valvePin, unsigned long duration);
void toggleLEDStrip();
void checkKillSwitch();
void killSwitch();
void updateValveCycle();
void automaticProcess();
void humidityData();
void sendHumidityData();
void controlWaterPump(unsigned long duration);
void testLed(); 
void fullTest();
void logStatus(int button);
void updateButtonStates();
void testWLED();
int humidityValueConverter(int rawValue);