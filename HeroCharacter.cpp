#include "HeroCharacter.h"

HeroCharacter::HeroCharacter(int HeroCharacterType){

	switch (HeroCharacterType) {
	case HCT_WARRIOR:

		m_maxHitPoints = 5;
		m_maxMagicPoints = 5;
		m_maxFatigue = 5;

		break;
	case HCT_MAGE:

		m_maxHitPoints = 6;
		m_maxMagicPoints = 6;
		m_maxFatigue = 6;

		break;
	}

	m_curHitPoints		=		m_maxHitPoints;
	m_curMagicPoints	=		m_maxMagicPoints;
	m_curFatigue		=		m_maxFatigue;

	m_activated = 0;
	m_hibernated = 0;


}

