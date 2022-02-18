/*
 * NfcReader.cpp
 *
 *  Created on: 26 Aug 2021
 *      Author: pionet
 */

#include "NfcReader.h"


NfcReader::NfcReader(uint8_t nfcReaderId, uint8_t sckPin,uint8_t misoPin,uint8_t mosiPin,uint8_t ssPin) {
	_nfcReaderId =  nfcReaderId;
	_sckPin = sckPin;
	_misoPin = misoPin;
	_mosiPin = mosiPin;
	_ssPin = ssPin;
	_nfc = new Adafruit_PN532(_sckPin,_misoPin,_mosiPin, _ssPin);
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
		Serial.print("Didn't find PN53x board ");Serial.println(_nfcReaderId);
	}else{





		Serial.print("PN53x board ");Serial.print(_nfcReaderId);Serial.println(" found ");
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
  if (_readerConnected){
  	if (millis() > _lastTagTimstamp + DEBOUNCE_TIME){
  		_tagRecognized = _nfc->readPassiveTargetID(PN532_MIFARE_ISO14443A, _uid, _uidLength);
  		if (_tagRecognized == true) {
  			Serial.print("Found a card ID: "); Serial.println(_uid[1]);//enough to report second byte!!
  			_newTagToPublish = true;
  			_lastTagTimstamp = millis();
  
  		}
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
