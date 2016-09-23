#include "CollisionManager.h"

CollisionManager::CollisionManager(){
}

void CollisionManager::Collide(Player& p, Map& m) {

	XMFLOAT4 B1;

	B1.x = p.GetCollision().x;
	B1.y = p.GetCollision().y;
	B1.z = p.GetCollision().z - p.GetCollision().x;
	B1.w = abs(p.GetCollision().w - p.GetCollision().y);

	XMFLOAT4 B2;

	for (int i = 0; i < m.m_numCollisionRects; i++) {

	
		B1 = p.GetCollision();
		B2 = m.m_collisionRects[i];
		B2.w = m.m_collisionRects[i].w * -1.0f;
		XMFLOAT3 velocity = { 0.0f, 0.0f, 0.0f };
		float l = B2.x - (B1.x + B1.z);
		float t = B2.y - (B1.y + B1.w);
		float r = (B2.x + B2.z) - B1.x;
		float b = (B2.y + B2.w) - B1.y;


		if (l > 0 || r < 0 || t > 0 || b < 0) continue;
		
		velocity.x = abs(l) < r ? l : r;
		velocity.y = abs(t) < b ? t : b;
		if (abs(velocity.x) < abs(velocity.y))velocity.y = 0.0f;
		else velocity.x = 0.0f;
		p.MoveBy(velocity);


	
	}



	
}
