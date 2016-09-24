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
	ps1.m_points[0] = { -xW - pOff,0.0f,0.0f };
	ps1.m_points[1] = { 0.0f,yH + pOff,0.0f };
	ps1.m_points[2] = { xW + pOff,0.0f,0.0f };
	ps1.m_points[3] = { 0.0f, -yH-pOff,0.0f };
	ps1.m_points[4] = { 0.0f, 0.0f,0.0f };
	ps1.Create(ps1.m_points,5);


	cs1.Create(0.5f, 12);

}


void Player::Update(double deltaTime) {

	prev_animState = animState;
	pv.applyGrav = true;


	if (pv.collidingBelow)vel.y = 0.0f;
	if (pv.collidingAbove)vel.y = 0.0f;

	// Camera
	float moveZ = (-gInput.b.leftTriggerFloat) + gInput.b.rightTriggerFloat;
	gCam.MoveBy(gInput.b.rightStickFloatX, gInput.b.rightStickFloatY, moveZ);


	vel.x += (deltaTime / 1000) * gInput.b.leftStickFloatX;
	//vel.y += (deltaTime / 1000) * gInput.b.leftStickFloatY;



		
	oGround += pv.collidingBelow;
		

	if (gInput.b.y)MoveTo({ 0.0f,0.0f,0.0f });
	if (gInput.b.a == false)jumpReleased = true;

	if (gInput.b.a) {
		if (pv.collidingBelow && jumpReleased && (oGround > 3)) {
			vel.y += 0.3f;
			jumpReleased = false;
			oGround = 0;
		}
		
	}
	if (gInput.b.x && pv.collidingBelow)vel.x *= 1.14f;



	if (vel.x < 0.0f) {
		pv.facing = -1;
		dir = XM_PI;
	}
	if (vel.x > 0.0f) {
		pv.facing = 1;
		dir = XM_2PI;
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
	
	
	//vel.y *= 0.8;



	//Animation
	if (vel.x > 0)animState = AS_PL_WALKLEFT;
	else if (vel.x < 0)animState = AS_PL_WALKRIGHT;

	//Final Calcs
	Animate(deltaTime);
	vel.x *= 0.85;

	if (vel.y < -0.218f) vel.y = -0.218f;
	if (vel.y > 0.3f)vel.y = 0.3f;
	

	if (vel.x < -0.19f) vel.x = -0.19f;
	if (vel.x > 0.19f)vel.x = 0.19f;


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