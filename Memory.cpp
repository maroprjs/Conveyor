/*
 * Memory.cpp
 *
 *  Created on: 26 Nov 2022
 *      Author: pionet
 */

#include "Memory.h"
#include <EEPROM.h>
#include "Defines.h"

Memory::Memory() {
	// TODO Auto-generated constructor stub

}

void Memory::begin(){
	//factoryReset();
	uint8_t initFlag = EEPROM.read(INIT_FLAG_EE_ADDR);
	Serial.println("");Serial.println(initFlag);
	if (initFlag != EEPROM_UPDATED){
		Serial.println("");Serial.print("Memory update required, initializing to default...");
		EEPROM.write(INIT_FLAG_EE_ADDR, EEPROM_UPDATED);Serial.print(".");
		if (ownIP() == IPAddress(IP_UNINITIALIZED)) ownIP(IPAddress(OWN_IP));Serial.print(".");
		if (udpServerIP() == IPAddress(IP_UNINITIALIZED)) udpServerIP(IPAddress(UDP_SERVER_IP));Serial.print(".");
		if (udpServerPort() == SERVERPORT_UNITIALIZED) udpServerPort(UDP_SERVER_PORT);Serial.print(".");
		Serial.println("Memory updated!");
	};
	//Serial.println(EEPROM.read(0));
	//Serial.println(EEPROM.length());
}

void Memory::ownIP(IPAddress ip){
	EEPROM.put(OWNIP_EE_ADDR, ip);
}

IPAddress Memory::ownIP(){
	IPAddress ip;
	EEPROM.get(OWNIP_EE_ADDR, ip);
	return ip;
}

void Memory::udpServerIP(IPAddress ip){
	EEPROM.put(UDP_SERVER_IP_EE_ADDR, ip);
}

IPAddress Memory::udpServerIP(){
	IPAddress ip;
	EEPROM.get(UDP_SERVER_IP_EE_ADDR, ip);
	return ip;
}

void Memory::udpServerPort(serverPort_t port){
	EEPROM.put(UDP_SERVER_PORT_EE_ADDR, port);
}

serverPort_t Memory::udpServerPort(){
	serverPort_t port;
	EEPROM.get(UDP_SERVER_PORT_EE_ADDR, port);
	return port;
}

void Memory::factoryReset(){
	unsigned int eeLength = USED_EE_SPACE; //EEPROM.length();
	Serial.print("Resetting Memory, size to be cleaned: ");Serial.print(eeLength);
	for (unsigned int i = 0; i <= eeLength; i++){
		EEPROM.write(i, 255);
	};
	begin();
}

Memory::~Memory() {
	// TODO Auto-generated destructor stub
}

