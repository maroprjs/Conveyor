/*
 * ConveyorDefines.h
 *
 *  Created on: 29 Jan 2022
 *      Author: pionet
 */

#ifndef DEFINES_H_
#define DEFINES_H_

//Motor:
//controllino doesn't set PINs below 0.5V at LOW, as required by Vetter's Faulhaber Motor,
//hence we use two Relais contacts to switch between proper GND and +24V
#define FORWARD_PIN CONTROLLINO_R2
#define REVERSE_PIN CONTROLLINO_R3

#if defined(CONTROLLINO_MAXI_AUTOMATION)
  #define SPEED_PIN CONTROLLINO_AO0 //maxi automation has internal digital to analog converter
#else
  #define SPEED_PIN CONTROLLINO_D1 //maxi (MAXI needs external digital to analog converter)
#endif
#define HALL_SENSOR_PIN CONTROLLINO_IN1
#define MOTOR_PWR_PIN CONTROLLINO_R1
#define ELECTRONICS_PWR_PIN CONTROLLINO_R0

//signal light
#if defined(CONTROLLINO_MAXI_AUTOMATION)
   #define RED_PIN CONTROLLINO_DO2
   #define YELLOW_PIN CONTROLLINO_DO3
   #define GREEN_PIN CONTROLLINO_DO4
   #define BUZZER_PIN CONTROLLINO_R9
#else
   #define RED_PIN CONTROLLINO_D2
   #define YELLOW_PIN CONTROLLINO_D3
   #define GREEN_PIN CONTROLLINO_D4
   #define BUZZER_PIN CONTROLLINO_R9
#endif

//nfc
#define PN532_SCK  (42)
#define PN532_MOSI (43)
#define PN532_SS   (44)
#define PN532_MISO (45)

//infrared sensor
#define IR_SENSOR_PIN CONTROLLINO_IN0

//Buttons
#if defined(CONTROLLINO_MAXI_AUTOMATION)
   #define STARTSTOP_BUTTON_PIN CONTROLLINO_DI0
   #define STARTSTOP_LED_PIN CONTROLLINO_DO5
   #define FWDREV_BUTTON_PIN CONTROLLINO_DI1
   #define FWDREV_LED_PIN  CONTROLLINO_DO6
   #define SPEED_BUTTON_PIN CONTROLLINO_DI2
   #define SPEED_LED_PIN  CONTROLLINO_DO7
   #define EMERGENCY_BUTTON_PIN CONTROLLINO_DI3
   #define ONOFF_SWITCH_PIN CONTROLLINO_AI0
   #define ONOFF_SWITCH_LED_PIN  CONTROLLINO_DO0 //this is dummy, not used! -Instead LED wired to Raspberry
#else
   #define STARTSTOP_BUTTON_PIN CONTROLLINO_D8
   #define STARTSTOP_LED_PIN CONTROLLINO_D5
   #define FWDREV_BUTTON_PIN CONTROLLINO_D9
   #define FWDREV_LED_PIN  CONTROLLINO_D6
   #define SPEED_BUTTON_PIN CONTROLLINO_D10
   #define SPEED_LED_PIN  CONTROLLINO_D7
   #define EMERGENCY_BUTTON_PIN CONTROLLINO_D11
   #define ONOFF_SWITCH_PIN CONTROLLINO_TBD

#endif


//Raspberry button
#define RASPBERRY_ONOFF_BUTTON_PIN CONTROLLINO_R5 //controllino emulates pwr button on raspberry
#define RASPBERRY_FULLPWR_PIN CONTROLLINO_R4 //full usb power cutoff to avoid confusions
#define ONOFF_SENSE_PIN CONTROLLINO_AI9 // checks if is Raspberry on or off?



//IP related
//(NOTE: if you change those values after second upload to controllino, factory reset needs to be done via serial
//-> 'X' -> 'factoryreset' -> 'exit' -> manual reboot)
//#define OWN_IP 10, 200, 20, 161
#define OWN_IP  0,0,0,0 //dhcp
#define UDP_SERVER_IP 10, 200, 20, 160 //application server f�r e.g. GUI to send status information
#define UDP_SERVER_PORT 5555
#define MAC_ADDRESS { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }
#define LOCAL_UDP_PORT 3333

//Memory (EEPROM) related
#define EEPROM_UPDATED 1 //Increase this whenever memory config for EEPROM changes, e.g. additional fields the initial value is 255
#define SERVERPORT_UNITIALIZED 65535
#define IP_UNINITIALIZED 255,255,255,255



#endif /* DEFINES_H_ */
