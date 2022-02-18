/*
 * Defines.h
 *
 *  Created on: 3 Feb 2022
 *      Author: pionet
 */

#ifndef DEFINES_H_
#define DEFINES_H_

//nfc
//#define PN532_SCK  (15)
//#define PN532_MISO (14)
//#define PN532_MOSI (13)
//#define PN532_SS_3   (12)
//#define PN532_SS_2   (11)
//#define PN532_SS_1   (10)
#define PN532_SCK_1  (7)
#define PN532_MISO_1 (6)
#define PN532_MOSI_1 (5)
#define PN532_SS_1   (4)

#define PN532_SCK_2  (13)
#define PN532_MISO_2 (12)
#define PN532_MOSI_2 (11)
#define PN532_SS_2   (10)

#define PN532_SCK_3  (45)
#define PN532_MISO_3 (44)
#define PN532_MOSI_3 (43)
#define PN532_SS_3   (42)

//IP related
#define OWN_IP 10, 200, 20, 162
#define UDP_SERVER_IP 10, 200, 20, 160 //application server f�r e.g. GUI to send status information
#define UDP_SERVER_PORT 5555
#define MAC_ADDRESS { 0xDE, 0xAD, 0xDE, 0xEF, 0xFE, 0xED }
#define LOCAL_UDP_PORT 3333

#endif /* DEFINES_H_ */
