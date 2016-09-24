#include "CollisionManager.h"


CollisionManager::CollisionManager(){
}

void CollisionManager::Collide(Player& p, Map& m) {


	XMFLOAT4 b1, b2;

	for (int i = 0; i < m.m_numCollisionRects; i++) {

		b1 = p.GetCollision();
		b2 = m.m_collisionRects[i];

		XMFLOAT3 velocity = { 0.0f, 0.0f, 0.0f };
		float l = b2.x - b1.z;
		float r = b2.z - b1.x;
		float b = b2.y - b1.w;
		float t = b2.w - b1.y;
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

			if (velocity.x > 0.0f) p.pv.collidingLeft = 1;
			else if (velocity.x < 0.0f) p.pv.collidingRight = 1;
			if (velocity.y < 0.0f)p.pv.collidingAbove = 1;
			else if (velocity.y > 0.0f)p.pv.collidingBelow = 1;

			p.MoveBy(velocity);

		}
	}

	
}

void CollisionManager::Collide(Enemy & e, Map & m){

	XMFLOAT4 b1, b2;

	for (int i = 0; i < m.m_numCollisionRects; i++) {

		b1 = e.GetCollision();
		b1.w = -(b1.w - b1.y);//abs
		b2 = m.m_collisionRects[i];
		float he = m.m_collisionRects[i].w - m.m_collisionRects[i].y;
		b2.y = he + m.m_collisionRects[i].y;
		b2.w = -(m.m_collisionRects[i].w - m.m_collisionRects[i].y);

		XMFLOAT3 velocity = { 0.0f, 0.0f, 0.0f };
		float l = b2.x - b1.z;
		float r = b2.z - b1.x;
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

			if (velocity.x > 0.0f) e.pv.collidingLeft = 1;
			else if (velocity.x < 0.0f) e.pv.collidingRight = 1;
			if (velocity.y < 0.0f)e.pv.collidingAbove = 1;
			else if (velocity.y > 0.0f)e.pv.collidingBelow = 1;

			e.MoveBy(velocity);

		}
	}




}

void CollisionManager::Collide(Player & p, Enemy & e)
{
}

void CollisionManager::Collide(Player & p, Item & it){



	XMFLOAT4 b1, b2;




	b1 = p.GetCollision();
	b1.w = -(b1.w - b1.y);//abs
	b2 = it.m_collision;
	float he = it.m_collision.w - it.m_collision.y;
	b2.y = he + it.m_collision.y;
	b2.w = -(it.m_collision.w - it.m_collision.y);


		XMFLOAT3 velocity = { 0.0f, 0.0f, 0.0f };
		float l = b2.x - b1.z;
		float r = b2.z - b1.x;
		float t = b2.y - (b1.y + b1.w);
		float b = (b2.y + b2.w) - b1.y;
		if (l > 0 || r < 0 || t > 0 || b < 0) {
			return;
		}
		else {
			velocity.x = abs(l) < r ? l : r;
			velocity.y = abs(t) < b ? t : b;
			if (abs(velocity.x) < abs(velocity.y)) {
				it.avail = false;
				velocity.y = 0.0f;
			}
			else {
				
				velocity.x = 0.0f;
				//if (!(spr01.m_vel.y > 0.0f))spr01.m_vel.y = 0.0f;
			}

			it.avail = false;
			it.MoveBy(velocity);

		}



}

void CollisionManager::Collide(Item & it, Map & m){

	XMFLOAT4 b1, b2;

	for (int i = 0; i < m.m_numCollisionRects; i++) {

		b1 = it.GetCollision();
		b1.w = -(b1.w - b1.y);//abs
		b2 = m.m_collisionRects[i];
		float he = m.m_collisionRects[i].w - m.m_collisionRects[i].y;
		b2.y = he + m.m_collisionRects[i].y;
		b2.w = -(m.m_collisionRects[i].w - m.m_collisionRects[i].y);

		XMFLOAT3 velocity = { 0.0f, 0.0f, 0.0f };
		float l = b2.x - b1.z;
		float r = b2.z - b1.x;
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


			it.MoveBy(velocity);

		}
	}

}

float mClamp(float x, float min, float max){

	return x < min ? min : (x > max ? max : x);

}

bool CollisionManager::RectCircleIntersect(XMFLOAT4 rect, XMFLOAT3 circPos, float circRadius){
	/*
	//XMFLOAT4 tt = rect;
	//tt.w = -(tt.w);//abs
	float closestX = mClamp(circPos.x, rect.x, rect.z);
	float closestY = mClamp(circPos.y, rect.w, rect.y);


	float distX = circPos.x - closestX;
	float distY = circPos.y - closestY;


	float distanceSquared = (distX * distX) + (distY * distY);
	return distanceSquared < (circRadius * circRadius);
	*/

	//Vector2D clamp_on_rectangle(Vector2D p, Rectangle r)
	//{
		XMFLOAT2 clamp;
		clamp.x = mClamp(circPos.x, rect.x, rect.z);
		clamp.y = mClamp(circPos.y, rect.y, rect.w);
		
	//}
	//Bool circle_rectangle_collide(Circle c, Rectangle r)
	//{
		
		//return circle_point_collide(c, clamped);

		//Bool circle_point_collide(Circle c, Vector2D p)
		//{
		XMFLOAT2 distance;
		distance.x = circPos.x - clamp.x;
		distance.y = circPos.y + clamp.y;

		float length = sqrtf(distance.x * distance.x + distance.y * distance.y);

		return length <= circRadius;

	
}



void CollisionManager::Collide(Enemy & enem, Emitter & emit){




	XMFLOAT4 b1, b2;

	for (int i = 0; i < emit.m_numParticles; i++) {

		b1 = enem.GetCollision();
		b1.w = -(b1.w - b1.y);//abs
		b2 = emit.GetCollision(i);
		float he = b2.w - b2.y;
		b2.y = he + b2.y;
		b2.w = -(b2.w - emit.GetCollision(i).y);

		XMFLOAT3 velocity = { 0.0f, 0.0f, 0.0f };
		float l = b2.x - b1.z;
		float r = b2.z - b1.x;
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


			enem.MoveBy(velocity);

		}
	}




}

void CollisionManager::Collide(Player & play, Emitter & emit){
}

void CollisionManager::Collide(Emitter & emit, Map & mp){


}
