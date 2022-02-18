/*
 * NfcReaderHubUI.h
 *
 *  Created on: 3 Feb 2022
 *      Author: pionet
 */

#ifndef NFCREADERHUBUI_H_
#define NFCREADERHUBUI_H_
#include "Modem.h"
#include "NfcReader.h"
#define PUBLISH_TIME_INTERVAL_MS 1000
#define PUBLISH_MSG_ID 2

class NfcReaderHubUI {
public:
	NfcReaderHubUI(Modem* modem, NfcReader* nfcReader1, NfcReader* nfcReader2, NfcReader* nfcReader3);
	void begin();
	void loop();
	virtual ~NfcReaderHubUI();
private:
	void publishStatus();
private:
	Modem* _modem;
	NfcReader* _nfcReader1;
	NfcReader* _nfcReader2;
	NfcReader* _nfcReader3;
	uint32_t _elapsedPublishTime;
	uint32_t _publishInterval;
	char* _txMsg;


};

#endif /* NFCREADERHUBUI_H_ */
