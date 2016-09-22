#include "Player.h"

Player::Player(){
	prev_pos = prev_vel = acc = vel = pos = { 0.0f, 0.0f, 0.0f };

}

void Player::Create(UINT tex, UINT vShader, UINT pShader){



	sprite.AssignResources(DT_WALKTEST, DV_BASICMATRX, DP_BASICMATRX);
	sprite.SetSourceRect(2);
	sprite.Create();





}


void Player::Update(double deltaTime) {
	
	prev_pos = pos;
	prev_vel = vel;
	prev_animState = animState;


	if (gInput.isConnected) {

		if (abs(gInput.b.leftStickFloatX) > 0.001) {
			vel.x += (deltaTime / 1000) * gInput.b.leftStickFloatX;

			
		}
		


	}

	//Gravity
	vel.y += -(deltaTime / 1000) * 0.2;



	//Animation
	if (vel.x > 0)animState = AS_PL_WALKLEFT;
	else if (vel.x < 0)animState = AS_PL_WALKRIGHT;

	//Final Calcs
	Animate(deltaTime);
	vel.x *= 0.8;
	pos.x += vel.x;
	pos.y += vel.y;
	UpdateCollision();



}

void Player::Draw() {

	sprite.Draw(pos);

}

void Player::Animate(double deltaTime) {

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

void Player::UpdateCollision(){
	col.x = pos.x;
	col.y = pos.y;
	col.z = pos.x + 1.0f;
	col.w = pos.y + 1.0f;

}

void Player::SetCollision(XMFLOAT4 c){
	col = c;
}

XMFLOAT4 Player::GetCollision(){
	return col;
}


void	Player::MoveBy(XMFLOAT3 p) {

	pos.x += p.x;
	pos.y += p.y;
	pos.z += p.z;
	UpdateCollision();

}