// #include <Arduino.h>
// #include "functions.h"
// #include "connection.h"
// #include "sensor.h"

// #define WIFI_SSID "SSID"
// #define WIFI_PASSWORD "PASSWORD"

// HaSensor sensor;
// HaConnection connection;

// void setup() {

//   //Automatic process
//   Serial.begin(115200);
//   setTime(8, 0, 0, 1, 11, 2024); 

//   // Starts the automatic process at 8:00 and 20:00
//   Alarm.alarmRepeat(8, 0, 0, automaticProcess);
//   Alarm.alarmRepeat(20, 0, 0, automaticProcess);  

//   setupPins();

//   // Connect to the WiFi network
//   connection = HaConnection(WIFI_SSID, WIFI_PASSWORD);

//   if (!connection.connected) {
//     return;
//   }

//   // Serial.println("Setup complete");
//   // Serial.println("Starting sensor setup");
  
//   // Initialize the sensor
//   sensor = HaSensor(SensorType::HUMIDITY);

//   Alarm.timerRepeat(10, humidityData);
// }

// void loop() {
//   // Check if the killswitch is active
//   checkKillSwitch();
//   if (!killswitchActive) {
//     //Alarm.delay(0);
//     for (int i = 0; i < 5; i++) {
//       // Read the state of the button
//       int buttonPin = PIN_INPUT_WATERPUMP + i;
//       int reading = digitalRead(buttonPin);
//       if (reading != lastButtonState[i]) {
//         // reset the debouncing timer
//         previousMillis[i] = millis();
//       }
//       if ((millis() - previousMillis[i]) > debounceDelay) {
//         if (reading != buttonState[i]) {
//           // save the reading
//           buttonState[i] = reading;
//           if (buttonState[i] == LOW) {
//             // button is pressed
//             handleButtonPress(i + 1);
//           }
//         }
//       }
//       lastButtonState[i] = reading;
//     }
//   }
//   updateValveCycle();

//   // Send the sensor data to Home Assistant
//   // connection.sendData(sensor);
//   // delay(5000);
// }

// // Connection data van in en uit

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
#include "functions.h"

void setup() {
  Serial.begin(115200);

  // Initialize the LED strip
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  // Set up a timer to read and send humidity data every 10 seconds
  Alarm.timerRepeat(10, readAndSendHumidity);
}

void loop() {
  Alarm.delay(0); // Non-blocking delay for alarms
}