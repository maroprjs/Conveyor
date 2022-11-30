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
#include "LEDButton.h"
#include "Raspberry.h"

#define PUBLISH_TIME_INTERVAL_MS 1000
#define PUBLISH_MSG_ID 1


class ConveyorUI {
public:
	ConveyorUI(Modem* modem, Conveyor* conveyor, SignalLight* signalLight, NfcReader* nfcReader, InfraredSensor* irSensor,  \
			   LEDButton* startStpBtn, LEDButton* fwdRvsBtn, LEDButton* speedBtn, LEDButton* emergBtn, LEDButton* onOffSwitch, \
			   Raspberry* raspberry );
	void begin();
	void loop();
	bool serialMMI(char command);
	virtual ~ConveyorUI();

private:
	void publishStatus();
	void _eXtendedUI();
	void handleNfcActions();
	void handleButtonActions();
	void handleSignalLightActions();

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
	bool _eXtendedUIActive;
	String _cmdString;
	LEDButton* _startStpBtn;
	LEDButton* _fwdRvsBtn;
	LEDButton* _speedBtn;
	LEDButton* _emergBtn;
	LEDButton* _onOffSwitch;
	Raspberry* _raspberry;
	bool _flipFlop;
	bool _emergencyActive;
	uint8_t _speedMap[NUM_OF_SPEED_VALUES] = SPEED_MAPPING;
};

#endif /* CONVEYORUI_H_ */
