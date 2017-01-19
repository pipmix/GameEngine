#include "MenuControl.h"

MenuControl::MenuControl()
{
}

void MenuControl::Update(double dt){
	/*
	MENUCONTROL_DIRECTION m_currentDirection;

	double m_elapsedTimeSinceMove = 0.0f;
	double m_timeBeforeCanMove = 400.0f;

	bool m_hasActionBeenReleased = 0;
	bool m_hasBacktBeenReleased = 0;
	bool m_hasMoveBeenReleased = 0;

	bool m_actionPressed = 0;
	bool m_backPressed = 0;
	*/

	m_elapsedTimeSinceMove += dt;

	if (m_elapsedTimeSinceMove > m_timeBeforeCanMove) {

		m_canMove = true;
	}
	else {

		m_canMove = false;
	}


	if (m_canMove) {
		if (gInput.b.up == 0 && gInput.b.down == 0)m_hasMoveBeenReleased = true;

		if (m_hasMoveBeenReleased) {
			if (gInput.b.up) {
				m_currentDirection = MCD_UP;
				Moved();
			}
			else if (gInput.b.down) {
				m_currentDirection = MCD_DOWN;
				Moved();
			}
		}

	}
	else {

		m_currentDirection = MCD_NOTHING;

	}



}

int MenuControl::GetCurrentDirection()
{
	return m_currentDirection;
}

void MenuControl::Moved(){
	m_elapsedTimeSinceMove = 0.0f;
	m_canMove = false;
	m_hasMoveBeenReleased = false;
}


bool MenuControl::IsButtonActionPressed() {
	if (gInput.b.y)return true;
	else return false;

}