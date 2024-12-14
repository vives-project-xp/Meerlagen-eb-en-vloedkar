#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "functions.h"
#include "connection.h"
#include "sensor.h"
#include "config.h"

// Global variable definitions
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN_LEDSTRIP, NEO_GRB + NEO_KHZ800);
unsigned long debounceDelay = 50;
unsigned long pumpDelay = 5000;
unsigned long valveDelay = 10000;
unsigned long valve90Seconds = 90000;
unsigned long previousMillis[5] = {0, 0, 0, 0, 0};
unsigned long valveTimer = 0;
unsigned long humidityTimer = 0;
const unsigned long humidityInterval = 600000;
bool valve2Active = false;
bool valve3And4Active = false;
int buttonState[5] = {LOW, LOW, LOW, LOW, LOW};
int lastButtonState[5] = {LOW, LOW, LOW, LOW, LOW};
bool killswitchActive = false;
const int valvePins[5] = {PIN_PUMP_VALVE, PIN_VALVE_INPUT, PIN_VALVE_OUTPUT_UPPER, PIN_VALVE_OUTPUT_LOWER, PIN_VALVE_OUTPUT};
const int buttonPins[6] = {PIN_INPUT_WATERTANK, PIN_INPUT_WATERPUMP, PIN_OUTPUT_WATER, PIN_OUTPUT_WATERTANK, PIN_LED, PIN_KILLSWITCH};

extern HaSensor humSensorUpper("Vochtigheid boven: ", SensorType::HUMIDITY);
extern HaSensor humSensorLower("Vochtigheid beneden: ", SensorType::HUMIDITY);

HaConnection connection;

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting setup...");

  setupPins();
  Alarm.alarmRepeat(8, 0, 0, automaticProcess);
  Alarm.alarmRepeat(20, 0, 0, automaticProcess);

  connection = HaConnection(WIFI_SSID, WIFI_PASSWORD, 80, true);
  connection.setup();

  if (!connection.connected)
  {
    return;
  }

  Serial.println("Setup complete");
  Serial.println("Starting sensor setup");

  humSensorUpper = HaSensor("Vochtigheid boven: ", SensorType::HUMIDITY);
  humSensorLower = HaSensor("Vochtigheid beneden: ", SensorType::HUMIDITY);

  connection.setup();
}

void loop()
{
  checkKillSwitch();
  if (!killswitchActive)
  {
    Alarm.delay(0);
    for (int i = 0; i < 6; i++)
    {
      int reading = digitalRead(buttonPins[i]);
      if (reading != lastButtonState[i])
      {
        previousMillis[i] = millis();
      }
      if ((millis() - previousMillis[i]) > debounceDelay)
      {
        if (reading != buttonState[i])
        {
          buttonState[i] = reading;
          if (buttonState[i] == LOW)
          {
            handleButtonPress(i + 1);
          }
        }
      }
      lastButtonState[i] = reading;
    }
  }
  humidityData();
}
