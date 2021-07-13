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

#define MINI_CONV_YELLOW_BULB_FLASHING_FOR_RED_MS 100

class SignalLight {
public:
	SignalLight(uint8_t redPin, uint8_t yellowPin, uint8_t greenPin, uint8_t miniConvYellowPin);
	void begin();
	void loop();
	void greenOn();
	void greenOff();
	void yellowOn();
	void yellowOff();
	void miniConvYellowOn();
	void miniConvYellowOff();
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
	uint8_t _miniConvYellowPin;
	bool _redLightOn;
	bool _yellowLightOn;
	bool _greenLightOn;
	bool _miniConvYellowOn;
	uint32_t _elapsedTime;

};

#endif /* SIGNALLIGHT_H_ */
