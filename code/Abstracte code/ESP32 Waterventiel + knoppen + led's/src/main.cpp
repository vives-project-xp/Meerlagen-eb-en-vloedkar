// works for LED

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "functions.h"
#include "connection.h"
#include "sensor.h"

// Define variables
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

// DONT TOUCH CODE BELOW
void ledsToColor()
{
  digitalWrite(PIN_LEDSTRIP, HIGH);
  for (int i = 0; i < NUM_LEDS; i++)
  {
    if (i % 4 == 0)
    {
      strip.setPixelColor(i, strip.Color(100, 30, 25));
      strip.show();
    }
    else if (i % 4 == 1)
    {
      strip.setPixelColor(i, strip.Color(30, 25, 100));
      strip.show();
    }
    else if (i % 4 == 3)
    {
      strip.setPixelColor(i, strip.Color(25, 100, 30));
      strip.show();
    }
    else
    {
      strip.setPixelColor(i, strip.Color(100, 30, 25));
      strip.show();
    }
  }
}

// WERKT NIET AANKOMEN
void humidityData()
{
  int humidityValueUpper = analogRead(PIN_HUMIDITYSENSOR_UPPER);
  int humidityValueLower = analogRead(PIN_HUMIDITYSENSOR_LOWER);
  Serial.print("Humidity upper: ");
  humidityValueUpper = humidityValueConverter(humidityValueUpper);
  Serial.println(humidityValueUpper);
  Serial.print("Humidity lower: ");
  humidityValueLower = humidityValueConverter(humidityValueLower);
  Serial.println(humidityValueLower);
  delay(10000);
}

// WERKT NIET AANKOMEN
int humidityValueConverter(int rawValue)
{
  int percentage = map(rawValue, 1500, 3900, 100, 0);
  percentage = constrain(percentage, 0, 100);
  return percentage;
}

// TESTEN
void openValveForDuration(int valvePin, unsigned long duration)
{
  digitalWrite(valvePin, HIGH);
  delay(duration);
  digitalWrite(valvePin, LOW);
}

// TESTEN
void openDoubleValveForDuration(int valvePin1, int valvePin2, unsigned long duration)
{
  digitalWrite(valvePin1, HIGH);
  digitalWrite(valvePin2, HIGH);
  delay(duration);
  digitalWrite(valvePin1, LOW);
  digitalWrite(valvePin2, LOW);
}

// TESTEN
void handleButtonPress(int button)
{
  if (killswitchActive)
  {
    return;
  }
  switch (button)
  {
  case 1:
    // Water in de tank
    Serial.println("Pump valve opened");
    openValveForDuration(PIN_PUMP_VALVE, valveDelay);
    Serial.println("Pump valve closed");
    break;
  case 2:
    // Water naar de bakken
    Serial.println("Output valve opened");
    controlWaterPump(pumpDelay);
    Serial.println("Output valve closed");
    break;
  case 3:
    // Water uit bakken
    Serial.println("Output valves opened");
    openDoubleValveForDuration(PIN_VALVE_OUTPUT_UPPER, PIN_VALVE_OUTPUT_LOWER, valveDelay);
    Serial.println("Output valves closed");
  case 4:
    // OUTPUT VENTIEL 5
    openValveForDuration(PIN_VALVE_OUTPUT, valveDelay);
    Serial.println("Input valve opened");
    break;
  case 5:
    // Toggle the LED strip
    ledsToColor();
    Serial.println("LED strip toggled");
    break;
  case 6:
    // Kills all processes
    killSwitch();
    Serial.println("Killswitch activated");
    break;
  }
}

// CHECKEN
void checkKillSwitch()
{
  int switchState = digitalRead(PIN_KILLSWITCH);
  if (switchState == HIGH && !killswitchActive)
  {
    killswitchActive = true;
    Serial.println("Killswitch activated");
  }
  else if (switchState == LOW && killswitchActive)
  {
    killswitchActive = false;
    Serial.println("Killswitch deactivated");
  }
}
// CHECKEN

void killSwitch()
{
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(valvePins[i], LOW);
  }
  strip.clear();
  strip.show();
}

// CHECKEN

void setupPins()
{
  for (int i = 0; i < 6; i++)
  {
    pinMode(buttonPins[i], INPUT);
    digitalWrite(buttonPins[i], LOW);
  }
  for (int i = 0; i < 5; i++)
  {
    pinMode(valvePins[i], OUTPUT);
    digitalWrite(valvePins[i], LOW);
  }

  pinMode(PIN_LEDSTRIP, OUTPUT);
  digitalWrite(PIN_LEDSTRIP, LOW);

  pinMode(PIN_HUMIDITYSENSOR_UPPER, INPUT);
  pinMode(PIN_HUMIDITYSENSOR_LOWER, INPUT);
  strip.begin();
  strip.show();
}

// TESTEN
void controlWaterPump(unsigned long duration)
{
  digitalWrite(PIN_PUMP, HIGH); 
  Serial.println("Pump on & Valve open");
  digitalWrite(PIN_VALVE_OUTPUT, HIGH);
  delay(duration);
  Serial.println("Valve closed");
  digitalWrite(PIN_VALVE_OUTPUT, LOW);
  delay(duration);
  digitalWrite(PIN_PUMP, LOW);
  Serial.println("Pump off");
}
// TESTEN

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting setup...");

  setTime(8,0,0,1,11,2024);

  Alarm.alarmRepeat(8, 0, 0, automaticProcess);
  Alarm.alarmRepeat(20, 0, 0, automaticProcess);  
  setupPins();
}
// TESTEN

void loop()
{
  checkKillSwitch();
  if(!killswitchActive){
    Alarm.delay(0);
    for (int i = 0; i < 6; i++) {
      int reading = digitalRead(buttonPins[i]);
      if (reading != lastButtonState[i]) {
      previousMillis[i] = millis();
    }
    if ((millis() - previousMillis[i]) > debounceDelay) {
      if (reading != buttonState[i]) {
        buttonState[i] = reading;
        if (buttonState[i] == LOW) {
          handleButtonPress(i + 1);
        }
      }
    }
    lastButtonState[i] = reading;
  }
    }
  humidityData();
}

// CHECKEN

// // Automatic process
// // void automaticProcess() {
// //   // if (!killswitchActive) {
// //   //   handleButtonPress(1);
// //   //   handleButtonPress(2);
// //   //   handleButtonPress(3);
// //   //   handleButtonPress(4);
// //   // }
// //   digitalWrite(PIN_PUMP_VALVE, HIGH);
// //   delay(1000);
// //   digitalWrite(PIN_PUMP_VALVE, LOW);
// //   delay(1000);
// // }
