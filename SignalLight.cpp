/*
 * SignalLight.cpp
 *
 *  Created on: 8 Apr 2021
 *      Author: pionet
 */

#include "SignalLight.h"

SignalLight::SignalLight(uint8_t redPin, uint8_t yellowPin, uint8_t greenPin, uint8_t buzzerPin) {
	_redPin = redPin;
	_yellowPin = yellowPin;
	_greenPin = greenPin;
	_buzzerPin = buzzerPin;
	_redLightOn = false;
	_yellowLightOn = false;
	_greenLightOn = false;
	_buzzerOn = false;
	_elapsedTime = 0;

};

void SignalLight::begin(){
	pinMode(_redPin, OUTPUT);
	pinMode(_yellowPin, OUTPUT);
	pinMode(_greenPin, OUTPUT);
	pinMode(_buzzerPin, OUTPUT);
	digitalWrite(_redPin, LOW);
	digitalWrite(_yellowPin, LOW);
	digitalWrite(_greenPin, LOW);
	digitalWrite(_buzzerPin, LOW);
};

void SignalLight::loop(){

	/*
	 * emulate RED if only one yellow bulb available
	 *//*
	if (_redLightOn){
		if (millis() >= (_elapsedTime + MINI_CONV_YELLOW_BULB_FLASHING_FOR_RED_MS)){
				if (_miniConvYellowOn == false){
					miniConvYellowOn();
				}else{
					 miniConvYellowOff();
				}
				_elapsedTime = millis();
		};
	} else if ((_redLightOn == false) && (_yellowLightOn == false) && (_miniConvYellowOn == true)){
		miniConvYellowOff();
	};*/
};

void SignalLight::redOn(){
	digitalWrite(_redPin, HIGH);
	_redLightOn = true;
};
void SignalLight::redOff(){
	digitalWrite(_redPin, LOW);
	_redLightOn = false;
	//miniConvYellowOff();
};

void SignalLight::yellowOn(){
	digitalWrite(_yellowPin, HIGH);
	_yellowLightOn = true;
	if (_redLightOn == false){
		//miniConvYellowOn();
	};
};
void SignalLight::yellowOff(){
	digitalWrite(_yellowPin, LOW);
	_yellowLightOn = false;
	if (_redLightOn == false){
		//miniConvYellowOff();
	};
};

void SignalLight::greenOn(){
	digitalWrite(_greenPin, HIGH);
	_greenLightOn = true;
};

void SignalLight::greenOff(){
	digitalWrite(_greenPin, LOW);
	_greenLightOn = false;
};

void SignalLight::allLightOn(){
	redOn();
	yellowOn();
	greenOn();

};

void SignalLight::allLightOff(){
	redOff();
	yellowOff();
	greenOff();
};

void SignalLight::buzzerOn(){
	digitalWrite(_buzzerPin, HIGH);
	_buzzerOn = true;
};

void SignalLight::buzzerOff(){
	digitalWrite(_buzzerPin, LOW);
	_buzzerOn = false;
};



SignalLight::~SignalLight() {
	// TODO Auto-generated destructor stub
}

