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
	SignalLight(uint8_t redPin, uint8_t yellowPin, uint8_t greenPin, uint8_t buzzerPin);
	void begin();
	void loop();
	void greenOn();
	void greenOff();
	void yellowOn();
	void yellowOff();
	void redOn();
	void redOff();
	void allLightOn();
	void allLightOff();
	void buzzerOn();
	void buzzerOff();
	bool isRedOn(){ return _redLightOn; };
	bool isYellowOn(){ return _redLightOn; };
	bool isGreenOn(){ return _greenLightOn; };
	bool isAllLightOn(){ return _redLightOn && _redLightOn && _greenLightOn;};
	bool isBuzzerOn(){ return _buzzerOn; };
	virtual ~SignalLight();

private:
	uint8_t _redPin;
	uint8_t _yellowPin;
	uint8_t _greenPin;
	uint8_t _buzzerPin;
	bool _redLightOn;
	bool _yellowLightOn;
	bool _greenLightOn;
	bool _buzzerOn;
	uint32_t _elapsedTime;

};

#endif /* SIGNALLIGHT_H_ */
