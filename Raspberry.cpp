/*
 * Raspberry.cpp
 *
 *  Created on: 29 Nov 2022
 *      Author: pionet
 */

#include "Raspberry.h"

Raspberry::Raspberry(uint8_t buttonPin, uint8_t sensePin, uint8_t fullPwrPin) {
	_buttonPin = buttonPin;
	_sensePin = sensePin;
	_elapsedTime = 0;
	_onOffClicked = false;
	_fullPwrPin = fullPwrPin;
	_fullPwrOffRequired = false;
	_elapsedTimeFullPwr = 0;
	_switchOnRequired = false;
	_switchOffRequired = false;
	_elapsedStartupTime = 0;

}

void Raspberry::begin(){
	pinMode(_buttonPin, OUTPUT); //controllino emulates pwr button for Raspberry
	pinMode(_fullPwrPin, OUTPUT);
	pinMode(_sensePin, INPUT);
	digitalWrite(_buttonPin, LOW);//deactivate Relais (open contact)
	digitalWrite(_fullPwrPin, LOW);//deactivate Relais (open contact)

}
void Raspberry::loop(){
	if (_onOffClicked == true){
		if (millis() >= (_elapsedTime + BTN_PRESS_TIME)){
			onOffReleaseClick();
		}
	}
	if (_fullPwrOffRequired == true){
		if (millis() >= (_elapsedTimeFullPwr + TIME_FOR_GRACEFULL_SHUTDOWN)){
			_fullPwrOffRequired = false;
			fullPwrOff();

		}
	}

	if (_switchOnRequired == true){
		if (isRaspberryOn() == false) {
			toggleOnOff();
		};
		_fullPwrOffRequired = false;
		_switchOnRequired = false;
		fullPwrOn(); //nothing will change here if already full power is on


	};

	if (_switchOffRequired == true){
		if (millis() >= (_elapsedStartupTime + TIME_TO_STARTUP)){ //give it some time, in case on/off switch released before raspberry is properly started
			if (isRaspberryOn() == true) {
				toggleOnOff();
				_fullPwrOffRequired = true;// switch full power off some time after toggle off
				Serial.println("_switchOffRequired");
				_elapsedTimeFullPwr = millis();
			}
			_switchOffRequired = false;
		}
	}

}

void Raspberry::switchOn(){
	_switchOnRequired = true;

}

void Raspberry::switchOff(){
	_switchOffRequired = true;
}

void Raspberry::toggleOnOff(){
	onOffClick();
	_elapsedTime = millis();

}

void Raspberry::onOffClick(){
	digitalWrite(_buttonPin, HIGH);
	_onOffClicked = true;

}

void Raspberry::onOffReleaseClick(){
	digitalWrite(_buttonPin, LOW);
	_onOffClicked = false;

}

void Raspberry::fullPwrOn(){
	digitalWrite(_fullPwrPin, HIGH);
	_elapsedStartupTime = millis();
}

void Raspberry::fullPwrOff(){
	digitalWrite(_fullPwrPin, LOW);
}


bool Raspberry::isRaspberryOn(){

bool retVal = false;
	if (digitalRead(_sensePin) == HIGH) retVal = true;

	return retVal;
}


Raspberry::~Raspberry() {
	// TODO Auto-generated destructor stub
}

