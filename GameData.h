#pragma once
#include "Data.h"

enum POINTCOL {
	PC_BottomLeft, PC_BottomRight, PC_BottomCenter, PC_Center, PC_TopLeft, PC_TopRight, PC_LeftLedge, PC_RightLedge, PC_TopCenter, PC_LeftCenter, PC_RightCenter, PC_COUNT
};

enum GD_BASIC_TYPES {
	GD_BT_PLAYER, GD_BT_ENEMY, GD_BT_ITEM, GD_BT_OBSTACLE, GD_BT_MAPCOLLISION, GD_BT_MELEE_ATTACK, 
	GD_BT_SWORD, GD_BT_ARMOR, GD_BT_BOW, GD_BT_MONEY, GD_BT_KEY, GD_BT_COUNT

};

enum GD_ITEM_TYPE {
	GC_SD_COIN, GC_SD_GEM, GC_SD_BAG
};

struct ItemData {
	GD_BASIC_TYPES itemType;
	float collisionW;
	float collisionH;
	const char* itemName;
	int textureID;
	int tileNumber;
	int animationFames;
	int value;
	float str;
	float def;
	float dmg;
} static const
ItemTypes[] = {
	{ GD_BT_MONEY,		0.5f,	0.5f,	"Coin",			DT_ITEMS,	0,	8},
	{ GD_BT_ARMOR,		0.5f,	0.5f,	"Carpe",		DT_ITEMS,	32, 0 },
	{ GD_BT_SWORD,		0.5f,	0.5f,	"Sword",		DT_ITEMS,	32, 0 },
},
GD_SwordTypes[] = {
	{ GD_BT_SWORD,		0.5f,	0.5f,	"Sword",		DT_ITEMS,	24,	0 },
	{ GD_BT_SWORD,		0.5f,	0.5f,	"Sword",		DT_ITEMS,	24,	0 },

},
GD_BowTypes[] = {
	{ GD_BT_BOW,		0.5f,	0.5f,	"Wooden Bow",		DT_ITEMS,	32,	0 },
	{ GD_BT_BOW,		0.5f,	0.5f,	"LongBow",			DT_ITEMS,	32,	0, 10, 2.0f,0.0f, 2.0f },

};
