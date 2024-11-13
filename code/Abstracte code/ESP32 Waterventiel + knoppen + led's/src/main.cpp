#include "functions.h"

void setup() {

  //Automatic process
  Serial.begin(115200);
  setTime(8, 0, 0, 1, 11, 2024); 

  // Starts the automatic process at 8:00 and 20:00
  Alarm.alarmRepeat(8, 0, 0, automaticProcess);
  Alarm.alarmRepeat(20, 0, 0, automaticProcess);  

  setupPins();
}

void loop() {
  // Check if the killswitch is active
  checkKillSwitch();
  if (!killswitchActive) {
    Alarm.delay(0);
    for (int i = 0; i < 5; i++) {
      // Read the state of the button
      int buttonPin = PIN_INPUT_WATERPUMP + i;
      int reading = digitalRead(buttonPin);
      if (reading != lastButtonState[i]) {
        // reset the debouncing timer
        previousMillis[i] = millis();
      }
      if ((millis() - previousMillis[i]) > debounceDelay) {
        if (reading != buttonState[i]) {
          // save the reading
          buttonState[i] = reading;
          if (buttonState[i] == LOW) {
            // button is pressed
            handleButtonPress(i + 1);
          }
        }
      }
      lastButtonState[i] = reading;
    }
  }
  updateValveCycle();
}

