
/**
 *  @file		NfcReaderHubr.ino
 *
 *  @author		maro
 *  @date		mm/dd/yyyy
 *  @version	x.y
 *
 *  @brief 		Main
 *
 *  @section DESCRIPTION
 *
 *  Instantiation and control of objects integrated in Conveyor IND21
 *
 */

/////////// Includes /////////////////
#include "Arduino.h"
#include <Controllino.h>
#include "Modem.h"
#include "NfcReader.h"
#include "NfcReaderHubUI.h"
#include "Defines.h"


/////////defines //////////////////////

//defines moved to ConveyorDefines.h

////////// Object Instantiation //////////////////
/*************************************************************
 * modem - local MMI represented by serial interface, WebUI by server IP and port
 */
IPAddress udpServerIP(UDP_SERVER_IP);
IPAddress ownIP(OWN_IP);
uint16_t udpServerPort = UDP_SERVER_PORT;

Modem modem(&Serial, udpServerIP, udpServerPort, ownIP);


/*************************************************************
 * NFC Reader
 */

NfcReader nfcReader1(1/*nfcReaderId*/,PN532_SCK_1,PN532_MISO_1,PN532_MOSI_1,PN532_SS_1); //other pins defined in Defines.h
NfcReader nfcReader2(2,PN532_SCK_2,PN532_MISO_2,PN532_MOSI_2,PN532_SS_2); //other pins defined in Defines.h
NfcReader nfcReader3(3,PN532_SCK_3,PN532_MISO_3,PN532_MOSI_3,PN532_SS_3); //other pins defined in Defines.h

/*************************************************************
 * NfcReaderHubUI
 */
NfcReaderHubUI nfcReaderHubUI(&modem, &nfcReader1, &nfcReader2, &nfcReader3);

enum NfcReaderCallState{
  READER1,
  READER2,
  READER3,
  MODEM
};

#define DELAY_BETWEEN_NFC 100
NfcReaderCallState nextReader = READER1;
unsigned long nfcLastChecked;


//////  The Arduino way ///////////////////
void setup()
{
	Serial.begin(9600);
	delay(100);
	modem.begin();
	nfcReader1.begin();
	nfcReader2.begin();
	nfcReader3.begin();
	nfcReaderHubUI.begin();
  nfcLastChecked = millis();


}

// The loop function is called in an endless loop
void loop()
{
    modem.loop();
    if (millis() > nfcLastChecked + DELAY_BETWEEN_NFC){
      if (nextReader == READER1){
        nfcReader1.loop();
        nextReader = READER2;
      }
      if (nextReader == READER2){
        nfcReader2.loop();
        nextReader = READER3;
      }
      if (nextReader == READER3){
        nfcReader3.loop();
        nextReader = MODEM;
      }
      if (nextReader == MODEM){
        nfcReaderHubUI.loop();
        nextReader = READER1;
      }

      nfcLastChecked = millis();
    };
}

