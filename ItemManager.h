#pragma once
#include "Headers.h"
#include "Sprite.h"
#include "Item.h"

enum LOCATION_TYPE {
	LOC_START, LOC_POS
};

struct Location {
	XMFLOAT3		m_pos;
	LOCATION_TYPE	m_locType;
	string			m_locName;
};

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



class ItemManager {

public:

	ItemManager();
	~ItemManager();
	void SpawnItem();

	void Load(wstring fn);


private:

	int m_numLocations;
	Location* m_locations;
	Sprite m_spr_chest;
	Sprite m_spr_coin;

};