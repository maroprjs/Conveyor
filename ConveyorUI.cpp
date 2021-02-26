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
	_rxMsg = new char[UDP_TX_PACKET_MAX_SIZE];
	_txMsg = new char[UDP_TX_PACKET_MAX_SIZE];
	_elapsedPublishTime = 0;
	_publishInterval = PUBLISH_TIME_INTERVAL_MS;

}

void ConveyorUI::begin(){
	_elapsedPublishTime = millis();
}

void ConveyorUI::loop(){
	if (_modem->msgArrived()){
		_modem->readMsg(_rxMsg);
		//Serial.println(_rxMsg);
		serialMMI(_rxMsg[0]);
	}
	while(_modem->mmiPort()->available()){
		char cmd = _modem->mmiPort()->read();
		_modem->mmiPort()->flush();
		serialMMI(cmd);
	}
	publishStatus();
}


/****************************
 *
 *  e - (e)lectronics on
 *  m - (m)otor on
 *  a - (a)ll on; electronics and motor on with middle speed (and forward dierction at first start after PLC power)
 *  0...9 - speed levels, where '0' has no movement and '9' the max speed
 *  r - (r)everse direction of conveyor (resumes same speed as before) - away from cam
 *  f - (f)orward direction of conveyor (resumes same speed as before) - this is towards camera
 *  o - (o)ff, sets speed to zero and turns off motor power and electronics
 *
 */
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
	case 'x':{
			_modem->mmiPort()->println(" - turn off elec");
	    	_conveyor->electronicsPwrOffReq();
		}
		retVal = true;
		break;
	case 'm':{
			_modem->mmiPort()->println(" - turn on motor");
			_conveyor->motorPwrOnReq();
		}
		retVal = true;
		break;
	case 'z':{
			_modem->mmiPort()->println(" - turn off motor");
			_conveyor->motorPwrOffReq();
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
	case 'p':{
			_modem->mmiPort()->println(" - publish status");
			publishStatus();
		}
		retVal = true;
		break;
	}
	return retVal;
}

/*
 * this must be called in loop function
 *
 * protocol fields:
 *   <electronics pwr state on(1)/off(0)>,<motor pwr state on(1)/off(0)>, <forward 1, else 0>, <measured RPM>,<set PWM value 0-255>
 *
 */
void ConveyorUI::publishStatus(){
	if (millis() >= (_elapsedPublishTime + _publishInterval)){
		//build message
		sprintf((char*)_txMsg,"%u,%u,%u,%u,%u",(unsigned int)_conveyor->isElectronicsPwrOn(), \
											(unsigned int)_conveyor->isMotorPwrOn(), \
											(unsigned int)_conveyor->isForward(), \
											(unsigned int)_conveyor->readRPM(), \
											(unsigned int)_conveyor->readSpeed());
		_modem->sendUdpMsg(_txMsg);
		_elapsedPublishTime = millis();
	}
}

ConveyorUI::~ConveyorUI() {
	// TODO Auto-generated destructor stub
}

