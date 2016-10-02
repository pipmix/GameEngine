#include "Player.h"

Player::Player(){
	prev_pos = prev_vel = acc = vel = pos = { 0.0f, 0.0f, 0.0f };
	col = { 0.0f, 0.0f, 0.0f, 0.0f };
	UpdateCollision();
	pv = { 0 };

}

void Player::Create(UINT tex, UINT vShader, UINT pShader){

	// dot stuff
	float xW = 0.5f;
	float yH = 1.0f;
	float pOff = 0.002f;
	float ledgeOff = 0.2f;
	int nPoints = 9;

	sprite.AssignResources(tex, vShader, pShader);
	sprite.SetSourceRect(2);
	sprite.SetDimensions(xW, yH);
	
	sprite.Create();


	ps1.m_numPoints = nPoints;
	ps1.m_points = new XMFLOAT3[ps1.m_numPoints];
	ps1.m_points[0] = { -xW - pOff,0.0f,0.0f };
	ps1.m_points[1] = { 0.0f,yH + pOff,0.0f };
	ps1.m_points[2] = { xW + pOff,0.0f,0.0f };
	ps1.m_points[3] = { 0.0f, -yH-pOff,0.0f };
	ps1.m_points[4] = { 0.0f, 0.0f,0.0f };

	ps1.m_points[5] = { -xW - pOff, yH				,0.0f };
	ps1.m_points[6] = { -xW - pOff, yH - ledgeOff	,0.0f };

	ps1.m_points[7] = { xW + pOff, yH				,0.0f };
	ps1.m_points[8] = { xW + pOff, yH - ledgeOff	,0.0f };
	ps1.Create(ps1.m_points, nPoints);


	cs1.Create(0.5f, 12);

}


void Player::Update(double deltaTime) {

	prev_animState = animState;
	pv.applyGrav = true;


	if (pv.collidingBelow) {
		vel.y = 0.0f;
		if (m_curState == PSTATE_CLIMBING)m_curState = PSTATE_IDLE;
		if (m_curState == PSTATE_JUMPING)m_curState = PSTATE_IDLE;
	}

	if (pv.collidingAbove)vel.y = 0.0f;


	if (pv.climbing && pv.collidingBelow)pv.climbing = false;
	// Camera
	float moveZ = (-gInput.b.leftTriggerFloat) + gInput.b.rightTriggerFloat;
	gCam.MoveBy(gInput.b.rightStickFloatX, gInput.b.rightStickFloatY, moveZ);

	if (gInput.b.y)MoveTo({ 0.0f, 0.0f, 0.0f });


	// Is able to climb
	if (!pv.leftLedgeTopCollide && pv.leftLedgeUnderCollide)pv.leftLedgeCollide = true;
	if (!pv.rightLedgeTopCollide && pv.rightLedgeUnderCollide)pv.rightLedgeCollide = true;

	// If able will climb if b pressed
	if (pv.leftLedgeCollide || pv.rightLedgeCollide) {

		if (gInput.b.x && m_curState != PSTATE_CLIMBING) {
			vel.y += 0.6f;
			m_curState = PSTATE_CLIMBING;
		}
	}



	vel.x += (deltaTime / 1000) * gInput.b.leftStickFloatX;
	
	oGround += pv.collidingBelow;

	if (pv.collidingRight && (gInput.b.leftStickFloatX > 0.0f) && !pv.collidingBelow) {
		m_curState = PSTATE_ONWALL;
		pv.onWall = true;
		

	}
	else if (pv.collidingLeft && (gInput.b.leftStickFloatX < 0.0f) && !pv.collidingBelow) {
		m_curState = PSTATE_ONWALL;
		pv.onWall = true;
		
	}
	else {
		pv.onWall = false;
		pv.wallStart = false;
	}

	if (pv.onWall && gInput.b.a) {
		if (pv.wallStart) {
			pv.onWall = false;
			if (pv.collidingLeft) {
				vel.x = 5.0f;
				vel.y = 0.6f;
			}
			if (pv.collidingRight) {
				vel.x = -5.0f;
				vel.y = 0.6f;

			}

		}
	}
		
	if (pv.onWall && !gInput.b.a)pv.wallStart = true;

	


	/// Jumping
	if (gInput.b.a == false)jumpReleased = true;
	if (gInput.b.a) {
		if (pv.collidingBelow && jumpReleased && (oGround > 3)) {
			vel.y += 0.3f;
			jumpReleased = false;
			oGround = 0;
		}
		
	}




	/// Running
	if (gInput.b.x && pv.collidingBelow)vel.x *= 1.14f;


	/// Facing
	if (vel.x < 0.0f) {
		pv.facing = -1;
		dir = XM_PI;
	}
	if (vel.x > 0.0f) {
		pv.facing = 1;
		dir = XM_2PI;
	}





	/// Gravity
	if (pv.applyGrav)vel.y -= (deltaTime / 1000);
	if (pv.onWall && m_curState != PSTATE_CLIMBING)vel.y *= 0.75f;
	/// Drag
	vel.x *= 0.85;


	/// Velocity Protection
	if (vel.y < -0.218f) vel.y = -0.218f;
	if (vel.y > 0.3f)vel.y = 0.3f;
	if (vel.x < -0.19f) vel.x = -0.19f;
	if (vel.x > 0.19f)vel.x = 0.19f;

	///Animation
	Animation(deltaTime);

	MoveBy(vel);
	//pv = { 0 };

	pv.rightLedgeTopCollide = pv.rightLedgeUnderCollide = pv.leftLedgeTopCollide = 
	pv.leftLedgeUnderCollide = pv.collidingBelow = pv.collidingLeft = pv.collidingRight = 
	pv.collidingAbove = pv.leftLedgeCollide = pv.rightLedgeCollide = 0;

}

void Player::Draw() {

	sprite.Draw(pos);
	ps1.Draw(pos);
	cs1.Draw(pos);

}

void Player::Animation(double deltaTime) {
	if (vel.x > 0)animState = AS_PL_WALKLEFT;
	else if (vel.x < 0)animState = AS_PL_WALKRIGHT;
	Animate(deltaTime);

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


}
void Player::MoveTo(XMFLOAT3 p) {

	pos.x = p.x;
	pos.y = p.y;
	pos.z = p.z;
	UpdateCollision();

}