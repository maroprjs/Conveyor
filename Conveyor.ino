
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
#define DIRECTION_PIN CONTROLLINO_D2
#define SPEED_PIN CONTROLLINO_D1
#define HALL_SENSOR_PIN CONTROLLINO_D3
#define MOTOR_PWR_PIN CONTROLLINO_R1
#define ELECTRONICS_PWR_PIN CONTROLLINO_R0

////////// Object Instantiation //////////////////
/*************************************************************
 * modem - local MMI represented by serial interface, WebUI by server IP and port
 */
IPAddress serverIP(10, 200, 20, 160);
uint16_t serverPort = 5555;

Modem modem(&Serial, serverIP, serverPort);


/*************************************************************
 * Conveyor
 */
Conveyor conveyor(ELECTRONICS_PWR_PIN, MOTOR_PWR_PIN, SPEED_PIN, DIRECTION_PIN, HALL_SENSOR_PIN );

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


