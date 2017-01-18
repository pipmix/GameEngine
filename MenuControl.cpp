#include "MenuControl.h"

MenuControl::MenuControl()
{
}

void MenuControl::Update(double dt){
	if (gInput.b.a) m_currentDirection = MCD_UP;
	else if (gInput.b.b) m_currentDirection = MCD_DOWN;
	else m_currentDirection = MCD_NOTHING;
}

int MenuControl::GetCurrentDirection()
{
	return m_currentDirection;
}

void MenuControl::Moved()
{
}
