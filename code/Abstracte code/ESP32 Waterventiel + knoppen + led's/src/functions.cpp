#include "sensor.h"
#include "functions.h"

// Define variables
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN_LEDSTRIP, NEO_GRB + NEO_KHZ800);
unsigned long debounceDelay = 50;
unsigned long valveDelay = 10000;
unsigned long valve90Seconds = 90000;
unsigned long previousMillis[5] = {0, 0, 0, 0, 0};
unsigned long valveTimer = 0;
unsigned long humidityTimer = 0; // Timer for humidity updates
const unsigned long humidityInterval = 600000; // 10 minutes in milliseconds
bool valve2Active = false;
bool valve3And4Active = false;
int buttonState[5] = {LOW, LOW, LOW, LOW, LOW};
int lastButtonState[5] = {LOW, LOW, LOW, LOW, LOW};
int ledState = 0;
bool killswitchActive = false;

// Sensor objects
HaSensor humiditySensor("Humidity Sensor", SensorType::HUMIDITY);

void setup() {
    Serial.begin(9600);
    setupPins();

    // Initialize sensors
    humiditySensor.setValue(0.0); // Initial value
    Serial.println(humiditySensor.toJson()); // om de 10 min waarde updaten.
}

void loop() {
    checkKillSwitch();
    updateButtonStates();
    updateValveCycle();

    // Periodically send humidity data
    unsigned long currentMillis = millis();
    if (currentMillis - humidityTimer >= humidityInterval) {
        sendHumidityData();
        humidityTimer = currentMillis;
    }
}

void setupPins() {
    // Set the pins for the buttons
    for (int i = 0; i < 5; i++) {
        pinMode(PIN_INPUT_WATERPUMP + i, INPUT_PULLUP);
    }
    for (int i = 0; i < 5; i++) {
        pinMode(PIN_PUMP_VALVE + i, OUTPUT);
        digitalWrite(PIN_PUMP_VALVE + i, LOW);
    }
    strip.begin();
    strip.show();
}

void updateButtonStates() {
    for (int i = 0; i < 5; i++) {
        int reading = digitalRead(PIN_INPUT_WATERPUMP + i);
        if (reading != lastButtonState[i] && millis() - previousMillis[i] > debounceDelay) {
            previousMillis[i] = millis();
            lastButtonState[i] = reading;
            if (reading == HIGH) {
                handleButtonPress(i + 1);
                logStatus(i + 1); // Log the button press and status
            }
        }
    }
}

void handleButtonPress(int button) {
    if (killswitchActive) {
        return;
    }
    switch (button) {
        case 1:
            // Open the pump valve for 10 seconds
            openValveForDuration(PIN_PUMP_VALVE, valveDelay);
            break;
        case 2:
            // Open the output valve for 10 seconds
            controlWaterPump(true, 10000);
            openValveForDuration(PIN_VALVE_OUTPUT, valveDelay);
            break;
        case 3:
            // Open the input valve for 10 seconds
            valveTimer = millis();
            valve2Active = true;
            digitalWrite(PIN_VALVE_INPUT, HIGH);
            break;
        case 4:
            // Toggle the LED strip
            toggleLEDStrip();
            break;
        case 5:
            // Kills all processes
            killSwitch();
            break;
    }
}

void logStatus(int button) {
    switch (button) {
        case 1:
            Serial.println("Status: Pump Valve Opened");
            std::cout("status: pump valve opened");
            break;
        case 2:
            Serial.println("Status: Output Valve Opened");
            std::cout("status: output valve opened");
            break;
        case 3:
            Serial.println("Status: Input Valve Opened");
            std::cout("status: input valve opened");
            break;
        case 4:
            Serial.println("Status: LED Strip Toggled");
            std::cout("status: led strip toggled");
            break;
        case 5:
            Serial.println("Status: Killswitch Activated");
            std::cout("status: killswitch activated");
            break;
    }
}

void openValveForDuration(int valvePin, unsigned long duration) {
    digitalWrite(valvePin, HIGH);
    delay(duration);
    digitalWrite(valvePin, LOW);
}

void sendHumidityData() {
    int humidityValue = analogRead(PIN_HUMIDITYSENSOR);
    float humidityPercentage = map(humidityValue, 0, 1023, 0, 100); // Adjust based on sensor range
    humiditySensor.setValue(humidityPercentage);

    // Log the humidity JSON
    String humidityJson = humiditySensor.toJson();
    Serial.println("Sending Humidity Data:");
    Serial.println(humidityJson);
}

void toggleLEDStrip() {
    switch (ledState) {
        case 0:
            // Set the LED strip to red
            strip.fill(strip.Color(255, 0, 0), 0, strip.numPixels());
            ledState = 1;
            Serial.println("LEDS: ON");
            std::cout("leds: on")

            break;
        case 1:
            // Clear the LED strip
            strip.clear();
            ledState = 0;
            Serial.println("LEDS: OFF");
            std::cout("leds: off");
            break;
    }
    strip.show();
}

void checkKillSwitch() {
    int switchState = digitalRead(PIN_KILLSWITCH);
    if (switchState == HIGH && !killswitchActive) {
        killswitchActive = true;
        Serial.println("Status: ON");
        std::cout("status: on")
    } else if (switchState == LOW && killswitchActive) {
        killswitchActive = false;
        Serial.println("Status: OFF");
        std::cout("status: off");
    }
}

void killSwitch() {
    for (int i = 0; i < 5; i++) {
        digitalWrite(PIN_PUMP_VALVE + i, LOW);
    }
    strip.clear();
    strip.show();
    ledState = 0;
}

void updateValveCycle() {
    if (valve2Active && millis() - valveTimer >= valve90Seconds) {
        // Close the input valve and open the output valve
        digitalWrite(PIN_VALVE_INPUT, LOW);
        valve2Active = false;
        valveTimer = millis();
        valve3And4Active = true;
        digitalWrite(PIN_VALVE_OUTPUT_UPPER, HIGH);
        digitalWrite(PIN_VALVE_OUTPUT_LOWER, HIGH);
    }
    if (valve3And4Active && millis() - valveTimer > valve90Seconds) {
        // Close the output lower valve and open the upper valve
        digitalWrite(PIN_VALVE_OUTPUT_UPPER, LOW);
        digitalWrite(PIN_VALVE_OUTPUT_LOWER, LOW);
        valve3And4Active = false;
    }
}

void controlWaterPump(bool state, unsigned long duration) {
    if (state) {
        digitalWrite(PIN_PUMP, HIGH);    // Turn on the pump
        delay(duration);                 // Keep it on for the specified duration
        digitalWrite(PIN_PUMP, LOW);
        Serial.println("Status: Pump on");
        std::cout("pump on")  // Turn off the pump after the duration
    } else {
        digitalWrite(PIN_PUMP, LOW);
        Serial.println("Status: Pump off"); 
        std::cout("pump off")    // Immediately turn off the pump if state is false
    }
}
