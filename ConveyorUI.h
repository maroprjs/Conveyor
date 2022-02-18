/*
 * ConveyorUI.h
 *
 *  Created on: 14 Feb 2021
 *      Author: pionet
 */

#ifndef CONVEYORUI_H_
#define CONVEYORUI_H_
#include "Modem.h"
#include "Conveyor.h"
#include "SignalLight.h"
#include "NfcReader.h"
#include "InfraredSensor.h"

#define PUBLISH_TIME_INTERVAL_MS 1000
#define PUBLISH_MSG_ID 1

class ConveyorUI {
public:
	ConveyorUI(Modem* modem, Conveyor* conveyor, SignalLight* signalLight, NfcReader* nfcReader, InfraredSensor* irSensor);
	void begin();
	void loop();
	bool serialMMI(char command);
	virtual ~ConveyorUI();

private:
	void publishStatus();

private:
	Modem* _modem;
	Conveyor* _conveyor;
	SignalLight* _signalLight;
	NfcReader* _nfcReader;
	InfraredSensor* _irSensor;
	char* _rxMsg;
	char* _txMsg;
	uint32_t _elapsedPublishTime;
	uint32_t _publishInterval;
};

#endif /* CONVEYORUI_H_ */
