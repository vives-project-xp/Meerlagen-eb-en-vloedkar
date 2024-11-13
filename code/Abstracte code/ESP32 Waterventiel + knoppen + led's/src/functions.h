#pragma once

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>
#include <TimeAlarms.h>

//define buttons
#define PIN_INPUT_WATERPUMP 13
#define PIN_OUTPUT_WATER 12
#define PIN_INPUT_WATERVALVE 14
#define PIN_LED 27
#define PIN_KILLSWITCH 26

//define LED strip
#define PIN_LEDSTRIP 25 

//define valves
#define PIN_PUMP_VALVE 33
#define PIN_VALVE_INPUT 32
#define PIN_VALVE_OUTPUT_UPPER 23
#define PIN_VALVE_OUTPUT_LOWER 22
#define PIN_VALVE_OUTPUT 21

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