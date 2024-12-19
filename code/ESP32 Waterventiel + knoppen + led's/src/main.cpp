// works for LED

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "functions.h"
#include "connection.h"
#include "sensor.h"
#include "config.h"

// Define variables
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, PIN_LEDSTRIP, NEO_GRB + NEO_KHZ800);
unsigned long debounceDelay = 50;
unsigned long pumpDelay = 2000;
unsigned long valveDelay = 60000;
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

HaSensor humSensorUpper;
HaSensor humSensorLower;

HaConnection connection;

void ledsToColor()
{
  // Set all LEDs to a certain color
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
  humSensorUpper = HaSensor("Vochtigheid boven: ", SensorType::HUMIDITY, 0, 100);
  humSensorLower = HaSensor("Vochtigheid beneden: ", SensorType::HUMIDITY, 0, 100);
  // Get the humidity values from the sensors and send it to Home Assistant
  float humidityValueUpper = analogRead(PIN_HUMIDITYSENSOR_UPPER);
  float humidityValueLower = analogRead(PIN_HUMIDITYSENSOR_UPPER);

  humSensorUpper.setValue(humidityValueUpper);
  humidityValueUpper = humidityValueConverter(humidityValueUpper);
  Serial.print("Humidity upper: " + String(humidityValueUpper));

  humSensorLower.setValue(humidityValueUpper);
  humidityValueLower = humidityValueConverter(humidityValueUpper);
  Serial.print("Humidity lower: " + String(humidityValueUpper));

  connection.sendData("Sensors Eb en Vloed", {humSensorLower, humSensorUpper});

  delay(10000);
}

int humidityValueConverter(int rawValue)
{
  // Convert the raw value from the sensor to a percentage
  float percentage = map(rawValue, 1500, 3900, 100, 0);
  return constrain(percentage, 0, 100);
}

void openValveForDuration(int valvePin, unsigned long duration)
{
  // Open a valve for a certain duration
  digitalWrite(valvePin, HIGH);
  delay(duration);
  digitalWrite(valvePin, LOW);
}

void openDoubleValveForDuration(int valvePin1, int valvePin2, unsigned long duration)
{
  // Open two valves for a certain duration
  digitalWrite(valvePin1, HIGH);
  digitalWrite(valvePin2, HIGH);
  delay(duration);
  digitalWrite(valvePin1, LOW);
  digitalWrite(valvePin2, LOW);
}

void handleButtonPress()
{
  if (killswitchActive)
  {
    return;
  }
  // Handle the button press
  if(digitalRead(PIN_INPUT_WATERTANK) == HIGH)
  {
    Serial.println("Pump valve opened");
        digitalWrite(PIN_VALVE_INPUT, HIGH);
    digitalWrite(PIN_PUMP_VALVE, HIGH);
    Serial.println("Pump valve closed");
  }else{
        digitalWrite(PIN_VALVE_INPUT, LOW);

  } 

  if (digitalRead(PIN_INPUT_WATERPUMP) == HIGH)
  {
        digitalWrite(PIN_PUMP_VALVE, HIGH);


  }else{
    digitalWrite(PIN_PUMP_VALVE, LOW);
  }

  if(digitalRead(PIN_OUTPUT_WATER) == HIGH){
    Serial.println("Output valves opened");
    digitalWrite(PIN_VALVE_OUTPUT_UPPER, HIGH);
    digitalWrite(PIN_VALVE_OUTPUT_LOWER, HIGH);
    Serial.println("Output valves closed");
  }else{
    digitalWrite(PIN_VALVE_OUTPUT_UPPER, LOW);
    digitalWrite(PIN_VALVE_OUTPUT_LOWER, LOW);
  }

  if(digitalRead(PIN_OUTPUT_WATERTANK) == HIGH){
    digitalWrite(PIN_VALVE_OUTPUT, HIGH);
    Serial.println("Input valve opened");
  }else{
    digitalWrite(PIN_VALVE_OUTPUT, LOW);
  }
  
  if(digitalRead(PIN_LED) == HIGH){
    ledsToColor();
    Serial.println("LED strip toggled");
  }else{
    strip.clear();
    strip.show();
  }

  if(digitalRead(PIN_KILLSWITCH) == HIGH){
    killSwitch();
    Serial.println("Killswitch activated");
  }else if(digitalRead(PIN_KILLSWITCH) == LOW){
    Serial.println("Killswitch deactivated");
  }

}

void checkKillSwitch()
{
  // Check if the killswitch is activated
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
  // Kill all processes
  for (int i = 0; i < 5; i++)
  {
    digitalWrite(valvePins[i], LOW);
  }
  strip.clear();
  strip.show();
}

void setupPins()
{
  // Setup the pins
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
  // Turn pump on and valve
  digitalWrite(PIN_PUMP, HIGH);
  Serial.println("Pump on & Valve open");
  // digitalWrite(PIN_VALVE_OUTPUT, HIGH);
  delay(duration);
  // close valve
  // Serial.println("Valve closed");
  // digitalWrite(PIN_VALVE_OUTPUT, LOW);
  delay(duration);
  // turn pump off
  digitalWrite(PIN_PUMP, LOW);
  Serial.println("Pump off");
}

void automaticProcess()
{
  // Run the automatic process if killswitch is not active
  if (!killswitchActive)
  {
    // handleButtonPress(1);
    // handleButtonPress(2);
    // handleButtonPress(3);
    // handleButtonPress(4);
  }
}

void registerAndHandleButtonPresses() {
    for (int i = 0; i < 5; i++) {
        int reading = digitalRead(buttonPins[i]);
        if (reading != lastButtonState[i] && millis() - previousMillis[i] > debounceDelay) {
            previousMillis[i] = millis();
            lastButtonState[i] = reading;
            if (reading == HIGH) {
                handleButtonPress(i + 1);
            }
        }
    }
}

void openValve(int valvePin)
{
  digitalWrite(valvePin, HIGH);
  delay(1000);
  digitalWrite(valvePin, LOW);
  delay(1000);
  
  // Open a valve

}

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting setup...");

  setTime(8, 0, 0, 1, 11, 2024);
  setupPins();

  // Alarm.alarmRepeat(8, 0, 0, automaticProcess);
  // Alarm.alarmRepeat(20, 0, 0, automaticProcess);

  connection = HaConnection(WIFI_SSID, WIFI_PASSWORD, "10.10.2.20", 8123);
  connection.setup();

  if (!connection.connected)
  {
    return;
  }

  Serial.println("Setup complete");
  Serial.println("Starting sensor setup");

  connection.setup();
}

void loop()
{
  checkKillSwitch();
  // if (!killswitchActive)
  // {
  //   if(digitalRead(PIN_LED) == HIGH)
  //   {
  //     ledsToColor();
  //     Serial.println("LED strip toggled");
  //   }else if(digitalRead(PIN_LED) == LOW)
  //   {
  //     Serial.println("LED strip not toggled");
  //   }
  // }
  //humidityData();

  //   controlWaterPump(pumpDelay);
  //   openDoubleValveForDuration(PIN_VALVE_OUTPUT_UPPER, PIN_VALVE_OUTPUT_LOWER, valveDelay);
  //   openValveForDuration(PIN_VALVE_OUTPUT, valveDelay);

  // openValve(PIN_PUMP_VALVE);
  // openValve(PIN_VALVE_INPUT);
  // openValve(PIN_VALVE_OUTPUT_UPPER);
  // openValve(PIN_VALVE_OUTPUT_LOWER);
  // openValve(PIN_VALVE_OUTPUT);

  // if(digitalRead(PIN_LED) == HIGH){
  //   ledsToColor();
  // }

  handleButtonPress();

}


