/*
 * Modem.h
 *
 *  Created on: 14 Feb 2021
 *      Author: pionet
 */

#ifndef MODEM_H_
#define MODEM_H_
#include "Arduino.h"
#include <Controllino.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#define MAC_ADDRESS { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }
#define LOCAL_UDP_PORT 3333


class Modem {

public:
	Modem(HardwareSerial* mmiPort, IPAddress serverIP, uint16_t serverPort);
	void begin();
	void loop();
	HardwareSerial* mmiPort() {return _mmiPort;};
	bool msgArrived();
	void readMsg(char* msg);
	virtual ~Modem();
private:
	IPAddress _serverIP;
	uint16_t _serverPort;
	HardwareSerial* _mmiPort;
	EthernetUDP* _udp;
	static byte _mac[6];
	unsigned int _localPort;
	int _packetSize;
	//char* _packetBuffer;

};

#endif /* MODEM_H_ */
