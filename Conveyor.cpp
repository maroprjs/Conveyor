/*
 * Conveyor.cpp
 *
 *  Created on: 7 Feb 2021
 *      Author: pionet
 */

#include "Conveyor.h"

Conveyor::Conveyor(uint8_t electronicsPwrPin, uint8_t motorPwrPin, uint8_t speedPin, uint8_t directionPin, uint8_t hallSensorPin) {
	_electronicsPwrPin = electronicsPwrPin;
	_motorPwrPin = motorPwrPin;
	_speedPin = speedPin;
	_hallSensorPin = hallSensorPin;
	_directionPin = directionPin;
	//_conveyorOn = false;
	//_conveyorOnReq = false;
	_electronicsPwrOn = false;
	_electronicsPwrOnReq = false;
	_motorPwrOn = false;
	_motorPwrOnReq = false;
	_hallSensorCount = 0;
	_sensorPinState = LOW;


}

void Conveyor::begin(){
	pinMode(_electronicsPwrPin, OUTPUT);
	pinMode(_motorPwrPin, OUTPUT);
	pinMode(_speedPin, OUTPUT);
	pinMode(_directionPin, OUTPUT);
	pinMode(_hallSensorPin, INPUT);

	digitalWrite(_electronicsPwrPin, LOW);
	digitalWrite(_motorPwrPin, LOW);
	digitalWrite(_directionPin, HIGH);
	analogWrite(_speedPin, 0);


}

void Conveyor::loop(){

	//if ((_conveyorOnReq == true) && ( _conveyorOn == false )) on();
	//if ((_conveyorOnReq == false) && ( _conveyorOn == true )) off();
	if ((_electronicsPwrOnReq == true) && ( _electronicsPwrOn == false )) electronicsPwrOn();
	if ((_electronicsPwrOnReq == false) && ( _electronicsPwrOn == true )) electronicsPwrOff();
	if ((_motorPwrOnReq == true) && ( _motorPwrOn == false )) motorPwrOn();
	if ((_motorPwrOnReq == false) && ( _motorPwrOn == true )) motorPwrOff();
	//if( RE(digitalRead(_hallSensorPin), _sensorPinState) ){
	//	_hallSensorCount++;
	//};


}

void Conveyor::pwrOnReq(){
	//_conveyorOnReq = true;
	_electronicsPwrOnReq = true;
	_motorPwrOnReq = true;

}

void Conveyor::pwrOffReq(){
	//_conveyorOnReq = false;
	_electronicsPwrOnReq = false;
	_motorPwrOnReq = false;
}

void Conveyor::electronicsPwrOnReq(){
	_electronicsPwrOnReq = true;
	Serial.println("electronicsPwrOnReq");
}

void Conveyor::electronicsPwrOffReq(){
	_electronicsPwrOnReq = false;
	Serial.println("electronicsPwrOffReq");
}

void Conveyor::motorPwrOnReq(){
	_motorPwrOnReq = true;
	Serial.println("motorPwrOnReq");
}

void Conveyor::motorPwrOffReq(){
	_motorPwrOnReq = false;
	Serial.println("motorPwrOffReq");
}


void Conveyor::setSpeed(int speed){
	if (speed == 0){
		motorPwrOffReq();
	}else{
		motorPwrOnReq();
	};
	analogWrite(_speedPin, speed);



}

uint16_t Conveyor::readHalls(){
	uint16_t ret = _hallSensorCount;
	_hallSensorCount = 0;
	return ret;
}

void Conveyor::off(){
	electronicsPwrOff();
	motorPwrOff();
	//_conveyorOn = false;

}

void Conveyor::on(){
	electronicsPwrOn();
	motorPwrOn();
	//_conveyorOn = true;

}

void Conveyor::electronicsPwrOff(){
	digitalWrite(_electronicsPwrPin, LOW);
	_electronicsPwrOn = false;
	Serial.println("elecs off");
}

void Conveyor::electronicsPwrOn(){
	digitalWrite(_electronicsPwrPin, HIGH);
	_electronicsPwrOn = true;
	Serial.println("elecs on");
}

void Conveyor::motorPwrOff(){
	digitalWrite(_motorPwrPin, LOW);
	_motorPwrOn = false;
	Serial.println("motor off");
}

void Conveyor::motorPwrOn(){
	digitalWrite(_motorPwrPin, HIGH);
	_motorPwrOn = true;
	Serial.println("motor on");
}

Conveyor::~Conveyor() {
	// TODO Auto-generated destructor stub
}

