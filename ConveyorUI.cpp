/*
 * ConveyorUI.cpp
 *
 *  Created on: 14 Feb 2021
 *      Author: pionet
 */

#include "ConveyorUI.h"

ConveyorUI::ConveyorUI(Modem* modem, Conveyor* conveyor, SignalLight* signalLight, NfcReader* nfcReader, InfraredSensor* irSensor, \
		               LEDButton* startStpBtn, LEDButton* fwdRvsBtn, LEDButton* speedBtn, LEDButton* emergBtn, LEDButton* onOffSwitch, Raspberry* raspberry) {
	_modem = modem;
	_conveyor = conveyor;
	_signalLight = signalLight;
	_nfcReader = nfcReader;
	_irSensor = irSensor;
	_rxMsg = new char[UDP_TX_PACKET_MAX_SIZE];
	_txMsg = new char[UDP_TX_PACKET_MAX_SIZE];
	_elapsedPublishTime = 0;
	_publishInterval = PUBLISH_TIME_INTERVAL_MS;
	_eXtendedUIActive = false;
	_cmdString = "";
	_startStpBtn = startStpBtn;
	_fwdRvsBtn = fwdRvsBtn;
	_speedBtn = speedBtn;
	_emergBtn = emergBtn;
	_onOffSwitch = onOffSwitch;
	_raspberry = raspberry;
	_flipFlop = false;
	_emergencyActive = false;
    _btnStatus.placeholder1 = 0;
    _btnStatus.placeholder2 = 0;
    _btnStatus.placeholder3 = 0;
    _btnStatus.placeholder11 = 0;
    _btnStatus.placeholder12 = 0;
    _btnStatus.placeholder13 = 0;
    _btnStatus.placeholder14 = 0;
    _btnStatus.placeholder15 = 0;
    _btnStatus.placeholder16 = 0;
    _btnStatus.placeholder17 = 0;
    _btnStatus.placeholder18 = 0;
    _extendendedUIParams = NONE;
    _factoryResetRequested = false;
    _factoryResetTime = 0;
    _factoryResetActive = false;


}

void ConveyorUI::begin(){
	if (_onOffSwitch->isActive() == false){
		_raspberry->switchOff();
	}else{
		//_raspberry->switchOn();<-this is not needed since click event is generated in loop
	};
	_elapsedPublishTime = millis();
}

void ConveyorUI::loop(){
	if (_modem->msgArrived()){
        if (_eXtendedUIActive == true){
        	_cmdString = _modem->readMsgUntil('\n');
        	if (_emergencyActive == false) _eXtendedUI(); //don't handle udp requests when emergency is on
        }else{
		   _modem->readMsg(_rxMsg);
		   //Serial.println(_rxMsg);
		   if (_emergencyActive == false) serialMMI(_rxMsg[0]);  //don't handle udp requests when emergency is on
        };
	}
	while(_modem->mmiPort()->available()){
        if (_eXtendedUIActive == true){
        	_cmdString = _modem->mmiPort()->readStringUntil('\n');
        	_eXtendedUI();
        }else{
    		char cmd = _modem->mmiPort()->read();
    		serialMMI(cmd);
        }
		_modem->mmiPort()->flush();
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
		serialMMI('4');
	    serialMMI('m');
	    	
		};
		retVal = true;
		break;
	case 'e':{
			_modem->mmiPort()->println(" - turn on elec");
	    	_conveyor->electronicsPwrOnReq();
		};
		retVal = true;
		break;
	case 'x':{
			_modem->mmiPort()->println(" - turn off elec");
	    	_conveyor->electronicsPwrOffReq();
		};
		retVal = true;
		break;
    case 'X': {
           Serial.println(F("eXtended UI"));
           _eXtendedUIActive = true;
        };
		retVal = true;
        break;
	case 'm':{
		_modem->mmiPort()->println(" - turn on motor");
		_irSensor->disableTemporaly();
		_conveyor->motorPwrOnReq();
		};
		retVal = true;
		break;
	case 'z':{
			_modem->mmiPort()->println(" - turn off motor");
			_conveyor->motorPwrOffReq();
		};
		retVal = true;
		break;
	case 'f':{
			_modem->mmiPort()->println(" - forward switch");
			_conveyor->moveForwardReq();

		};
		retVal = true;
		break;
	case 'r':{
			_modem->mmiPort()->println(" - reverse switch");
			_conveyor->moveReverseReq();
		};
		retVal = true;
		break;
	case 'o':{
			_modem->mmiPort()->println(" - turn off");
			_conveyor->setSpeed(0);
			_conveyor->pwrOffReq();
		};
		retVal = true;
		break;
	case '0':{
			_modem->mmiPort()->print(" - speed "); _modem->mmiPort()->println(_speedMap[0]);
			_conveyor->setSpeed(_speedMap[0]); //stops with value 10, but offset added in setSpeed function
		};
		retVal = true;
		break;
	case '1':{
			//_modem->mmiPort()->println(" - speed 25");
			_modem->mmiPort()->print(" - speed "); _modem->mmiPort()->println(_speedMap[1]);
			_conveyor->setSpeed(_speedMap[1]);
		};
		retVal = true;
		break;
	case '2':{
			//_modem->mmiPort()->println(" - speed 50");
			_modem->mmiPort()->print(" - speed "); _modem->mmiPort()->println(_speedMap[2]);
			_conveyor->setSpeed(_speedMap[2]);
		};
		retVal = true;
		break;

	case '3':{
			//_modem->mmiPort()->println(" - speed 85");
			_modem->mmiPort()->print(" - speed "); _modem->mmiPort()->println(_speedMap[3]);
			_conveyor->setSpeed(_speedMap[3]);
		};
		retVal = true;
		break;
	case '4':{
			//_modem->mmiPort()->println(" - speed 110");
			_modem->mmiPort()->print(" - speed "); _modem->mmiPort()->println(_speedMap[4]);
			_conveyor->setSpeed(_speedMap[4]);
		};
		retVal = true;
		break;
	case '5':{
			//_modem->mmiPort()->println(" - speed 135");
			_modem->mmiPort()->print(" - speed "); _modem->mmiPort()->println(_speedMap[5]);
			_conveyor->setSpeed(_speedMap[5]);
		};
		retVal = true;
		break;
	case '6':{
			//_modem->mmiPort()->println(" - speed 160");
			_modem->mmiPort()->print(" - speed "); _modem->mmiPort()->println(_speedMap[6]);
			_conveyor->setSpeed(_speedMap[6]);
		};
		retVal = true;
		break;
	case '7':{
			//_modem->mmiPort()->println(" - speed 185");
			_modem->mmiPort()->print(" - speed "); _modem->mmiPort()->println(_speedMap[7]);
			_conveyor->setSpeed(_speedMap[7]);
		};
		retVal = true;
		break;
	case '8':{
			//_modem->mmiPort()->println(" - speed 210");
			_modem->mmiPort()->print(" - speed "); _modem->mmiPort()->println(_speedMap[8]);
			_conveyor->setSpeed(_speedMap[8]);
		};
		retVal = true;
		break;
	case '9':{
			//_modem->mmiPort()->println(" - speed 255");
			_modem->mmiPort()->print(" - speed "); _modem->mmiPort()->println(_speedMap[9]);
			_conveyor->setSpeed(_speedMap[9]);
		};
		retVal = true;
		break;
	case 'p':{
			//_modem->mmiPort()->println(" - publish status"); <-obsolete
			//publishStatus();<-obsolete
		    _modem->mmiPort()->println(" - red light on");
		    _signalLight->redOn();
		};
		retVal = true;
		break;
	case 'q':{
		    _modem->mmiPort()->println(" - red light off");
		    _signalLight->redOff();
		};
		retVal = true;
		break;
	case 'k':{
		    _modem->mmiPort()->println(" - yellow light on");
		    _signalLight->yellowOn();
		};
		retVal = true;
		break;
	case 'l':{
		    _modem->mmiPort()->println(" - yellow light off");
		    _signalLight->yellowOff();
		};
		retVal = true;
		break;
	case 'v':{
		    _modem->mmiPort()->println(" - green light on");
		    _signalLight->greenOn();
		};
		retVal = true;
		break;
	case 'w':{
		    _modem->mmiPort()->println(" - green light off");
		    _signalLight->greenOff();
		};
		retVal = true;
		break;
	case 'b':{
		    _modem->mmiPort()->println(" - buzzer on");
		    _signalLight->buzzerOn();
		};
		retVal = true;
		break;
	case 'c':{
		    _modem->mmiPort()->println(" - buzzer off");
		    _signalLight->buzzerOff();
		};
		retVal = true;
		break;
	};
	return retVal;
};

/*
 * this must be called in loop function
 *
 * protocol fields:
 *   <message ID>,<electronics pwr state on(1)/off(0)>,<motor pwr state on(1)/off(0)>, <forward 1, else 0>, <measured RPM>,<set PWM value 0-255>,
 *   <red Light Status>,<yellow light status>,<green Light Status>
 */
void ConveyorUI::publishStatus(){

	handleNfcActions();
	handleButtonActions();

	if (millis() >= (_elapsedPublishTime + _publishInterval)){

		//flashing lights in extenden UI  mode
		handleSignalLightActions();

		//build message for GUI
		sprintf((char*)_txMsg,"%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u", (unsigned int)PUBLISH_MSG_ID, \
				                            (unsigned int)_conveyor->isElectronicsPwrOn(), \
											(unsigned int)_conveyor->isMotorPwrOn(), \
											(unsigned int)_conveyor->isForward(), \
											(unsigned int)_conveyor->readRPM(), \
											(unsigned int)_conveyor->readSpeed(), \
											(unsigned int)_signalLight->isRedOn(), \
											(unsigned int)_signalLight->isYellowOn(), \
											(unsigned int)_signalLight->isGreenOn(), \
											(unsigned int)_nfcReader->getTagId(), \
											(unsigned int)_irSensor->isObjectDetected(), \
											_btnStatus);
		//Serial.println(_btnStatus);
		_modem->sendUdpMsg(_txMsg);
		_elapsedPublishTime = millis();
	}
}

void ConveyorUI::_eXtendedUI(){
	//_cmdString = _modem->mmiPort()->readStringUntil('\n');
	_cmdString.trim();
	_cmdString.replace(" ", "");
	_cmdString.toLowerCase();
	Serial.println(_cmdString);
	if (_cmdString == "exit") {
		_eXtendedUIActive = false;
		if (_signalLight->isAllLightOn()) _signalLight->allLightOff(); //all status lights flashing to indicate extended UI mode (see below in publishStatus() method)
		Serial.println("exit eXtended UI");
	};
	//if (_cmdString == "thisisatest") Serial.println("THIS IS A TEST");
	switch (_extendendedUIParams){
	   case ExtendendedUIParams::NONE :{
			if (_cmdString == "setownip") _extendendedUIParams = SET_OWN_IP;
			if (_cmdString == "setserverip") _extendendedUIParams = SET_UDPSERVER_IP;
			if (_cmdString == "setserverport") _extendendedUIParams = SET_UDPSERVER_PORT;
			if (_cmdString == "factoryreset") {
				_signalLight->buzzerOn(); //to give audio feedback to user that reset is ongoing
				_factoryResetActive = true;
				_elapsedPublishTime = millis(); //so the buzzer is at least ON for one interval (1 second)
				_modem->_memory->factoryReset();
				_modem->begin();
				_cmdString = "exit";
				_eXtendedUI();
			};

	   };
	   break;
	   case ExtendendedUIParams::SET_OWN_IP :{
		   //Serial.print("set own IP: ");Serial.println(_modem->str2IP(_cmdString));
		   _modem->_memory->ownIP(_modem->str2IP(_cmdString));
		   _extendendedUIParams = NONE;
		   _modem->begin();
		   _cmdString = "exit";
		   _eXtendedUI();

	   };
	   break;
	   case ExtendendedUIParams::SET_UDPSERVER_IP :{
		   _modem->_memory->udpServerIP(_modem->str2IP(_cmdString));
		   _extendendedUIParams = NONE;
		   _modem->begin();
		   _cmdString = "exit";
		   _eXtendedUI();

	   };
	   break;
	   case ExtendendedUIParams::SET_UDPSERVER_PORT :{
		   _modem->_memory->udpServerPort(_cmdString.toInt());
		   _extendendedUIParams = NONE;
		   _modem->begin();
		   _cmdString = "exit";
		   _eXtendedUI();

	   };
	   break;
	}

	_cmdString = "";
};

void ConveyorUI::handleNfcActions(){
	if (_nfcReader->isNewTagToPublish()){
		_elapsedPublishTime = 0; //that will make next if condition true immediately
	};
}

void ConveyorUI::handleButtonActions(){
	bool emergClicked = _emergBtn->isClicked(); //for action
	bool emergActive = _emergBtn->isActive(); //for publish to GUI
	bool emergReleased = _emergBtn->isReleased(); //for action
	bool startStopClicked = _startStpBtn->isClicked();
	bool fwdRvsClicked = _fwdRvsBtn->isClicked();
	bool speedClicked = _speedBtn->isClicked();
	bool onOffSwitchClicked = _onOffSwitch->isClicked();
	bool onOffSwitchReleased = _onOffSwitch->isReleased();
	bool onOffSwitchActive = _onOffSwitch->isActive();
	//Serial.print(emergClicked);	Serial.print(emergActive);	Serial.print(emergReleased);Serial.print(startStopClicked);Serial.print(fwdRvsClicked); \
	//Serial.print(speedClicked);Serial.print(onOffSwitchClicked);Serial.print(_onOffSwitch->isActive());Serial.println(onOffSwitchReleased);
    _btnStatus.emergActive = emergActive;
    _btnStatus.startStopClicked = startStopClicked;
    _btnStatus.fwdRvsClicked = fwdRvsClicked;
    _btnStatus.speedClicked = speedClicked;
    _btnStatus.onOffSwitchActive = onOffSwitchActive;



	/*****
	 * emergency button
	 */
	if (emergClicked == true){
		_conveyor->motorPwrOffReq();
		_conveyor->electronicsPwrOffReq();
		serialMMI('b'); //buzzer on
		//_elapsedPublishTime = 0; //that will make next if condition true immediately, report to GUI <==no need to report immediately, "active" flag reported periodically
	};
	if (emergReleased == true){
		serialMMI('c'); //buzzer off
		_conveyor->electronicsPwrOnReq();
		//_elapsedPublishTime = 0; //that will make next if condition true immediately, report to GUI <==no need to report immediately, "active" flag reported periodically
	};

	/*****
	 * start/stop button for conveyor
	 */
	if (startStopClicked == true){
		if (_conveyor->isMotorPwrOn() == true){
			_conveyor->motorPwrOffReq();
		}else{
			_conveyor->motorPwrOnReq();
		}
		_elapsedPublishTime = 0; //that will make next if condition true immediately, report to GUI
	};

	/*****
	 * forward/reverse button
	 */
	if (fwdRvsClicked == true){
		if (_conveyor->isForward() == true){
			_conveyor->moveReverseReq();
		}else{
			_conveyor->moveForwardReq();
		}
		_elapsedPublishTime = 0; //that will make next if condition true immediately, report to GUI
	};

	/*****
	 * conveyor speed button
	 */
	if (speedClicked == true){
		_conveyor->speedUpDown();
		_elapsedPublishTime = 0; //that will make next if condition true immediately, report to GUI
	};

	/*****
	 * suitcase on/off switch handling for raspberry graceful shutdown
	 */
	if (onOffSwitchClicked == true ){
		_raspberry->switchOn();
	};
	if (onOffSwitchReleased == true){
		_raspberry->switchOff();
	}

	/*****
	 * factory reset combination (start/stop, fwdRev- and speed buttons pressed for 10 secs)
	 */
	if (_startStpBtn->isActive() && _fwdRvsBtn->isActive() && _speedBtn->isActive() == true){
		if (_factoryResetRequested == false){
			_factoryResetTime = millis() + FACTORYRESET_ELAPSE_TIME;
			_factoryResetRequested = true;
		}
	}else{
		_factoryResetRequested = false;
	};
	if ((millis() >= _factoryResetTime) && ( _factoryResetRequested == true)){
		_factoryResetRequested = false;
		_signalLight->buzzerOn(); //to give audio feedback to user that reset is ongoing
		_factoryResetActive = true;
		_elapsedPublishTime = millis(); //so the buzzer is at least ON for one interval (1 second)
        _modem->_memory->factoryReset();
        _modem->begin();
	}

}

void ConveyorUI::handleSignalLightActions(){
	_flipFlop = !_flipFlop;
	if (_eXtendedUIActive == true){ //all status lights flashing to indicate exetnded UI mode
	   if (_flipFlop == true){
		   _signalLight->allLightOn();
	   }
	   else{
		   _signalLight->allLightOff();
	   };
	};
	if (_factoryResetActive == true){
		_factoryResetActive = false;
		_signalLight->buzzerOff();
	};

}

ConveyorUI::~ConveyorUI() {
	// TODO Auto-generated destructor stub
}
