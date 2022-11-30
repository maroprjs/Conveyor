/*
 * LEDButton.h
 *
 *  Created on: 25.06.2021
 *      Author: maro
 */

#ifndef LEDBUTTON_H_
#define LEDBUTTON_H_
#include "Arduino.h"
#include "Conveyor.h"

#define LED_BUTTON_DEBOUNCE_DELAY  50 //ms

class LEDButton {
public:
	LEDButton(uint8_t buttonPin, uint8_t buttonLedPin);
	void begin();
	void loop();
	bool isClicked(){bool retVal = _isClicked; _isClicked = false; return retVal; };
	bool isReleased(){bool retVal = _isReleased; _isReleased = false; return retVal; };
	bool isActive(){return _isActive; };
	void ledOn();
	void ledOff();
	virtual ~LEDButton();
private:
	uint8_t _buttonPin;
	uint8_t _buttonLedPin;
	bool _lastButtonState;
	bool _buttonState;             // the current reading from the input pin
	uint32_t _lastDebounceTime;
	bool _isClicked;
	bool _isActive;
	bool _isReleased;
	bool _initializationDone;
};

#endif /* LEDBUTTON_H_ */
