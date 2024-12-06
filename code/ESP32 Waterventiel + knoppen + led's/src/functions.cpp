// #include "sensor.h"
// #include <Arduino.h>
// #include "functions.h"
// #include <FastLED.h>

// // Define variables
// Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN_LEDSTRIP, NEO_GRB + NEO_KHZ800);
// CRGB leds[NUM_LEDS];
// unsigned long debounceDelay = 50;
// unsigned long valveDelay = 10000;
// unsigned long valve90Seconds = 90000;
// unsigned long previousMillis[5] = {0, 0, 0, 0, 0};
// unsigned long valveTimer = 0;
// unsigned long humidityTimer = 0;
// const unsigned long humidityInterval = 600000;
// bool valve2Active = false;
// bool valve3And4Active = false;
// int buttonState[5] = {LOW, LOW, LOW, LOW, LOW};
// int lastButtonState[5] = {LOW, LOW, LOW, LOW, LOW};
// int ledState = 0;
// bool killswitchActive = false;

// extern HaSensor humSensorUpper("Vochtigheid boven: ", SensorType::HUMIDITY);
// extern HaSensor humSensorLower("Vochtigheid beneden: ", SensorType::HUMIDITY);


// // Sensor objects
// HaSensor humiditySensor("Humidity Sensor", SensorType::HUMIDITY);

// void updateButtonStates() {
//     for (int i = 0; i < 5; i++) {
//         int reading = digitalRead(PIN_INPUT_WATERPUMP + i);
//         if (reading != lastButtonState[i] && millis() - previousMillis[i] > debounceDelay) {
//             previousMillis[i] = millis();
//             lastButtonState[i] = reading;
//             if (reading == HIGH) {
//                 handleButtonPress(i + 1);
//                 logStatus(i + 1); // Log the button press and status
//             }
//         }
//     }
// }




