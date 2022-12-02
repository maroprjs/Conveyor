/*
 * Conveyor.h
 *
 *  Created on: 7 Feb 2021
 *      Author: pionet
 */

#ifndef CONVEYOR_H_
#define CONVEYOR_H_

#include "Arduino.h"
#include <Controllino.h>

#define HALL_SENSOR_MEAS_INTERVAL_MS 1000
#define SECONDS HALL_SENSOR_MEAS_INTERVAL_MS / 1000 //if required change this with meas interval accordingly
#define HALLS_PER_ROUND 32
#define RPM_FACTOR 60 * SECONDS / HALLS_PER_ROUND
#define SPEED_ZERO  0 //PWM 0 doesn't produce 0V, so we add an offset
#define INITIAL_SPEED 4
#define STATE_TRANSITION_TIME_MS 25


#define NUM_OF_SPEED_VALUES 10
#define SPEED_MAPPING  {0,25,50,85,110,135,160,185,210,255}


class Conveyor {

	enum DirectionChangeState{
		IDLE,
		RELEASE_DIRECTIONAL_CONTACTS,
		RESUME_DIRECTIONAL_CONTACTS,
		RESUME_SPEED
	};

public:
	Conveyor(uint8_t electronicsPwrPin, uint8_t motorPwrPin, uint8_t speedPin, uint8_t hallSensorPin, uint8_t forwardPin, uint8_t reversePin );
	void begin();
	void loop();
	void pwrOnReq();
	void pwrOffReq();
	void electronicsPwrOnReq();
	void electronicsPwrOffReq();
	void motorPwrOnReq();
	void motorPwrOffReq();
	void setSpeed(int speed); //PWM value between 0....255
	void moveReverseReq();
	void moveForwardReq();
	void motorPwrOff();
	uint16_t readRPM(){return _currentHallCountsPerInterval * RPM_FACTOR;};
	bool isMotorPwrOn(){ return _motorPwrOn; };
	bool isElectronicsPwrOn(){ return _electronicsPwrOn; };
	int readSpeed(){ return _currentSpeed;}; //PWM value between 0....255
	bool isForward(){ return _isForward;};
	int speedDelta(){return _speedDelta;};
	void speedUpDown();

	virtual ~Conveyor();

private:
	void off();
	void on();
	void electronicsPwrOff();
	void electronicsPwrOn();
	//void motorPwrOff();
	void motorPwrOn();
	void switchDirection();
	void releaseDirectionalContacts();
	void resumeDirectionalContacts();


private:
	uint8_t _electronicsPwrPin;
	uint8_t _motorPwrPin;
	uint8_t _speedPin;
	uint8_t _hallSensorPin;
	uint8_t _sensorPinState;
	//uint16_t _hallSensorCount;
	uint8_t _forwardPin;
	uint8_t _reversePin;
	//bool _conveyorOn;
	//bool _conveyorOnReq;
	bool _electronicsPwrOn;
	bool _electronicsPwrOnReq;
	bool _motorPwrOn;
	bool _motorPwrOnReq;
	uint32_t _elapsedTime;
	uint32_t _measurementInterval;
	uint32_t _currentHallCountsPerInterval;
	int _lastSpeed;
	int _currentSpeed;
	bool _electronicsInitialized; //if electronic didnt have a speed unequal zero at least once and direction changed, it motor will move despite zero speed settings
	bool _forwardReq;
	bool _isForward;
	DirectionChangeState _directionChangeState;
	uint32_t _nextStateTransition;
	uint32_t _transitionStartTime;
	int _speedDelta;
	bool _minSpeedReached;
	bool _maxSpeedReached;


};

#endif /* CONVEYOR_H_ */
