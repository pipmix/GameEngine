#pragma once
#include "Input.h"

extern Input gInput;

enum MENUCONTROL_DIRECTION {
	MCD_NOTHING, MCD_UP, MCD_DOWN, MCD_LEFT, MCD_RIGHT, MCD_UPLEFT, MCD_UPRIGHT, MCD_DOWNLEFT, MCD_DOWNRIGHT, MCD_COUNT
};

class MenuControl {


public:

	MenuControl();
	void Update(double dt);
	int GetCurrentDirection();
	void Moved();


private:

	MENUCONTROL_DIRECTION m_currentDirection;


};