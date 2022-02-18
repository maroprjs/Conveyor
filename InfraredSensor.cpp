/*
 * InfraredSensor.cpp
 *
 *  Created on: 29 Jan 2022
 *      Author: pionet
 */

#include "InfraredSensor.h"

#include "Defines.h"

volatile uint32_t iobjectDetected;

void objectDetected(void) {
	digitalWrite(MOTOR_PWR_PIN, LOW);
	iobjectDetected = true;
}

InfraredSensor::InfraredSensor(uint8_t irSensorPin, Conveyor* conveyor) {
	_irSensorPin = irSensorPin;
	_objectDetected = false;
	_conveyor = conveyor;

}

void InfraredSensor::begin(){
	pinMode(_irSensorPin, INPUT);
	attachInterrupt(digitalPinToInterrupt(_irSensorPin), objectDetected, RISING);
};

void InfraredSensor::loop(){
	//_objectDetected = (digitalRead(_irSensorPin) == HIGH) ? true : false ;
	//_objectDetected = iobjectDetected;
	//iobjectDetected = false;
	if (iobjectDetected == true){
		iobjectDetected = false;
		_conveyor->motorPwrOffReq(); //Note!!! Power turned off already by interrupt (above), due timing!!!!

	};
	_objectDetected = digitalRead(_irSensorPin);
}

InfraredSensor::~InfraredSensor() {
	// TODO Auto-generated destructor stub
}

