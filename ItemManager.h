#pragma once
#include "Sprite.h"

struct ItemStruct {
	bool canPickup;
	bool goesInInv;
	bool isLocked;
	bool isKey;
	bool isWeapon;
};

enum IT_ITEMS {

	IT_CHEST, IT_COIN,
};

class Items{

public:


private:

};


class ItemManager {

public:

	void SpawnItem();


private:


	Sprite m_spr_chest;
	Sprite m_spr_coin;

};