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
#define SPEED_ZERO  10
#define STATE_TRANSITION_TIME_MS 25

//controllino doesn't set PINs below 0.5V at LOW, as required by Vetter's Faulhaber Motor,
//hence we use two Relais contacts to switch between proper GND and +24V
#define FORWARD_PIN CONTROLLINO_R2
#define REVERSE_PIN CONTROLLINO_R3



class Conveyor {

	enum DirectionChangeState{
		IDLE,
		RELEASE_DIRECTIONAL_CONTACTS,
		RESUME_DIRECTIONAL_CONTACTS,
		RESUME_SPEED
	};

public:
	Conveyor(uint8_t electronicsPwrPin, uint8_t motorPwrPin, uint8_t speedPin, uint8_t directionPin, uint8_t hallSensorPin );
	void begin();
	void loop();
	void pwrOnReq();
	void pwrOffReq();
	void electronicsPwrOnReq();
	void electronicsPwrOffReq();
	void motorPwrOnReq();
	void motorPwrOffReq();
	void setSpeed(int speed);
	void moveReverseReq();
	void moveForwardReq();
	//bool isMotorPwrOn() {return _motorPwrOn;};
	//uint16_t readHalls();

	virtual ~Conveyor();

private:
	void off();
	void on();
	void electronicsPwrOff();
	void electronicsPwrOn();
	void motorPwrOff();
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
	uint8_t _directionPin;
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
	bool _forwardReq;
	bool _isForward;
	DirectionChangeState _directionChangeState;
	uint32_t _nextStateTransition;
	uint32_t _transitionStartTime;

};

#endif /* CONVEYOR_H_ */
