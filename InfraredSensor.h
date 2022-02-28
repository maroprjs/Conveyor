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

#define TEMPORAR_DISABLED_TIME 3000

class InfraredSensor {
public:
	InfraredSensor(uint8_t irSensorPin, Conveyor* conveyor);
	void begin();
	void loop();
  void enable();
  void disable();
  void disableTemporaly();
	bool isObjectDetected(){ return _objectDetected; };
	virtual ~InfraredSensor();

private:
	uint8_t _irSensorPin;
	bool _objectDetected;
  bool _temporaryDisabled;
  unsigned long _temporarDisabledTime;
	Conveyor* _conveyor;
};

#endif /* INFRAREDSENSOR_H_ */
