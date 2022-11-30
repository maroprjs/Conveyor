/*
 * LEDButton.cpp
 *
 *  Created on: 25.06.2021
 *      Author: maro
 */

#include "LEDButton.h"

LEDButton::LEDButton(uint8_t buttonPin, uint8_t buttonLedPin) {
	_buttonPin = buttonPin;
	_buttonLedPin = buttonLedPin;
	_lastButtonState = HIGH;
	_buttonState = HIGH;
	_lastDebounceTime = 0;
	_isClicked = false;
	_isActive = false;
	_isReleased = false;
	_initializationDone = false;
}

void LEDButton::begin(){
	pinMode(_buttonPin, INPUT);
	pinMode(_buttonLedPin, OUTPUT);
	_buttonState = digitalRead(_buttonPin);
	_lastButtonState = _buttonState;
    if (_buttonState == HIGH) {
  	  _isClicked = true;
  	  _isActive = true;
    };
	ledOff();
}

void LEDButton::loop(){
	bool reading = digitalRead(_buttonPin);
	if (reading != _lastButtonState) {
	    // reset the debouncing timer
	    _lastDebounceTime = millis();
	    	}
	if ((millis() - _lastDebounceTime) > LED_BUTTON_DEBOUNCE_DELAY) {
	   // whatever the reading is at, it's been there for longer than the debounce
	   // delay, so take it as the actual current state:

	   // if the button state has changed:
	   if (reading != _buttonState) {
	      _buttonState = reading;

    	  //if (_initializationDone == true){
    	      // only toggle  if the new button state is LOW (= surely pushed)
    	      if (_buttonState == HIGH) {
    	    	  //_wlanRouter->toggle();

    	    	  _isClicked = true;
    	    	  _isActive = true;
    	    	  ledOn();

              }else{
            	  _isActive = false;
            	  _isReleased = true;
            	  ledOff();
              }

    	 // }
    	  _initializationDone = true;
	   }
	}
	_lastButtonState = reading;

}

void LEDButton::ledOn(){
	digitalWrite(_buttonLedPin, HIGH);
}

void LEDButton::ledOff(){
	digitalWrite(_buttonLedPin, LOW);
}

LEDButton::~LEDButton() {
	// TODO Auto-generated destructor stub
}

