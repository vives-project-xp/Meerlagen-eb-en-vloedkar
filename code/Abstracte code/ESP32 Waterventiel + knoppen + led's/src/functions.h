#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>
#include <TimeAlarms.h>

//define buttons
#define PIN_INPUT_WATERPUMP 34
#define PIN_OUTPUT_WATER 32
#define PIN_INPUT_WATERVALVE 35
#define PIN_LED 33
#define PIN_KILLSWITCH 39

//define LED strip
#define PIN_LEDSTRIP 23 

//define valves
#define PIN_PUMP_VALVE 2
#define PIN_VALVE_INPUT 15
#define PIN_VALVE_OUTPUT_UPPER 8
#define PIN_VALVE_OUTPUT_LOWER 7
#define PIN_VALVE_OUTPUT 6

//define pump
#define PIN_PUMP 0

//define humiditysensor
#define PIN_HUMIDITYSENSOR 36

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
void readAndSendHumidity();