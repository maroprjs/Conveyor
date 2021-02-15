/*
 * ConveyorUI.h
 *
 *  Created on: 14 Feb 2021
 *      Author: pionet
 */

#ifndef CONVEYORUI_H_
#define CONVEYORUI_H_
#include "Modem.h"
#include "Conveyor.h"

class ConveyorUI {
public:
	ConveyorUI(Modem* modem, Conveyor* conveyor);
	void begin();
	void loop();
	bool serialMMI(char command);
	virtual ~ConveyorUI();
private:
	Modem* _modem;
	Conveyor* _conveyor;
	char* _msg;
};

#endif /* CONVEYORUI_H_ */
