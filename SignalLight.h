/*
 * SignalLight.h
 *
 *  Created on: 8 Apr 2021
 *      Author: pionet
 */

#ifndef SIGNALLIGHT_H_
#define SIGNALLIGHT_H_
#include "Arduino.h"
#include <Controllino.h>

class SignalLight {
public:
	SignalLight(uint8_t redPin, uint8_t yellowPin, uint8_t greenPin);
	void begin();
	void loop();
	void greenOn();
	void greenOff();
	void yellowOn();
	void yellowOff();
	void redOn();
	void redOff();
	bool isRedOn(){ return _redLightOn; };
	bool isYellowOn(){ return _yellowLightOn; };
	bool isGreenOn(){ return _greenLightOn; };
	virtual ~SignalLight();

private:
	uint8_t _redPin;
	uint8_t _yellowPin;
	uint8_t _greenPin;
	bool _redLightOn;
	bool _yellowLightOn;
	bool _greenLightOn;
};

#endif /* SIGNALLIGHT_H_ */
