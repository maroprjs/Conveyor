/*
 * InfraredSensor.h
 *
 *  Created on: 29 Jan 2022
 *      Author: pionet
 */

#ifndef INFRAREDSENSOR_H_
#define INFRAREDSENSOR_H_
#include "Arduino.h"
#include <Controllino.h>
#include "Conveyor.h"

class InfraredSensor {
public:
	InfraredSensor(uint8_t irSensorPin, Conveyor* conveyor);
	void begin();
	void loop();
	bool isObjectDetected(){ return _objectDetected; };
	virtual ~InfraredSensor();

private:
	uint8_t _irSensorPin;
	bool _objectDetected;
	Conveyor* _conveyor;
};

#endif /* INFRAREDSENSOR_H_ */
