#pragma once
#include "Player.h"
#include "Map.h"



class CollisionManager {

public:


	CollisionManager();

	void Collide(Player& p, Map& m);



};
