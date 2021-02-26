
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
#include "ConveyorUI.h"

/////////defines //////////////////////
//controllino doesn't set PINs below 0.5V at LOW, as required by Vetter's Faulhaber Motor,
//hence we use two Relais contacts to switch between proper GND and +24V
#define FORWARD_PIN CONTROLLINO_R2
#define REVERSE_PIN CONTROLLINO_R3

#define SPEED_PIN CONTROLLINO_D1
#define HALL_SENSOR_PIN CONTROLLINO_IN1
#define MOTOR_PWR_PIN CONTROLLINO_R1
#define ELECTRONICS_PWR_PIN CONTROLLINO_R0

#define UDP_SERVER_IP 10, 200, 20, 153 //application server für e.g. GUI to send status information
#define UDP_SERVER_PORT 5555

////////// Object Instantiation //////////////////
/*************************************************************
 * modem - local MMI represented by serial interface, WebUI by server IP and port
 */
IPAddress udpServerIP(UDP_SERVER_IP);
uint16_t udpServerPort = UDP_SERVER_PORT;

Modem modem(&Serial, udpServerIP, udpServerPort);


/*************************************************************
 * Conveyor
 */
Conveyor conveyor(ELECTRONICS_PWR_PIN, MOTOR_PWR_PIN, SPEED_PIN, HALL_SENSOR_PIN, FORWARD_PIN, REVERSE_PIN );

/*************************************************************
 * ConveyorUI
 */
ConveyorUI conveyorUI(&modem, &conveyor);



//////  The Arduino way ///////////////////
void setup()
{
	Serial.begin(9600);
	modem.begin();
	conveyor.begin();
	conveyorUI.begin();

}

// The loop function is called in an endless loop
void loop()
{
    modem.loop();
	conveyor.loop();
	conveyorUI.loop();
}


