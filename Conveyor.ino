
/**
 *  @file		Conveyor.ino
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
#include "Conveyor.h"
#include "SignalLight.h"
#include "NfcReader.h"
#include "InfraredSensor.h"
#include "ConveyorUI.h"
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
 * Conveyor
 */
Conveyor conveyor(ELECTRONICS_PWR_PIN, MOTOR_PWR_PIN, SPEED_PIN, HALL_SENSOR_PIN, FORWARD_PIN, REVERSE_PIN );

/*************************************************************
 * Signal Light Tower
 */
SignalLight signalLight(RED_PIN, YELLOW_PIN, GREEN_PIN, BUZZER_PIN, MINI_CONV_YELLOW_PIN);

/*************************************************************
 * NFC Reader
 */
NfcReader nfcReader; //pins defined in NfcReader.h

/*************************************************************
 * Infrared Sensor
 */
InfraredSensor irSensor(IR_SENSOR_PIN, &conveyor);


/*************************************************************
 * ConveyorUI
 */
ConveyorUI conveyorUI(&modem, &conveyor, &signalLight, &nfcReader, &irSensor);




//////  The Arduino way ///////////////////
void setup()
{
	Serial.begin(9600);
	delay(100);
	modem.begin();
	conveyor.begin();
	signalLight.begin();
	nfcReader.begin();
	irSensor.begin();
	conveyorUI.begin();


}

// The loop function is called in an endless loop
void loop()
{
    modem.loop();
	irSensor.loop();//keep this one before conveyor loop
	conveyor.loop();
	signalLight.loop();
	nfcReader.loop();
	conveyorUI.loop();
}


