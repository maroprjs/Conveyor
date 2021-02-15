/*
 * ConveyorUI.cpp
 *
 *  Created on: 14 Feb 2021
 *      Author: pionet
 */

#include "ConveyorUI.h"

ConveyorUI::ConveyorUI(Modem* modem, Conveyor* conveyor) {
	_modem = modem;
	_conveyor = conveyor;
	_msg = new char[UDP_TX_PACKET_MAX_SIZE];

}

void ConveyorUI::begin(){
	//dummy
}

void ConveyorUI::loop(){
	if (_modem->msgArrived()){
		_modem->readMsg(_msg);
		Serial.println(_msg);
		serialMMI(_msg[0]);
	}
	while(_modem->mmiPort()->available()){
		char cmd = _modem->mmiPort()->read();
		serialMMI(cmd);
	}
}

bool ConveyorUI::serialMMI(char command){
	bool retVal = false;
	_modem->mmiPort()->print(command);
	switch (command){
	case 'e':{
			_modem->mmiPort()->println(" - turn on elec");
	    	_conveyor->electronicsPwrOnReq();
		}
		retVal = true;
		break;
	case 'm':{
			_modem->mmiPort()->println(" - turn on motor");
			_conveyor->motorPwrOnReq();
		}
		retVal = true;
		break;
	case 'o':{
			_modem->mmiPort()->println(" - turn off");
			_conveyor->pwrOffReq();
		}
		retVal = true;
		break;
	case '0':{
			_modem->mmiPort()->println(" - speed 0");
			_conveyor->setSpeed(0);
		}
		retVal = true;
		break;
	case '1':{
			_modem->mmiPort()->println(" - speed 25");
			_conveyor->setSpeed(25);
		}
		retVal = true;
		break;
	case '2':{
			_modem->mmiPort()->println(" - speed 75");
			_conveyor->setSpeed(75);
		}
		retVal = true;
		break;

	case '3':{
			_modem->mmiPort()->println(" - speed 125");
			_conveyor->setSpeed(125);
		}
		retVal = true;
		break;
	case '4':{
			_modem->mmiPort()->println(" - speed 175");
			_conveyor->setSpeed(175);
		}
		retVal = true;
		break;
	case '5':{
			_modem->mmiPort()->println(" - speed 255");
			_conveyor->setSpeed(255);
		}
		retVal = true;
		break;
	case '9':{
			_modem->mmiPort()->println(_conveyor->readHalls());
		}
		retVal = true;
		break;
	}
	return retVal;
}

ConveyorUI::~ConveyorUI() {
	// TODO Auto-generated destructor stub
}

