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
#include "Memory.h"
#include "Defines.h"




class Modem {

public:
	Modem(HardwareSerial* mmiPort, Memory* memory);
	void begin();
	void loop();
	HardwareSerial* mmiPort() {return _mmiPort;};
	bool msgArrived();
	void readMsg(char* msg);
	String readMsgUntil(char terminator);
	void sendUdpMsg(char* msg);
	IPAddress str2IP(String str);
	virtual ~Modem();
	Memory* _memory;
private:
	int getIpBlock(int index, String str);
	IPAddress _serverIP;
	IPAddress _ownIP;
	uint16_t _serverPort;
	HardwareSerial* _mmiPort;
	EthernetUDP* _udp;
	static byte _mac[6];
	unsigned int _localPort;
	int _packetSize;
	//char* _packetBuffer;

};

#endif /* MODEM_H_ */
