// Home assistance, automatisatie testen


#include <Arduino.h>
#include <TimeLib.h>
#include <TimeAlarms.h>
#include "functions.h"
#include "connection.h"
#include "sensor.h"
#include "config.h"

#define PIN_PUMP_VALVE 2

HaConnection connection;

void automaticProcess() {
  // if (!killswitchActive) {
  //   handleButtonPress(1);
  //   handleButtonPress(2);
  //   handleButtonPress(3);
  //   handleButtonPress(4);
  // }
  digitalWrite(PIN_PUMP_VALVE, HIGH);
  delay(1000);
  digitalWrite(PIN_PUMP_VALVE, LOW);
  delay(1000);
}

void setup() {

  //Automatic process
  Serial.begin(115200);
  setupPins();

  // Starts the automatic process at 8:00 and 20:00
  // Alarm.alarmRepeat(8,0, 0, automaticProcess);
  // Alarm.alarmRepeat(20, 0, 0, automaticProcess);  
    Alarm.timerOnce(20, automaticProcess);


  //setupPins();

  // // Connect to the WiFi network
  // connection = HaConnection(WIFI_SSID, WIFI_PASSWORD, 80, true);
  // connection.setup();

  // if (!connection.connected) {
  //   return;
  // }

  // Serial.println("Setup complete");
  // Serial.println("Starting sensor setup");
  
  
  // // Initialize the sensor
  // humSensorUpper = HaSensor("Vochtigheid boven ", SensorType::HUMIDITY);
  // humSensorLower = HaSensor("Vochtigheid beneden ", SensorType::HUMIDITY);

  // connection.setup();
  // Alarm.timerRepeat(5, humidityData);
}

void loop() {
  // Check if the killswitch is active
  // checkKillSwitch();
  // if (!killswitchActive) {
  //   //Alarm.delay(0);
  //   for (int i = 0; i < 5; i++) {
  //     // Read the state of the button
  //     int buttonPin = PIN_INPUT_WATERPUMP + i;
  //     int reading = digitalRead(buttonPin);
  //     if (reading != lastButtonState[i]) {
  //       // reset the debouncing timer
  //       previousMillis[i] = millis();
  //     }
  //     if ((millis() - previousMillis[i]) > debounceDelay) {
  //       if (reading != buttonState[i]) {
  //         // save the reading
  //         buttonState[i] = reading;
  //         if (buttonState[i] == LOW) {
  //           // button is pressed
  //           handleButtonPress(i + 1);
  //         }
  //       }
  //     }
  //     lastButtonState[i] = reading;
  //   }
  // }
  // updateValveCycle();

  // Send the sensor data to Home Assistant
  // int humidityValue = analogRead(PIN_HUMIDITYSENSOR);
  // humSensorUpper.setValue(humidityValue);
  // Serial.print("Humidity: " + String(humidityValue));

  // // humSensorLower.setValue(randomNumber/10);
  // std::vector<HaSensor> sensors = {humSensorUpper, humSensorLower};
  // connection.sendData("Testing Sensor Eb en Vloed", sensors);
  // delay(10000);
    Alarm.delay(100);

}




// LED TEST WERKT NIET

// #include <Arduino.h>
// #include "functions.h"

// void setup() {
//   Serial.begin(115200);
//   setupPins();
//   Alarm.timerRepeat(5, testLed);

// }

// void loop() {
//   Alarm.delay(0); // Non-blocking delay for alarms
//   //testLed();
// }



// Valve test

// #include <Arduino.h>

// #define PIN_PUMP_VALVE 2
// #define PIN_VALVE_INPUT 0
// #define PIN_VALVE_OUTPUT_UPPER 4
// #define PIN_VALVE_OUTPUT_LOWER 16
// #define PIN_VALVE_OUTPUT 17


// void setup() {
//   Serial.begin(115200);
//   //setupPins();
//   pinMode(PIN_PUMP_VALVE, OUTPUT);
//   //Alarm.timerRepeat(5, fullTest);
// }

// void loop() {
//   digitalWrite(PIN_PUMP_VALVE, HIGH);
//   delay(1000);
//   digitalWrite(PIN_PUMP_VALVE, LOW);
//   delay(1000);
  
// }







// Vochtig test

// #include <Arduino.h>
// #include "functions.h"
// #include "connection.h"

// void setup() {
//   Serial.begin(115200);
//   setupPins();
  
//   humSensorUpper = HaSensor("Vochtigheid boven: ", SensorType::HUMIDITY);
//   humSensorLower = HaSensor("Vochtigheid beneden: ", SensorType::HUMIDITY);
// }

// void loop(){
//   checkKillSwitch();
//   updateButtonStates();
// }

