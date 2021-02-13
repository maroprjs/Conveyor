
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
#include "Conveyor.h"
#include <Ethernet.h>
#include <EthernetUdp.h>

/////////defines //////////////////////
#define DIRECTION_PIN CONTROLLINO_D2
#define SPEED_PIN CONTROLLINO_D1
#define HALL_SENSOR_PIN CONTROLLINO_D3
#define MOTOR_PWR_PIN CONTROLLINO_R1
#define ELECTRONICS_PWR_PIN CONTROLLINO_R0


////////// Object Istantiation //////////////////
/*************************************************************
 * Conveyor
 */
Conveyor conveyor(ELECTRONICS_PWR_PIN, MOTOR_PWR_PIN, SPEED_PIN, DIRECTION_PIN, HALL_SENSOR_PIN );


/*************************************************************
 * UI - represented by serial interface
 */
HardwareSerial* ui;


//////  The Arduino way ///////////////////
void setup()
{
	Serial.begin(9600);
	ui = &Serial;
	//ui->begin(9600);
	conveyor.begin();
}

// The loop function is called in an endless loop
void loop()
{
	while(!Serial.available()){
		conveyor.loop();
	}
	char cmd = Serial.read();
	localUI(cmd);

}

bool localUI(char command){
	bool retVal = false;
	switch (command){
	case 'e':{
		Serial.println("e - turn on elec");
			conveyor.electronicsPwrOnReq();
		}
		retVal = true;
		break;
	case 'm':{
		    Serial.println("m - turn on motor");
			conveyor.motorPwrOnReq();
		}
		retVal = true;
		break;
	case 'o':{
			Serial.println("o - turn off");
			conveyor.pwrOffReq();
		}
		retVal = true;
		break;
	case '0':{
			Serial.println("0 - speed 0");
			conveyor.setSpeed(0);
		}
		retVal = true;
		break;
	case '1':{
			Serial.println("1 - speed 25");
			conveyor.setSpeed(25);
		}
		retVal = true;
		break;
	case '2':{
		    Serial.println("2 - speed 75");
			conveyor.setSpeed(75);
		}
		retVal = true;
		break;

	case '3':{
		Serial.println("3 - speed 125");
			conveyor.setSpeed(125);
		}
		retVal = true;
		break;
	case '4':{
		Serial.println("4 - speed 175");
			conveyor.setSpeed(175);
		}
		retVal = true;
		break;
	case '5':{
		Serial.print("5 - speed 255");
			conveyor.setSpeed(255);
		}
		retVal = true;
		break;
	case '9':{
			Serial.println(conveyor.readHalls());
		}
		retVal = true;
		break;
	}
	return retVal;
}
