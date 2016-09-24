#pragma once
#include "Headers.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "Map.h"
#include "Emitter.h"




class CollisionManager {

public:


	CollisionManager();

	void Collide(Player& p, Map& m);
	void Collide(Enemy& e, Map& m);
	void Collide(Player& p, Enemy& e);
	void Collide(Player& p, Item& it);
	void Collide(Item& it, Map& m);
	void Collide(Enemy& enem, Emitter& emit);
	void Collide(Player& play, Emitter& emit);
	void Collide(Emitter& emit, Map& mp);


	bool RectCircleIntersect(XMFLOAT4 rect, XMFLOAT3 circPos, float circRadius);


};
