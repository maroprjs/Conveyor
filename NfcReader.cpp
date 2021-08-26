/*
 * NfcReader.cpp
 *
 *  Created on: 26 Aug 2021
 *      Author: pionet
 */

#include "NfcReader.h"


NfcReader::NfcReader() {
	// TODO Auto-generated constructor stub
	_nfc = new Adafruit_PN532(PN532_SCK, PN532_MISO, PN532_MOSI, PN532_SS);
	_readerConnected = false;
	_tagRecognized = false;
	_uid = new uint8_t[7];
	_uidLength = new uint8_t;
	_lastTagTimstamp = 0;
	_newTagToPublish = false;


}

void NfcReader::begin(){
	_nfc->begin();
	uint32_t versiondata = _nfc->getFirmwareVersion();
	if (! versiondata) {
		Serial.println("Didn't find PN53x board");
	}else{
		_readerConnected = true;
		// Set the max number of retry attempts to read from a card
		// This prevents us from waiting forever for a card, which is
		// the default behaviour of the PN532.
		_nfc->setPassiveActivationRetries(0x0A); //default was FF

		// configure board to read RFID tags
		_nfc->SAMConfig();
	}

}
void NfcReader::loop(){
	if (millis() > _lastTagTimstamp + DEBOUNCE_TIME){
		_tagRecognized = _nfc->readPassiveTargetID(PN532_MIFARE_ISO14443A, _uid, _uidLength);
		if (_tagRecognized) {
			Serial.print("Found a card ID: "); Serial.println(_uid[1]);//enough to report second byte!!
			_newTagToPublish = true;
			_lastTagTimstamp = millis();

		}
	}


}

bool NfcReader::isNewTagToPublish(){
	return _newTagToPublish;
}
unsigned int NfcReader::getTagId(){
	unsigned int retVal = 0;
	if (_newTagToPublish){
		retVal = _uid[1]; //enough to report second byte!!
		_newTagToPublish = false;
	};
	return retVal;
}

NfcReader::~NfcReader() {
	// TODO Auto-generated destructor stub
}

