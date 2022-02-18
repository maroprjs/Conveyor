/*
 * NfcReaderHubUI.cpp
 *
 *  Created on: 3 Feb 2022
 *      Author: pionet
 */

#include "NfcReaderHubUI.h"

NfcReaderHubUI::NfcReaderHubUI(Modem* modem, NfcReader* nfcReader1, NfcReader* nfcReader2, NfcReader* nfcReader3) {
	_modem = modem;
	_nfcReader1 = nfcReader1;
	_nfcReader2 = nfcReader2;
	_nfcReader3 = nfcReader3;
	_elapsedPublishTime = 0;
	_publishInterval = PUBLISH_TIME_INTERVAL_MS;
	_txMsg = new char[UDP_TX_PACKET_MAX_SIZE];

}

void NfcReaderHubUI::begin(){
	_elapsedPublishTime = millis();
}

void NfcReaderHubUI::loop(){

	publishStatus();
}

/*
 * this must be called in loop function
 *
 * protocol fields:
 *   <message ID>,<electronics pwr state on(1)/off(0)>,<motor pwr state on(1)/off(0)>, <forward 1, else 0>, <measured RPM>,<set PWM value 0-255>,
 *   <red Light Status>,<yellow light status>,<green Light Status>
 */
void NfcReaderHubUI::publishStatus(){
	if (_nfcReader1->isNewTagToPublish() || _nfcReader2->isNewTagToPublish() || _nfcReader3->isNewTagToPublish()){
		_elapsedPublishTime = 0; //that will make next if condition true immediately
	};
	if (millis() >= (_elapsedPublishTime + _publishInterval)){
		//build message
		sprintf((char*)_txMsg,"%u,%u,%u,%u", (unsigned int)PUBLISH_MSG_ID, \
											(unsigned int)_nfcReader1->getTagId(), \
											(unsigned int)_nfcReader2->getTagId(), \
											(unsigned int)_nfcReader3->getTagId());
		_modem->sendUdpMsg(_txMsg);
		_elapsedPublishTime = millis();
	}
}


NfcReaderHubUI::~NfcReaderHubUI() {
	// TODO Auto-generated destructor stub
}

