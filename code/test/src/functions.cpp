#include "functions.h"
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "sensor.h"
#include "connection.h"
#include "config.h"

extern Adafruit_NeoPixel strip;
extern HaConnection connection;
extern HaSensor humSensorUpper;
extern HaSensor humSensorLower;

void ledsToColor()
{
    digitalWrite(PIN_LEDSTRIP, HIGH);
    for (int i = 0; i < NUM_LEDS; i++)
    {
        if (i % 4 == 0)
        {
            strip.setPixelColor(i, strip.Color(100, 30, 25));
        }
        else if (i % 4 == 1)
        {
            strip.setPixelColor(i, strip.Color(30, 25, 100));
        }
        else if (i % 4 == 3)
        {
            strip.setPixelColor(i, strip.Color(25, 100, 30));
        }
        else
        {
            strip.setPixelColor(i, strip.Color(100, 30, 25));
        }
        strip.show();
    }
}

void humidityData()
{
    int humidityValueUpper = analogRead(PIN_HUMIDITYSENSOR_UPPER);
    int humidityValueLower = analogRead(PIN_HUMIDITYSENSOR_UPPER);
    humSensorUpper.setValue(humidityValueUpper);
    humidityValueUpper = humidityValueConverter(humidityValueUpper);
    Serial.print("Humidity upper: " + String(humidityValueUpper));

    humSensorLower.setValue(humidityValueUpper);
    humidityValueLower = humidityValueConverter(humidityValueUpper);
    Serial.print("Humidity lower: " + String(humidityValueUpper));

    std::vector<HaSensor> sensors = {humSensorUpper, humSensorLower};
    connection.sendData("Sensor Eb en Vloed", sensors);
    delay(10000);
}

int humidityValueConverter(int rawValue)
{
    int percentage = map(rawValue, 1500, 3900, 100, 0);
    return constrain(percentage, 0, 100);
}

void openValveForDuration(int valvePin, unsigned long duration)
{
    digitalWrite(valvePin, HIGH);
    delay(duration);
    digitalWrite(valvePin, LOW);
}

void openDoubleValveForDuration(int valvePin1, int valvePin2, unsigned long duration)
{
    digitalWrite(valvePin1, HIGH);
    digitalWrite(valvePin2, HIGH);
    delay(duration);
    digitalWrite(valvePin1, LOW);
    digitalWrite(valvePin2, LOW);
}

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

void killSwitch()
{
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(valvePins[i], LOW);
  }
  strip.clear();
  strip.show();
}

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

void automaticProcess() {
  if (!killswitchActive) {
    handleButtonPress(1);
    handleButtonPress(2);
    handleButtonPress(3);
    handleButtonPress(4);
  }
  digitalWrite(PIN_PUMP_VALVE, HIGH);
  delay(1000);
  digitalWrite(PIN_PUMP_VALVE, LOW);
  delay(1000);
}
