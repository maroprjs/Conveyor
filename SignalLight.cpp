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
};
void SignalLight::redOff(){
	digitalWrite(_redPin, LOW);
};

void SignalLight::yellowOn(){
	digitalWrite(_yellowPin, HIGH);
};
void SignalLight::yellowOff(){
	digitalWrite(_yellowPin, LOW);
};

void SignalLight::greenOn(){
	digitalWrite(_greenPin, HIGH);
};

void SignalLight::greenOff(){
	digitalWrite(_greenPin, LOW);
};


SignalLight::~SignalLight() {
	// TODO Auto-generated destructor stub
}

