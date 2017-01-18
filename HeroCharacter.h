#pragma once

enum HERO_CHARACTER_TYPE {
	HCT_WARRIOR, HCT_MAGE
};


class HeroCharacter {
public:

	HeroCharacter(int HeroCharacterType);


	void ResetTurn();
	void EndTurn();


private:


	int m_maxHitPoints;
	int m_curHitPoints;

	int m_maxMagicPoints;
	int m_curMagicPoints;

	int m_maxFatigue;
	int m_curFatigue;

	bool m_activated;
	bool m_hibernated;
	bool m_hasSearched;

	int m_actionsTaken;

	

};