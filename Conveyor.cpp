/*
 * Conveyor.cpp
 *
 *  Created on: 7 Feb 2021
 *      Author: pionet
 */

#include "Conveyor.h"

volatile uint32_t hallSensorCount;

void countHall(void) {
	hallSensorCount++;
}

Conveyor::Conveyor(uint8_t electronicsPwrPin, uint8_t motorPwrPin, uint8_t speedPin, uint8_t directionPin, uint8_t hallSensorPin) {
	_electronicsPwrPin = electronicsPwrPin;
	_motorPwrPin = motorPwrPin;
	_speedPin = speedPin;
	_hallSensorPin = hallSensorPin;
	_directionPin = directionPin;
	_forwardPin = FORWARD_PIN;
	_reversePin = REVERSE_PIN;
	//_conveyorOn = false;
	//_conveyorOnReq = false;
	_electronicsPwrOn = false;
	_electronicsPwrOnReq = false;
	_motorPwrOn = false;
	_motorPwrOnReq = false;
	//_hallSensorCount = 0;
	_sensorPinState = LOW;

	_elapsedTime = 0;
	_measurementInterval = HALL_SENSOR_MEAS_INTERVAL_MS;
	_currentHallCountsPerInterval = 0;
	_lastSpeed = SPEED_ZERO;
	_currentSpeed = SPEED_ZERO;
	_forwardReq = true;
	_directionChangeState = IDLE;
	_isForward = true;
	_nextStateTransition = 0;
	_transitionStartTime = 0;

}

void Conveyor::begin(){
	pinMode(_electronicsPwrPin, OUTPUT);
	pinMode(_motorPwrPin, OUTPUT);
	pinMode(_speedPin, OUTPUT);
	pinMode(_directionPin, OUTPUT);
	pinMode(_forwardPin, OUTPUT);
	pinMode(_reversePin, OUTPUT);
	pinMode(_hallSensorPin, INPUT);

	digitalWrite(_electronicsPwrPin, LOW);
	digitalWrite(_motorPwrPin, LOW);
	digitalWrite(_directionPin, LOW); //LOW = forward
    resumeDirectionalContacts();//for safety, those to pins always treated together
	analogWrite(_speedPin, _lastSpeed);

	attachInterrupt(digitalPinToInterrupt(_hallSensorPin), countHall, RISING);
	_elapsedTime = millis();


}

void Conveyor::loop(){

	//if ((_conveyorOnReq == true) && ( _conveyorOn == false )) on();
	//if ((_conveyorOnReq == false) && ( _conveyorOn == true )) off();
	if ((_electronicsPwrOnReq == true) && ( _electronicsPwrOn == false )) electronicsPwrOn();
	if ((_electronicsPwrOnReq == false) && ( _electronicsPwrOn == true )) electronicsPwrOff();
	if ((_motorPwrOnReq == true) && ( _motorPwrOn == false )) motorPwrOn();
	if ((_motorPwrOnReq == false) && ( _motorPwrOn == true )) motorPwrOff();
	if (millis() >= (_elapsedTime + _measurementInterval)){ //motor speed
		_currentHallCountsPerInterval = hallSensorCount;
		_elapsedTime = millis();
		hallSensorCount = 0;
		Serial.print("motor speed: ");Serial.print(_currentHallCountsPerInterval/32);Serial.println(" rpi");
	};
	if ((_forwardReq == true) && (_isForward == false)) switchDirection();
	if ((_forwardReq == false) && (_isForward == true)) switchDirection();





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
	//if (speed == 0){ <- this was necessary when PWM used without DAC 0...10V converter
	//	motorPwrOffReq();
	//}else{
	//	motorPwrOnReq();
	//};
	speed = (speed < SPEED_ZERO) ? SPEED_ZERO : speed;
	analogWrite(_speedPin, speed);
	_currentSpeed = speed;
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

void Conveyor::moveForwardReq(){
		_forwardReq = true;//TODO
		Serial.println("moveForwardReq");

}
void Conveyor::moveReverseReq(){
		_forwardReq = false;
		Serial.println("moveReverseReq");
}

void Conveyor::switchDirection(){
	bool doesntStop = false;
	if ((millis() + STATE_TRANSITION_TIME_MS) >= _nextStateTransition ){
		switch (_directionChangeState)
		{
		 case IDLE:
			_lastSpeed = _currentSpeed;
			_transitionStartTime = millis();
			setSpeed(0);
			_directionChangeState = RELEASE_DIRECTIONAL_CONTACTS;
	        _nextStateTransition = millis() + STATE_TRANSITION_TIME_MS;
	        break;
		 case RELEASE_DIRECTIONAL_CONTACTS:
			doesntStop = ((millis() - _transitionStartTime) > (2* HALL_SENSOR_MEAS_INTERVAL_MS)) ? true : false; //should be enough time to reach zero
			if ((_currentHallCountsPerInterval == 0) || (doesntStop == true)) {
				releaseDirectionalContacts();
				_directionChangeState = RESUME_DIRECTIONAL_CONTACTS;
				_nextStateTransition = millis() + STATE_TRANSITION_TIME_MS;
				if  (doesntStop == true) motorPwrOffReq();
			};
			break;
		 case RESUME_DIRECTIONAL_CONTACTS:
			if (_motorPwrOn == false){
				motorPwrOnReq();
			}
			else{
				resumeDirectionalContacts();
				_directionChangeState = RESUME_SPEED;
			};
			_nextStateTransition = millis() + STATE_TRANSITION_TIME_MS;
			break;
		 case RESUME_SPEED:
			setSpeed(_lastSpeed);
			_isForward = (_isForward == true) ? false : true;
			_directionChangeState = IDLE;
			break;
		}
	}
}

void Conveyor::releaseDirectionalContacts(){
	digitalWrite(_forwardPin, LOW); //LOW = relay contact open
	digitalWrite(_reversePin, LOW); //LOW = relay contact open
}

void Conveyor::resumeDirectionalContacts(){
	if (_forwardReq == true){
		digitalWrite(_forwardPin, HIGH); //GND to directional wire for forward
		digitalWrite(_reversePin, LOW); //LOW = relay contact to V+ open
		//_isForward = true;
	}else{
		digitalWrite(_forwardPin, LOW); // LOW = relay contact to GND open
		digitalWrite(_reversePin, HIGH); //V+ to directional wire for reverse
		//_isForward = false;
	}

}



Conveyor::~Conveyor() {
	// TODO Auto-generated destructor stub
}

