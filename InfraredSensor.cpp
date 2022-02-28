/*
 * InfraredSensor.cpp
 *
 *  Created on: 29 Jan 2022
 *      Author: pionet
 */

#include "InfraredSensor.h"

#include "Defines.h"

volatile uint32_t iobjectDetected;
volatile bool sensorEnabled;

void objectDetected(void) {
	if (sensorEnabled == true ) digitalWrite(MOTOR_PWR_PIN, LOW);
	iobjectDetected = true;
}

InfraredSensor::InfraredSensor(uint8_t irSensorPin, Conveyor* conveyor) {
	_irSensorPin = irSensorPin;
	_objectDetected = false;
	_conveyor = conveyor;
 _temporaryDisabled = false;
 _temporarDisabledTime = 0;

}

void InfraredSensor::begin(){
	pinMode(_irSensorPin, INPUT);
  enable();
	attachInterrupt(digitalPinToInterrupt(_irSensorPin), objectDetected, RISING);
  
  _temporarDisabledTime = millis();;
};

void InfraredSensor::loop(){
	//_objectDetected = (digitalRead(_irSensorPin) == HIGH) ? true : false ;
	//_objectDetected = iobjectDetected;
	//iobjectDetected = false;
	if (iobjectDetected == true){
		iobjectDetected = false;
		if (sensorEnabled == true ) _conveyor->motorPwrOffReq(); //Note!!! Power turned off already by interrupt (above), due timing!!!!

	};

  _objectDetected = digitalRead(_irSensorPin);
  if (_temporaryDisabled == true){
    if ( millis() > _temporarDisabledTime ) {
      enable();
      _temporaryDisabled = false;
      
    }
  }
}

void InfraredSensor::disableTemporaly(){
  disable();
  _temporaryDisabled = true;
  _temporarDisabledTime = millis() + TEMPORAR_DISABLED_TIME;
}

void InfraredSensor::enable(){
  //attachInterrupt(digitalPinToInterrupt(_irSensorPin), objectDetected, RISING);
  sensorEnabled = true;
}

void InfraredSensor::disable(){
  //detachInterrupt(digitalPinToInterrupt(_irSensorPin));
  sensorEnabled = false;
  
}

InfraredSensor::~InfraredSensor() {
	// TODO Auto-generated destructor stub
}
