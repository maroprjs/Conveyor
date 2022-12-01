/*
 * Memory.h
 *
 *  Created on: 26 Nov 2022
 *      Author: MARO
 */

#ifndef MEMORY_H_
#define MEMORY_H_
#include "Arduino.h"
#include <Ethernet.h>




//Memory map:
#define INIT_FLAG_EE_ADDR		0 // uint8_t - 1 byte
#define OWNIP_EE_ADDR 			1 // IPAddress - 6 bytes
#define UDP_SERVER_IP_EE_ADDR		7 //sizeof IPADDRESS = 6 bytes
#define UDP_SERVER_PORT_EE_ADDR	13//sizeof uint16_t - 2 bytes
#define USED_EE_SPACE 15

//This put-method requires EEPROM to be initialzed properly, otherwise Controllino gets stuck at startup:
//struct EEMemConfig{
//	uint8_t initFlag;
//	IPAddress ownIP;
//	IPAddress udpServerIP;
//	uint16_t udpServerPort;
//};

typedef uint16_t serverPort_t;

class Memory {
public:
	Memory();
	void begin(void);
	IPAddress ownIP();
	void ownIP(IPAddress);
	IPAddress udpServerIP();
	void udpServerIP(IPAddress);
	serverPort_t udpServerPort();
	void udpServerPort(serverPort_t);
	void factoryReset();
	virtual ~Memory();
};

#endif /* MEMORY_H_ */
