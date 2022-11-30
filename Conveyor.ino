
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
#include "LEDButton.h"
#include "ConveyorUI.h"
#include "Defines.h"
#include "Memory.h"
#include "Raspberry.h"

/////////defines //////////////////////

//defines moved to ConveyorDefines.h

////////// Object Instantiation //////////////////
/*************************************************************
 * Memory - storage for c0onfiguration (e.g. IP addresses) on EEPROM
 */
Memory memory;


/*************************************************************
 * modem - local MMI represented by serial interface, WebUI by server IP and port
 */
Modem modem(&Serial,&memory);


/*************************************************************
 * Conveyor
 */
Conveyor conveyor(ELECTRONICS_PWR_PIN, MOTOR_PWR_PIN, SPEED_PIN, HALL_SENSOR_PIN, FORWARD_PIN, REVERSE_PIN );

/*************************************************************
 * Signal Light Tower or status lights
 */
SignalLight signalLight(RED_PIN, YELLOW_PIN, GREEN_PIN, BUZZER_PIN);

/*************************************************************
 * NFC Reader
 */
NfcReader nfcReader; //pins defined in NfcReader.h

/*************************************************************
 * Infrared Sensor
 */
InfraredSensor irSensor(IR_SENSOR_PIN, &conveyor);


/*************************************************************
 * Start/Stop Button
 */
LEDButton startStopButton(STARTSTOP_BUTTON_PIN, STARTSTOP_LED_PIN);


/*************************************************************
 * FWD/REV Button
 */
LEDButton fwdRevButton(FWDREV_BUTTON_PIN, FWDREV_LED_PIN);

/*************************************************************
 * Speed Button
 */
LEDButton speedButton(SPEED_BUTTON_PIN, SPEED_LED_PIN);

/*************************************************************
 * Emergency Button
 */
LEDButton emergButton(EMERGENCY_BUTTON_PIN, RED_PIN);

/*************************************************************
 * ON OFF Switch for Raspberry
 */
LEDButton onOffSwitch(ONOFF_SWITCH_PIN, ONOFF_SWITCH_LED_PIN);


/*************************************************************
 * Raspberry -exposes the on-off button-
 */
Raspberry raspberry(RASPBERRY_ONOFF_BUTTON_PIN,ONOFF_SENSE_PIN, RASPBERRY_FULLPWR_PIN);



/*************************************************************
 * ConveyorUI
 */
ConveyorUI conveyorUI(&modem, &conveyor, &signalLight, &nfcReader, &irSensor, &startStopButton, &fwdRevButton, &speedButton, &emergButton, &onOffSwitch, &raspberry  );




//////  The Arduino way ///////////////////
void setup()
{
	Serial.begin(9600);
	delay(100);
	memory.begin();
	modem.begin();
	conveyor.begin();
	signalLight.begin();
	nfcReader.begin();
	irSensor.begin();
	startStopButton.begin();
	fwdRevButton.begin();
	speedButton.begin();
	emergButton.begin();
	onOffSwitch.begin();
	raspberry.begin();
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
	startStopButton.loop();
	fwdRevButton.loop();
	speedButton.loop();
	emergButton.loop();
	onOffSwitch.loop();
	raspberry.loop();
	conveyorUI.loop();
}


