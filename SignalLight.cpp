/*
 * SignalLight.cpp
 *
 *  Created on: 8 Apr 2021
 *      Author: pionet
 */

#include "SignalLight.h"

SignalLight::SignalLight(uint8_t redPin, uint8_t yellowPin, uint8_t greenPin) {
	_redPin = redPin;
	_yellowPin = yellowPin;
	_greenPin = greenPin;
	_redLightOn = false;
	_yellowLightOn = false;
	_greenLightOn = false;

};

void SignalLight::begin(){
	pinMode(_redPin, OUTPUT);
	pinMode(_yellowPin, OUTPUT);
	pinMode(_greenPin, OUTPUT);
	digitalWrite(_redPin, LOW);
	digitalWrite(_yellowPin, LOW);
	digitalWrite(_greenPin, LOW);
};

void SignalLight::loop(){
	//placeholder
};

void SignalLight::redOn(){
	digitalWrite(_redPin, HIGH);
	_redLightOn = true;
};
void SignalLight::redOff(){
	digitalWrite(_redPin, LOW);
	_redLightOn = false;
};

void SignalLight::yellowOn(){
	digitalWrite(_yellowPin, HIGH);
	_yellowLightOn = true;
};
void SignalLight::yellowOff(){
	digitalWrite(_yellowPin, LOW);
	_yellowLightOn = false;
};

void SignalLight::greenOn(){
	digitalWrite(_greenPin, HIGH);
	_greenLightOn = true;
};

void SignalLight::greenOff(){
	digitalWrite(_greenPin, LOW);
	_greenLightOn = false;
};


SignalLight::~SignalLight() {
	// TODO Auto-generated destructor stub
}

