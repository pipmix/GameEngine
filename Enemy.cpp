#include "Enemy.h"

Enemy::Enemy() {
	prev_pos = prev_vel = acc = vel = pos = { 0.0f, 0.0f, 0.0f };
	col = { 0.0f, 0.0f, 0.0f, 0.0f };
	UpdateCollision();
	pv = { 0 };

}

void Enemy::Create(UINT tex, UINT vShader, UINT pShader) {

	sprite.AssignResources(DT_WALKTEST, DV_BASICMATRX, DP_BASICMATRX);
	sprite.SetSourceRect(2);
	sprite.Create();


}


void Enemy::Update(double deltaTime) {


	prev_animState = animState;

	if (pv.collidingBelow)vel.y = 0.0f;
	if (pv.collidingRight)xdir = -1;
	if (pv.collidingLeft)xdir = 1;

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



	pv = { 0 };
	prev_pos = pos;
}

void Enemy::Draw() {

	sprite.Draw(pos);

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
	col.x = pos.x;
	col.y = pos.y;
	col.z = pos.x + 1.0f;
	col.w = pos.y - 1.0f;

}

void Enemy::SetCollision(XMFLOAT4 c) {
	col = c;
}

XMFLOAT4 Enemy::GetCollision() {
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