/*
 * NfcReader.h
 *
 *  Created on: 26 Aug 2021
 *      Author: pionet
 */

#ifndef NFCREADER_H_
#define NFCREADER_H_

#include <Adafruit_PN532.h>
#include "Defines.h" //for pins


#define DEBOUNCE_TIME 1000

class NfcReader {
public:
	NfcReader(uint8_t nfcReaderId,uint8_t sckPin,uint8_t misoPin,uint8_t mosiPin,uint8_t ssPin);
	void begin();
	void loop();
	bool isNewTagToPublish();
	unsigned int getTagId();
	virtual ~NfcReader();
private:
	Adafruit_PN532* _nfc;
	bool _readerConnected;
	bool _tagRecognized;
	uint8_t* _uid;
	uint8_t* _uidLength;
	uint32_t _lastTagTimstamp;
	uint8_t _nfcReaderId;
	uint8_t _sckPin;
	uint8_t _misoPin;
	uint8_t _mosiPin;
	uint8_t _ssPin;
	bool _newTagToPublish;

};

#endif /* NFCREADER_H_ */
