/*
 * Modem.cpp
 *
 *  Created on: 14 Feb 2021
 *      Author: pionet
 */

#include "Modem.h"


Modem::Modem(HardwareSerial* mmiPort, Memory* memory){
	_mmiPort = mmiPort;
	_memory = memory;
    _serverIP = UDP_SERVER_IP;
    _ownIP = IPAddress(OWN_IP);
    _serverPort =  UDP_SERVER_PORT;
    _localPort = LOCAL_UDP_PORT;
    //_serverIP = _memory->udpServerIP();
    //_ownIP = _memory->ownIP();
    //_serverPort = _memory->udpServerPort();
    _packetSize = 0;
    //_packetBuffer = new char[UDP_TX_PACKET_MAX_SIZE];
    _udp = new EthernetUDP;
}


byte Modem::_mac[] = MAC_ADDRESS;

void Modem::begin(){
    _serverIP = _memory->udpServerIP();
    Serial.print("serverIP: ");Serial.println(_serverIP);
    _ownIP = _memory->ownIP();
    _serverPort = _memory->udpServerPort();
    Serial.print("serverPort: ");Serial.println(_serverPort);
	if (_ownIP == IPAddress(0,0,0,0)){
		Serial.println(""); Serial.print("dhcp ");
		Ethernet.begin(_mac);
	}else{
		Serial.println(""); Serial.println("static IP ");
		Ethernet.begin(_mac, _ownIP);
	}
	//if (Ethernet.linkStatus() == LinkOFF) { //not working on WIZ 5100
	//    Serial.println("Ethernet cable is not connected.");
	//};
	Serial.println(Ethernet.localIP());
	_udp->begin(_localPort);
}

void Modem::loop(){
	 /* int packetSize = Udp.parsePacket();
	  if (packetSize) {
	    Serial.print("Received packet of size ");
	    Serial.println(packetSize);
	    Serial.print("From ");
	    IPAddress remote = Udp.remoteIP();
	    for (int i=0; i < 4; i++) {
	      Serial.print(remote[i], DEC);
	      if (i < 3) {
	        Serial.print(".");
	      }
	    }
	    Serial.print(", port ");
	    Serial.println(Udp.remotePort());

	    // read the packet into packetBufffer
	    Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
	    Serial.println("Contents:");
	    Serial.println(packetBuffer);*/
	//delay(1000);
	//Serial.println("...hatschio");
	//Serial.println(_serverIP);
	//_udp->beginPacket(_serverIP, _serverPort);
	//_udp->write("test");
	//_udp->endPacket();

}

bool Modem::msgArrived(){
   bool retVal = false;
   _packetSize = _udp->parsePacket();
   retVal = (_packetSize > 0) ? true : false;
   return retVal;
}

void Modem::readMsg(char* msg){
   _udp->read(msg, UDP_TX_PACKET_MAX_SIZE);
}

String Modem::readMsgUntil(char terminator){
   String msg = _udp->readStringUntil(terminator);
   return msg;
}


void Modem::sendUdpMsg(char* msg){
	Serial.print("tx udp: "); Serial.println(msg);
	_udp->beginPacket(_serverIP, _serverPort);
	_udp->write(msg);
	_udp->endPacket();
}

IPAddress Modem::str2IP(String str) {

    IPAddress ret( getIpBlock(0,str),getIpBlock(1,str),getIpBlock(2,str),getIpBlock(3,str) );
    return ret;

}

int Modem::getIpBlock(int index, String str) {
    char separator = '.';
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = str.length()-1;

    for(int i=0; i<=maxIndex && found<=index; i++){
      if(str.charAt(i)==separator || i==maxIndex){
          found++;
          strIndex[0] = strIndex[1]+1;
          strIndex[1] = (i == maxIndex) ? i+1 : i;
      }
    }

    return found>index ? str.substring(strIndex[0], strIndex[1]).toInt() : 0;
}

Modem::~Modem() {
	// TODO Auto-generated destructor stub
}

