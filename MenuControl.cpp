#include "MenuControl.h"

MenuControl::MenuControl()
{
}

void MenuControl::Update(double dt){

	m_elapsedTimeSinceMove += dt;
	m_elapsedTimeSinceActivateSelection += dt;
	m_buttonsCurPressed = 0;

	// Direction Input
	if (m_elapsedTimeSinceMove > m_timeBeforeCanMove) 
		m_canMove = true;
	else 
		m_canMove = false;

	if (m_elapsedTimeSinceActivateSelection > m_timeBeforeCanActivateSelection)
		m_canActivateSelection = true;
	else
		m_canActivateSelection = false;
	




	if (m_canMove) {
		if (gInput.b.up == 0 && gInput.b.down == 0 && gInput.b.left == 0 && gInput.b.right == 0)m_hasMoveBeenReleased = true;
		if (gInput.b.a == 0)m_hasActivateSelectionBeenReleased = true;

		if (gInput.b.a == 0)m_hasConfirmBeenReleased = true;
		if (gInput.b.b == 0)m_hasCanceltBeenReleased = true;
		

		if (m_hasMoveBeenReleased) {
			if (gInput.b.up) {
				m_currentDirection = MCD_UP;
				Moved();
			}
			else if (gInput.b.down) {
				m_currentDirection = MCD_DOWN;
				Moved();
			}
			else if (gInput.b.left) {
				m_currentDirection = MCD_LEFT;
				Moved();
			}
			else if (gInput.b.right) {
				m_currentDirection = MCD_RIGHT;
				Moved();
			}
		}

	}
	else {
		m_currentDirection = MCD_NOTHING;
	}

	// Button Logic
	if (m_canActivateSelection) {
		if (gInput.b.a && m_hasConfirmBeenReleased) {
			m_hasConfirmBeenReleased = false;
			m_buttonsCurPressed |= CBP_CONFIRM;
			ActivatedSelection();
		}
		if (gInput.b.b && m_hasCanceltBeenReleased) {
			m_hasCanceltBeenReleased = false;
			m_buttonsCurPressed |= CBP_CANCEL;
		}
	}
	





}

int MenuControl::GetCurrentDirection(){




	return m_currentDirection;
}

void MenuControl::Moved(){
	m_elapsedTimeSinceMove = 0.0f;
	m_canMove = false;
	m_hasMoveBeenReleased = false;
}

void MenuControl::ActivatedSelection() {

	m_elapsedTimeSinceActivateSelection = 0.0f;
	m_canActivateSelection = false;
	m_hasActivateSelectionBeenReleased = false;



}


bool MenuControl::IsButtonActionPressed() {
	if (gInput.b.a && m_hasConfirmBeenReleased) {
		m_hasConfirmBeenReleased = false;
		return true;
	}
	else return false;

}

int MenuControl::GetCurrentButtonsPressed(){
	return m_buttonsCurPressed;
}
