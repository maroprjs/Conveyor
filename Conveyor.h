/*
 * Conveyor.h
 *
 *  Created on: 7 Feb 2021
 *      Author: pionet
 */

#ifndef CONVEYOR_H_
#define CONVEYOR_H_

#include "Arduino.h"

//macro for detection af rasing edge
#define RE(signal, state) (state=(state<<1)|(signal&1)&3)==1

//macro for detection af falling edge
#define FE(signal, state) (state=(state<<1)|(signal&1)&3)==2

class Conveyor {


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
	uint16_t readHalls();

	virtual ~Conveyor();

private:
	void off();
	void on();
	void electronicsPwrOff();
	void electronicsPwrOn();
	void motorPwrOff();
	void motorPwrOn();

private:
	uint8_t _electronicsPwrPin;
	uint8_t _motorPwrPin;
	uint8_t _speedPin;
	uint8_t _hallSensorPin;
	uint8_t _sensorPinState;
	uint16_t _hallSensorCount;
	uint8_t _directionPin;
	//bool _conveyorOn;
	//bool _conveyorOnReq;
	bool _electronicsPwrOn;
	bool _electronicsPwrOnReq;
	bool _motorPwrOn;
	bool _motorPwrOnReq;

};

#endif /* CONVEYOR_H_ */
