#include "CollisionManager.h"

CollisionManager::CollisionManager(){
}

void CollisionManager::Collide(Player& p, Map& m) {


	XMFLOAT4 b1, b2;

	for (int i = 0; i < m.m_numCollisionRects; i++) {

		b1 = p.GetCollision();
		b1.z = b1.z - b1.x;
		b1.w = -(b1.w - b1.y);//abs

		b2 = m.m_collisionRects[i];
		float he = m.m_collisionRects[i].w - m.m_collisionRects[i].y;
		b2.x = m.m_collisionRects[i].x;
		b2.y = he + m.m_collisionRects[i].y;
		b2.z = m.m_collisionRects[i].z - m.m_collisionRects[i].x;
		b2.w = -(m.m_collisionRects[i].w - m.m_collisionRects[i].y);

		XMFLOAT3 velocity = { 0.0f, 0.0f, 0.0f };
		float l = b2.x - (b1.x + b1.z);
		float r = (b2.x + b2.z) - b1.x;
		float t = b2.y - (b1.y + b1.w);
		float b = (b2.y + b2.w) - b1.y;
		if (l > 0 || r < 0 || t > 0 || b < 0) {
			continue;
		}
		else {
			velocity.x = abs(l) < r ? l : r;
			velocity.y = abs(t) < b ? t : b;
			if (abs(velocity.x) < abs(velocity.y)) {
				velocity.y = 0.0f;
			}
			else {
				velocity.x = 0.0f;
				//if (!(spr01.m_vel.y > 0.0f))spr01.m_vel.y = 0.0f;
			}
			p.MoveBy(velocity);


		}
	}







	/*
	for (int i = 0; i < m.m_numCollisionRects; i++) {

	
		B1 = p.GetCollision();
		B2 = m.m_collisionRects[i];

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
	*/


	
}
