#include "Enemy.h"

Enemy::Enemy() {
	prev_pos = prev_vel = acc = vel = pos = { 0.0f, 0.0f, 0.0f };
	col = { 0.0f, 0.0f, 0.0f, 0.0f };
	UpdateCollision();
	ev = { 0 };

}

void Enemy::Create(UINT tex, UINT vShader, UINT pShader) {

	sprite.AssignResources(tex, vShader, pShader);
	sprite.SetSourceRect(2);
	sprite.SetDimensions(0.5f, 0.5f);
	sprite.Create();




	// dot stuff
	float xW = 0.5f;
	float yH = 0.5f;
	float pOff = 0.002f;
	ps1.m_numPoints = 5;
	ps1.m_points = new XMFLOAT3[ps1.m_numPoints];
	ps1.m_points[0] = { -xW - pOff,0.0f,0.0f };
	ps1.m_points[1] = { 0.0f,yH + pOff,0.0f };
	ps1.m_points[2] = { xW + pOff,0.0f,0.0f };
	ps1.m_points[3] = { 0.0f, -yH - pOff,0.0f };
	ps1.m_points[4] = { 0.0f, 0.0f,0.0f };
	ps1.Create(ps1.m_points, 5);





}


void Enemy::Update(double deltaTime) {


	prev_animState = animState;

	if (ev.collidingBelow)vel.y = 0.0f;
	if (ev.collidingAbove)vel.y = 0.0f;


	if (ev.collidingRight)xdir = -1;
	if (ev.collidingLeft)xdir = 1;

	vel.x = (deltaTime / 1000) * 3.0f * xdir;

	//Animation
	if (vel.x > 0)animState = AS_PL_WALKLEFT;
	else if (vel.x < 0)animState = AS_PL_WALKRIGHT;

	
	vel.y -= (deltaTime / 1000);

	//Final Calcs
	Animate(deltaTime);
	vel.x *= 0.8;

	if (vel.y < -0.5f)vel.y = -0.5f;
	MoveBy(vel);



	
	prev_pos = pos;
}

void Enemy::Draw() {

	sprite.Draw(pos);
	ps1.Draw(pos);

}

void Enemy::Animate(double deltaTime) {

	if (animState != prev_animState) { // Instantly play if new animation
		curAnimFrame = 0;
		sprite.SetSourceRect(AS_PL_FRAMES[animState].frameLoc[curAnimFrame]);
		return;
	}

	elapsedTime += deltaTime;

	if (elapsedTime > 300) { //play frame
		elapsedTime -= 300;

		curAnimFrame++;
		if (curAnimFrame >= AS_PL_FRAMES[animState].numFrames)curAnimFrame = 0;

		sprite.SetSourceRect(AS_PL_FRAMES[animState].frameLoc[curAnimFrame]);

	}
}

void Enemy::UpdateCollision() {
	XMFLOAT2 temp = sprite.GetSprWH();
	col.x = pos.x - temp.x;
	col.y = pos.y + temp.y;
	col.z = pos.x + temp.x;
	col.w = pos.y - temp.y;
}

void Enemy::SetCollision(XMFLOAT4 c) {
	col = c;
}

XMFLOAT4 Enemy::GetCollision() {
	UpdateCollision();
	return col;
}


void Enemy::MoveBy(XMFLOAT3 p) {

	pos.x += p.x;
	pos.y += p.y;
	pos.z += p.z;
	UpdateCollision();

}
void Enemy::MoveTo(XMFLOAT3 p) {

	pos.x = p.x;
	pos.y = p.y;
	pos.z = p.z;
	UpdateCollision();

}