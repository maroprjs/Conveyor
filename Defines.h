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
#define RED_PIN CONTROLLINO_R6
#define YELLOW_PIN CONTROLLINO_R7
#define GREEN_PIN CONTROLLINO_R8
#define BUZZER_PIN CONTROLLINO_R9
#define MINI_CONV_YELLOW_PIN CONTROLLINO_R5 //yellow light as replacement when no industrial is available

//nfc
#define PN532_SCK  (3)
#define PN532_MOSI (4)
#define PN532_SS   (5)
#define PN532_MISO (6)

//infrared sensor
#define IR_SENSOR_PIN CONTROLLINO_IN0

//IP related
#define OWN_IP 10, 200, 20, 161
#define UDP_SERVER_IP 10, 200, 20, 160 //application server f�r e.g. GUI to send status information
#define UDP_SERVER_PORT 5555
#define MAC_ADDRESS { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }
#define LOCAL_UDP_PORT 3333



#endif /* DEFINES_H_ */
