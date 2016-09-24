#include "Player.h"

Player::Player(){
	prev_pos = prev_vel = acc = vel = pos = { 0.0f, 0.0f, 0.0f };
	col = { 0.0f, 0.0f, 0.0f, 0.0f };
	UpdateCollision();
	pv = { 0 };

}

void Player::Create(UINT tex, UINT vShader, UINT pShader){

	float xW = 0.5f;
	float yH = 1.0f;
	float pOff = 0.002f;

	sprite.AssignResources(DT_WALKTEST, DV_BASICMATRX, DP_BASICMATRX);

	sprite.SetSourceRect(2);
	sprite.SetDimensions(xW, yH);
	
	sprite.Create();


	ps1.m_numPoints = 5;
	ps1.m_points = new XMFLOAT3[ps1.m_numPoints];
	XMFLOAT3 pnts[5];
	pnts[0] = { -xW - pOff,0.0f,0.0f };
	pnts[1] = { 0.0f,yH + pOff,0.0f };
	pnts[2] = { xW + pOff,0.0f,0.0f };
	pnts[3] = { 0.0f, -yH-pOff,0.0f };
	pnts[4] = { 0.0f, 0.0f,0.0f };
	ps1.Create(pnts,5);


	cs1.Create(0.5f, 12);

}


void Player::Update(double deltaTime) {

	prev_animState = animState;
	pv.applyGrav = true;


	vel.x += (deltaTime / 1000) * gInput.b.leftStickFloatX;
	//vel.y += (deltaTime / 1000) * gInput.b.leftStickFloatY;


	if (gInput.isConnected) {


		
		if (gInput.b.y)MoveTo(XMFLOAT3{ 0.0f, 0.0f, 0.0f });

		gInput.b.a ? pv.jumping = true : pv.jumping = false;
		gInput.b.x ? pv.running = true : pv.running = false;
		
		if (gInput.b.a == false)jumpReleased = true;

		//if (abs(gInput.b.leftStickFloatY) > 0.001) {
		//	vel.y += (deltaTime / 1000) * gInput.b.leftStickFloatY;
		//}

		float moveZ = (-gInput.b.leftTriggerFloat) + gInput.b.rightTriggerFloat;
		gCam.MoveBy(gInput.b.rightStickFloatX, gInput.b.rightStickFloatY, moveZ);
		

		
	}



	if (vel.x < 0.0f) {
		pv.facing = -1;
		dir = XM_PI;
	}
	if (vel.x > 0.0f) {
		pv.facing = 1;
		dir = XM_2PI;
	}

	oGround += pv.collidingBelow;
	if (pv.running) {

			vel.x *= 1.1f;

	
		
	}
	if (pv.jumping && pv.collidingBelow) {
		
		if (oGround > 3) {
			if (jumpReleased) {
				pv.facing == -1 ? animState = AS_PL_JUMPINGLEFT : animState = AS_PL_JUMPINGRIGHT;
				vel.y += 0.2f;
				oGround = 0;
				jumpReleased = false;

			}
		}


	}


	//Gravity
	if (pv.applyGrav)vel.y -= (deltaTime / 1000);
	else vel.y *= 0.8;



	//Animation
	if (vel.x > 0)animState = AS_PL_WALKLEFT;
	else if (vel.x < 0)animState = AS_PL_WALKRIGHT;

	//Final Calcs
	Animate(deltaTime);
	vel.x *= 0.8;

	if (vel.y < -0.218f) {
		if (pv.applyGrav)vel.y = -0.218f;
		
	}
	MoveBy(vel);

	

	pv = { 0 };
	prev_pos = pos;
}

void Player::Draw() {

	sprite.Draw(pos);
	ps1.Draw(pos);
	cs1.Draw(pos);

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
	XMFLOAT2 temp = sprite.GetSprWH();
	col.x = pos.x - temp.x;
	col.y = pos.y + temp.y;
	col.z = pos.x + temp.x;
	col.w = pos.y - temp.y;

}

void Player::SetCollision(XMFLOAT4 c){
	col = c;
}

XMFLOAT4 Player::GetCollision(){
	UpdateCollision();
	return col;
}


void Player::MoveBy(XMFLOAT3 p) {

	pos.x += p.x;
	pos.y += p.y;
	pos.z += p.z;
	UpdateCollision();
	/*
	if (p.x > 0.0f)pv.collidingLeft = 1;
	else if (p.x < 0.0f)pv.collidingRight= 1;
	
	

	if (p.y > 0.0f)pv.collidingBelow = 1;
	else if (p.y < 0.0f)pv.collidingAbove = 1;
	*/


}
void Player::MoveTo(XMFLOAT3 p) {

	pos.x = p.x;
	pos.y = p.y;
	pos.z = p.z;
	UpdateCollision();

}