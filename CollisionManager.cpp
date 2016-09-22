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

		
		
		//B2.x = m.m_collisionRects[i].x;
		//B2.y = m.m_collisionRects[i].y;
		//B2.z = m.m_collisionRects[i].z;
		//B2.w = m.m_collisionRects[i].w;

		B1 = p.GetCollision();
		B2 = m.m_collisionRects[i];
		XMFLOAT3 velocity = { 0.0f, 0.0f, 0.0f };
		float l = B2.x - (B1.x + B1.z);
		float r = (B2.x + B2.z) - B1.x;
		float t = B2.y - (B1.y + B1.w);
		float b = (B2.y + B2.w) - B1.y;


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

				if (!(p.vel.y > 0.0f))p.vel.y = 0.0f;

			}


			if (velocity.x > 0.0f) {
				p.pv.cLeft = 1;
				p.vel.x = 0.0f;
			}
			else if (velocity.x < 0.0f) {
				p.pv.cRight = 1;
				p.vel.x = 0.0f;
			}
			if (velocity.y < 0.0f)p.pv.cTop = 1;
			else if (velocity.y > 0.0f)p.pv.cBottom = 1;

			p.MoveBy(velocity);

		}


	}



	
}
