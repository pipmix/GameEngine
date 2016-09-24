#include "CollisionManager.h"


CollisionManager::CollisionManager(){
}

bool CollisionManager::PointRectIntersect(XMFLOAT3 point, XMFLOAT4 r){


	//return rect.x <= tp.x && rect.w <= tp.y && tp.x <= rect.z && tp.y <= rect.y;
	return((		((point.x) >= min(r.x, r.z)) && ((point.x) <= max(r.x, r.z))		)			&&		(((point.y) >= min(r.y, r.w)) && ((point.y) <= max(r.y, r.w))		));
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

			abs(velocity.x) < abs(velocity.y) ? velocity.y = 0.0f : velocity.x = 0.0f;

			p.MoveBy(velocity);

		}
	}


	//p.ps1.UpdatePoints(XMFLOAT3 p);
	for (int i = 0; i < p.ps1.m_numPoints; i++) {
		bool hit = false;
		XMFLOAT3 tp = p.ps1.m_points[i];
		tp.x += p.pos.x;
		tp.y += p.pos.y;
		for (int j = 0; j < m.m_numCollisionRects; j++) {
			if (PointRectIntersect(tp, m.m_collisionRects[j]))hit = true;
		}
		if (hit) {
			switch (i){
			case 0:
				p.pv.collidingLeft = true;
				break;
			case 1:
				p.pv.collidingAbove = true;
				break;
			case 2:
				p.pv.collidingRight = true;
				break;
			case 3:
				p.pv.collidingBelow = true;
				break;
			case 4:
				p.pv.collidingLadder = true;
				break;
			}

		}
		else {
			switch (i) {
			case 0:
				p.pv.collidingLeft = false;
				break;
			case 1:
				p.pv.collidingAbove = false;
				break;
			case 2:
				p.pv.collidingRight = false;
				break;
			case 3:
				p.pv.collidingBelow = false;
				break;
			case 4:
				p.pv.collidingLadder = false;
				break;
			}
		}
	}
}

void CollisionManager::Collide(Enemy & e, Map & m){

	XMFLOAT4 b1, b2;

	for (int i = 0; i < m.m_numCollisionRects; i++) {

		b1 = e.GetCollision();
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

			abs(velocity.x) < abs(velocity.y) ? velocity.y = 0.0f : velocity.x = 0.0f;

			e.MoveBy(velocity);

		}
	}

	/// POINTS
	for (int i = 0; i < e.ps1.m_numPoints; i++) {
		bool hit = false;
		XMFLOAT3 tp = e.ps1.m_points[i];
		tp.x += e.pos.x;
		tp.y += e.pos.y;
		for (int j = 0; j < m.m_numCollisionRects; j++) {
			if (PointRectIntersect(tp, m.m_collisionRects[j]))hit = true;
		}
		if (hit) {
			switch (i) {
			case 0:
				e.ev.collidingLeft = true;
				break;
			case 1:
				e.ev.collidingAbove = true;
				break;
			case 2:
				e.ev.collidingRight = true;
				break;
			case 3:
				e.ev.collidingBelow = true;
				break;
			case 4:
				e.ev.collidingLadder = true;
				break;
			}

		}
		else {
			switch (i) {
			case 0:
				e.ev.collidingLeft = false;
				break;
			case 1:
				e.ev.collidingAbove = false;
				break;
			case 2:
				e.ev.collidingRight = false;
				break;
			case 3:
				e.ev.collidingBelow = false;
				break;
			case 4:
				e.ev.collidingLadder = false;
				break;
			}
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
