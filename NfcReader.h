/*
 * NfcReader.h
 *
 *  Created on: 26 Aug 2021
 *      Author: pionet
 */

#ifndef NFCREADER_H_
#define NFCREADER_H_

#include <Adafruit_PN532.h>

#define PN532_SCK  (3)
#define PN532_MOSI (4)
#define PN532_SS   (5)
#define PN532_MISO (6)
#define DEBOUNCE_TIME 500

class NfcReader {
public:
	NfcReader();
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
	bool _newTagToPublish;

};

#endif /* NFCREADER_H_ */
