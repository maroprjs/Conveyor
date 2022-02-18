/*
 * ConveyorUI.cpp
 *
 *  Created on: 14 Feb 2021
 *      Author: pionet
 */

#include "ConveyorUI.h"

ConveyorUI::ConveyorUI(Modem* modem, Conveyor* conveyor, SignalLight* signalLight, NfcReader* nfcReader, InfraredSensor* irSensor) {
	_modem = modem;
	_conveyor = conveyor;
	_signalLight = signalLight;
	_nfcReader = nfcReader;
	_irSensor = irSensor;
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
 *  a - (a)ll on; electronics and motor on with middle speed (and forward dierction at first start after PLC power)
 *  e - (e)lectronics on
 *  x - turn electronics power off
 *  m - (m)otor on
 *  z - turn motor power off
 *  f - (f)orward direction of conveyor (resumes same speed as before) - this is towards camera
 *  r - (r)everse direction of conveyor (resumes same speed as before) - away from cam
 *  o - (o)ff, sets speed to zero and turns off motor power and electronics
 *  0...9 - speed levels, where '0' has no movement and '9' the max speed
 *  p - (p)unainen on = red on
 *  q - red off
 *  k - (k)eltainen on = yellow on
 *  l - yellow off
 *  v - (v)ihrea on = green on
 *  w - green off
 *  b - buzzer on
 *  c - bozzer off
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
			//_modem->mmiPort()->println(" - publish status"); <-obsolete
			//publishStatus();<-obsolete
		    _modem->mmiPort()->println(" - red light on");
		    _signalLight->redOn();
		}
		retVal = true;
		break;
	case 'q':{
		    _modem->mmiPort()->println(" - red light off");
		    _signalLight->redOff();
		}
		retVal = true;
		break;
	case 'k':{
		    _modem->mmiPort()->println(" - yellow light on");
		    _signalLight->yellowOn();
		}
		retVal = true;
		break;
	case 'l':{
		    _modem->mmiPort()->println(" - yellow light off");
		    _signalLight->yellowOff();
		}
		retVal = true;
		break;
	case 'v':{
		    _modem->mmiPort()->println(" - green light on");
		    _signalLight->greenOn();
		}
		retVal = true;
		break;
	case 'w':{
		    _modem->mmiPort()->println(" - green light off");
		    _signalLight->greenOff();
		}
		retVal = true;
		break;
	case 'b':{
		    _modem->mmiPort()->println(" - buzzer on");
		    _signalLight->buzzerOn();
		}
		retVal = true;
		break;
	case 'c':{
		    _modem->mmiPort()->println(" - buzzer off");
		    _signalLight->buzzerOff();
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
 *   <message ID>,<electronics pwr state on(1)/off(0)>,<motor pwr state on(1)/off(0)>, <forward 1, else 0>, <measured RPM>,<set PWM value 0-255>,
 *   <red Light Status>,<yellow light status>,<green Light Status>
 */
void ConveyorUI::publishStatus(){
	if (_nfcReader->isNewTagToPublish()){
		_elapsedPublishTime = 0; //that will make next if condition true immediately
	};
	if (millis() >= (_elapsedPublishTime + _publishInterval)){
		//build message
		sprintf((char*)_txMsg,"%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u", (unsigned int)PUBLISH_MSG_ID, \
				                            (unsigned int)_conveyor->isElectronicsPwrOn(), \
											(unsigned int)_conveyor->isMotorPwrOn(), \
											(unsigned int)_conveyor->isForward(), \
											(unsigned int)_conveyor->readRPM(), \
											(unsigned int)_conveyor->readSpeed(), \
											(unsigned int)_signalLight->isRedOn(), \
											(unsigned int)_signalLight->isYellowOn(), \
											(unsigned int)_signalLight->isGreenOn(), \
											(unsigned int)_nfcReader->getTagId(), \
											(unsigned int)_irSensor->isObjectDetected());
		_modem->sendUdpMsg(_txMsg);
		_elapsedPublishTime = millis();
	}
}

ConveyorUI::~ConveyorUI() {
	// TODO Auto-generated destructor stub
}

