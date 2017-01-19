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


	bool IsButtonActionPressed();


private:

	MENUCONTROL_DIRECTION m_currentDirection;

	double m_elapsedTimeSinceMove = 0.0f;
	double m_timeBeforeCanMove = 70.0f;

	bool m_hasActionBeenReleased = 0;
	bool m_hasBacktBeenReleased = 0;
	bool m_hasMoveBeenReleased = 0;

	bool m_actionPressed = 0;
	bool m_backPressed = 0;

	bool m_canMove = 0;
	bool m_canAction = 0;
	bool m_canBack = 0;
};