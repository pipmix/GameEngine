#pragma once
#include "Input.h"

extern Input gInput;

enum E_CURRENT_BUTTONS_PRESSED {
	CBP_NONE = 1,
	CBP_CONFIRM = 2,
	CBP_CANCEL = 4,

};

DEFINE_ENUM_FLAG_OPERATORS(E_CURRENT_BUTTONS_PRESSED)

enum MENUCONTROL_DIRECTION {
	MCD_NOTHING, MCD_UP, MCD_DOWN, MCD_LEFT, MCD_RIGHT, MCD_UPLEFT, MCD_UPRIGHT, MCD_DOWNLEFT, MCD_DOWNRIGHT, MCD_COUNT
};

class MenuControl {


public:

	MenuControl();
	void Update(double dt);
	int GetCurrentDirection();
	void Moved();
	void ActivatedSelection();

	bool IsButtonActionPressed();

	int GetCurrentButtonsPressed();


private:

	MENUCONTROL_DIRECTION m_currentDirection;

	double m_elapsedTimeSinceMove = 0.0f;
	double m_timeBeforeCanMove = 70.0f;

	double m_elapsedTimeSinceActivateSelection = 0.0f;
	double m_timeBeforeCanActivateSelection = 70.0f;

	bool m_canActivateSelection = 0;
	bool m_hasActivateSelectionBeenReleased = 0;

	bool m_hasConfirmBeenReleased = 0;
	bool m_hasCanceltBeenReleased = 0;
	bool m_hasMoveBeenReleased = 0;

	bool m_actionPressed = 0;
	bool m_backPressed = 0;

	bool m_canMove = 0;
	bool m_canAction = 0;
	bool m_canBack = 0;

	int m_buttonsCurPressed = 1;
};