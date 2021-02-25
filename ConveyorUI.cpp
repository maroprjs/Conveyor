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
		//Serial.println(_msg);
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
	case 'a':{
			serialMMI('e');
	    	serialMMI('m');
	    	serialMMI('5');
		}
		retVal = true;
		break;
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
	case 'f':{
			_modem->mmiPort()->println(" - forward switch");
			_conveyor->moveForwardReq();

		}
		retVal = true;
		break;
	case 'r':{
			_modem->mmiPort()->println(" - reverse switch");
			_conveyor->moveReverseReq();
		}
		retVal = true;
		break;
	case 'o':{
			_modem->mmiPort()->println(" - turn off");
			_conveyor->setSpeed(0);
			_conveyor->pwrOffReq();
		}
		retVal = true;
		break;
	case '0':{
			_modem->mmiPort()->println(" - speed 0");
			_conveyor->setSpeed(0); //stops with value 10, but offset added in setSpeed function
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
			_modem->mmiPort()->println(" - speed 50");
			_conveyor->setSpeed(50);
		}
		retVal = true;
		break;

	case '3':{
			_modem->mmiPort()->println(" - speed 85");
			_conveyor->setSpeed(85);
		}
		retVal = true;
		break;
	case '4':{
			_modem->mmiPort()->println(" - speed 110");
			_conveyor->setSpeed(110);
		}
		retVal = true;
		break;
	case '5':{
			_modem->mmiPort()->println(" - speed 135");
			_conveyor->setSpeed(135);
		}
		retVal = true;
		break;
	case '6':{
			_modem->mmiPort()->println(" - speed 160");
			_conveyor->setSpeed(160);
		}
		retVal = true;
		break;
	case '7':{
			_modem->mmiPort()->println(" - speed 185");
			_conveyor->setSpeed(185);
		}
		retVal = true;
		break;
	case '8':{
			_modem->mmiPort()->println(" - speed 210");
			_conveyor->setSpeed(210);
		}
		retVal = true;
		break;
	case '9':{
			_modem->mmiPort()->println(" - speed 255");
			_conveyor->setSpeed(255);
		}
		retVal = true;
		break;
	}
	return retVal;
}

ConveyorUI::~ConveyorUI() {
	// TODO Auto-generated destructor stub
}

