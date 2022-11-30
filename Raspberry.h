/*
 * Raspberry.h
 *
 *  Created on: 29 Nov 2022
 *      Author: pionet
 */

#ifndef RASPBERRY_H_
#define RASPBERRY_H_
#include "Arduino.h"

#define BTN_PRESS_TIME 500 //[ms]
#define TIME_FOR_GRACEFULL_SHUTDOWN 20000 //[ms]
#define TIME_TO_STARTUP 40000 //[ms] //give it some time, in case on/off switch released before raspberry is properly started

class Raspberry {
public:
	Raspberry(uint8_t buttonPin, uint8_t sensePin, uint8_t fullPwrPin);
	void begin();
	void loop();
	void switchOn(); //raspberry turns on
	void switchOff(); //graceful shutdown of raspberry and power supply will be cutoff afterwards
	void fullPwrOn(); //power supply will be provided via relais
	void fullPwrOff(); //power supply will be cutoff
	void toggleOnOff();
	bool isRaspberryOn();
	virtual ~Raspberry();
private:
	void onOffClick();
	void onOffReleaseClick();
	uint8_t _buttonPin;
	uint8_t _sensePin;
	uint8_t _fullPwrPin;
	uint32_t _elapsedTime;
	uint32_t _elapsedTimeFullPwr;
	uint32_t _elapsedStartupTime;
	bool _onOffClicked;
	bool _fullPwrOffRequired;
	bool _switchOnRequired;
	bool _switchOffRequired;
};

#endif /* RASPBERRY_H_ */
