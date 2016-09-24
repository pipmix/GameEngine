#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Map.h"



class CollisionManager {

public:


	CollisionManager();

	void Collide(Player& p, Map& m);
	void Collide(Enemy& e, Map& m);
	void Collide(Player& p, Enemy& e);



};
