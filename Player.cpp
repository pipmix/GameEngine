#include "Player.h"

Player::Player(){
	prev_pos = prev_vel = acc = vel = pos = { 0.0f, 0.0f, 0.0f };
	col = { 0.0f, 0.0f, 0.0f, 0.0f };
	UpdateCollision();
	pv = { 0 };
	m_statHP = 10;

	m_basicType = GD_BT_PLAYER;

	colOff = { 0.4f, 0.2f, 0.4f, 0.0f };
	
}

void Player::Create(UINT tex, UINT vShader, UINT pShader){


	float xW = 1.0f;
	float yH = 1.0f;
	float pOff = 0.002f;
	float ledgeOff = 0.2f;
	int nPoints = 9;
	float verOffSet = 0.001f;

	sprite.AssignResources(tex, vShader, pShader);
	sprite.SetSourceRect(2);
	sprite.SetDimensions(xW, yH);
	
	sprite.Create();

	XMFLOAT2 temp = sprite.GetSprWH();
	XMFLOAT4 bound;
	bound.x = -(temp.x - colOff.x);
	bound.y = +(temp.y - colOff.y);
	bound.z = +(temp.x - colOff.z);
	bound.w = -(temp.y - colOff.w);

	/// Contact Points
	ps1.m_numPoints					= PC_COUNT;
	ps1.m_points					= new XMFLOAT3[PC_COUNT];
	ps1.m_points[PC_BottomRight]	= { bound.z - verOffSet, bound.w -pOff,0.0f };
	ps1.m_points[PC_BottomLeft]		= { bound.x + verOffSet, bound.w - pOff,0.0f };
	ps1.m_points[PC_BottomCenter]	= { 0.0f, bound.w - pOff,  0.0f };
	ps1.m_points[PC_Center]			= { 0.0f, 0.0f,  0.0f };
	ps1.m_points[PC_TopLeft]		= { bound.x - pOff, yH				,0.0f };
	ps1.m_points[PC_TopRight]		= { bound.z + pOff, yH				,0.0f };
	ps1.m_points[PC_LeftLedge]		= { bound.x - pOff, yH - ledgeOff	,0.0f };
	ps1.m_points[PC_RightLedge]		= { bound.z + pOff, yH - ledgeOff	,0.0f };
	ps1.m_points[PC_LeftCenter]		= { bound.x - pOff, 0.0f,0.0f };
	ps1.m_points[PC_TopCenter]		= { 0.0f,bound.y + pOff,0.0f };
	ps1.m_points[PC_RightCenter]	= { bound.z + pOff,0.0f,0.0f };
	ps1.Create(ps1.m_points, PC_COUNT);


	cs1.Create(0.5f, 12);

	/// melee weapon
	m_meleeWeapon.parent = &pos;
	m_meleeWeapon.active = false;
	pv.CanMelee = true;



	memset(&contact, 0, sizeof(bool) * PC_COUNT);
	pv = { 0 };
	pv.EffectedByGravity = true;
}

/// UPDATE FUNCTIONS
void Player::Update(double deltaTime) {

	dTime = deltaTime;
	CheckContacts();

	gInput.b.a ? JumpButton = true : JumpButton = false;
	gInput.b.x ? RunButton = true : RunButton = false;
		

	//if (gInput.b.a)JumpButton = true;
	//else JumpButton = false;

	prev_animState = animState;

	/// GamePad Input
	/// Camera
	float moveZ = (-gInput.b.leftTriggerFloat) + gInput.b.rightTriggerFloat;
	gCam.MoveBy(gInput.b.rightStickFloatX, gInput.b.rightStickFloatY, moveZ);


	vel.x += (deltaTime / 1000) * gInput.b.leftStickFloatX;

	pv.AgainstGround ? pv.AgainstGroundCounter += pv.AgainstGround : pv.AgainstGroundCounter = 0;


	/// Apply Gravity if not on ground
	!contact[PC_BottomCenter] && pv.EffectedByGravity ? vel.y -= (GRAVITY * deltaTime) : vel.y = 0.0f ;
		
	Jump();
	Run();
	
	
	/// Facing
	if (vel.x < 0.0f) {
		pv.xFacing = -1;
		dir = XM_PI;
	}
	if (vel.x > 0.0f) {
		pv.xFacing = 1;
		dir = XM_2PI;
	}
	if (gInput.b.leftStickFloatY > 0.0f) pv.yFacing = 1;
	else if (gInput.b.leftStickFloatY < 0.0f) pv.yFacing = -1;
	else pv.yFacing = 0;
		

	/// Drag
	vel.x *= 0.85f;
	vel.y *= 0.95f;


	/// Velocity Protection
	//if (vel.y < -0.218f) vel.y = -0.218f;
	//if (vel.y > 6.3f)vel.y = 6.3f;
	//if (vel.x < -0.19f) vel.x = -0.19f;
	//if (vel.x > 0.19f)vel.x = 0.19f;

	///Animation
	Animation(deltaTime);

	MoveBy(vel);

	//contact[PC_BottomRight] ? tempVar = true : tempVar = false;

}

void Player::CheckContacts() {

	//if (contact[PC_BottomCenter] && contact[PC_BottomLeft] && !contact[PC_BottomRight]);//overledge
	//if (contact[PC_BottomCenter] && !contact[PC_BottomLeft] && contact[PC_BottomRight]);//overledge

	contact[PC_BottomLeft] || contact[PC_BottomRight] || contact[PC_BottomCenter] ? pv.AgainstGround = true : pv.AgainstGround = false;
	!contact[PC_TopLeft] && contact[PC_LeftLedge] ? pv.AgainstLedgeLeft = true : pv.AgainstLedgeLeft = false;
	!contact[PC_TopRight] && contact[PC_RightLedge] ? pv.AgainstLedgeRight = true : pv.AgainstLedgeRight = false;
	contact[PC_LeftCenter] ? pv.AgainstWallLeft = true : pv.AgainstWallLeft = false;
	contact[PC_RightCenter] ? pv.AgainstWallRight = true : pv.AgainstWallRight = false;



}

void Player::Run() {

	if (!pv.IsJumping &&  pv.AgainstGround && RunButton)vel.x *= RUNMULTPLIER;

}

void Player::Jump() {


	if (!JumpButton) pv.JumpButtonReset = true;


	if (pv.AgainstGround && pv.JumpButtonReset && pv.AgainstGroundCounter > 0 && JumpButton) {
		pv.IsJumping = true;
		pv.JumpButtonReset = false;
	}

	if (pv.IsJumping) {
		// If jump button is no longer pressed
		if (pv.JumpButtonReset) {
			pv.IsJumping = false;
			
		}
		else {
			vel.y += JUMPVEL * dTime;
			if (vel.y > MAXJUMPVEL) {
				vel.y = MAXJUMPVEL;
				pv.IsJumping = false;
			}
		}
	}




			


	

	/*
	if (gInput.b.a == false)jumpReleased = true;

	(pv.AgainstGround && jumpReleased && (pv.AgainstGroundCounter > 3)) ? pv.CanJump = true : pv.CanJump = false;


	if (pv.IsJumping) {
		vel.y += dTime * 0.09f;
		if (jumpReleased)pv.IsJumping = false;
	}
	else {



		if (pv.CanJump && gInput.b.a) {
			jumpReleased = false;
			pv.IsJumping = true;
			pv.CanJump = false;
		}




	}
	*/
	/*
	if (gInput.b.a && !pv.IsJumping) {
		if (pv.AgainstGround && jumpReleased && (pv.AgainstGroundCounter > 3)) {

			pv.IsJumping = true;
			jumpReleased = false;
			pv.AgainstGroundCounter = 0;
			pv.JumpTimeCounter = 0;
		}
	}

	if (pv.IsJumping) {
		if (jumpReleased == false) {
			pv.JumpTimeCounter += dTime;
			vel.y += dTime * 0.06f;
			if (vel.y > 2.0f) {
				vel.y = 2.0f;
				pv.IsJumping = false;
				pv.JumpTimeCounter = 0;
			}

		}
		else {
			pv.IsJumping = false;
			pv.JumpTimeCounter = 0;

		}
	}
	*/

}

void Player::LedgeClimb() {
	//if (pv.climbing && pv.collidingBelow)pv.climbing = false;

	// If able will climb if b pressed
	if (pv.AgainstLedgeLeft || pv.AgainstLedgeRight) {

		if (gInput.b.x && pv.CanLedgeGrab) {
			vel.y += 0.6f;
			pv.CanLedgeGrab = false;
		}
	}

	/*
	if (pv.AgainstWallRight && (gInput.b.leftStickFloatX > 0.0f) && !pv.AgainstGround) {

	pv.IsWallSliding = true;
	}
	else if (pv.AgainstWallLeft && (gInput.b.leftStickFloatX < 0.0f) && !pv.AgainstGround) {

	pv.IsWallSliding = true;


	}
	else {
	pv.IsWallSliding = false;
	}

	/// Wall jumping
	if (pv.IsWallSliding && gInput.b.a) {
	if (pv.JumpButtonReset) {
	pv.JumpButtonReset = false;
	pv.IsWallSliding = false;
	if (pv.AgainstWallLeft) {
	vel.x = 5.0f;
	vel.y = 0.6f;
	}
	if (pv.AgainstWallRight) {
	vel.x = -5.0f;
	vel.y = 0.6f;

	}

	}
	}

	if (pv.IsWallSliding && !gInput.b.a)pv.JumpButtonReset = true;
	if (pv.IsWallSliding)vel.y *= 0.75f;


	*/


}

void Player::Melee() {

	//If melee attacking
	if (gInput.b.y) {
		if (pv.CanMelee) {
			pv.CanMelee = false;
			m_meleeWeapon.active = true;
		}
	}
	if (m_meleeWeapon.active) {
		m_meleeWeapon.curMeleeCounter += dTime;
		if (m_meleeWeapon.curMeleeCounter > m_meleeWeapon.meleeTime) { // Melee done
			pv.CanMelee = true;
			m_meleeWeapon.active = false;
			m_meleeWeapon.curMeleeCounter = 0;

		}
		else { // Melee Active
			m_meleeWeapon.facing = pv.xFacing;
			m_meleeWeapon.UpdateCollision();
		}
	} // End Melee



}

void Player::Draw() {

	//if (tempVar) 
	sprite.Draw(pos);
	ps1.Draw(pos);
	cs1.Draw(pos);


	if (m_meleeWeapon.active)sprite.Draw({ 0.0f,0.0f,0.0f });

}

void Player::Animation(double deltaTime) {
	if (vel.x < 0) {
		animState = AS_PL_WALKLEFT;
		if (gInput.b.x)animState = AS_PL_RUNLEFT;
	}

	else if (vel.x > 0) {
		animState = AS_PL_WALKRIGHT;
		if (gInput.b.x)animState = AS_PL_RUNRIGHT;
	}
	
	if (gInput.b.leftStickFloatX == 0.0f) {

		if (animState == AS_PL_WALKLEFT)animState = AS_PL_FACINGLEFT;
		if (animState == AS_PL_WALKRIGHT)animState = AS_PL_FACINGRIGHT;
	}
	


	Animate(deltaTime);

}
/// ITEM
void Player::GetItem(int msg, int value){

	switch (msg) {
	case 0:
		Damage(value);
		break;
	case 1:
		Heal(value);
		break;
	case 2:
		AddToInv(value);
		break;
	}
}

void Player::Damage(int value) {

	m_statHP -= value;
}


void Player::Heal(int value) {

	m_statHP += value;
}

void Player::AddToInv(int value) {

	
}

/// Obstacle 

void Player::GetObstacle(int msg, int value) {
	switch (msg) {
	case 0:
		Damage(value);
		break;
	case 1:
		Heal(value);
		break;
	case 2:
		AddToInv(value);
		break;
	}
}





void Player::Animate(double deltaTime) {

	if (animState != prev_animState) { // Instantly play if new animation
		curAnimFrame = 0; 
		sprite.SetSourceRect(AS_PL_FRAMES[animState].frameLoc[curAnimFrame]);
		return;
	}

	elapsedTime += deltaTime;

	if (elapsedTime > 200) { //play frame
		elapsedTime -= 200;

		curAnimFrame++;
		if (curAnimFrame >= AS_PL_FRAMES[animState].numFrames)curAnimFrame = 0;

		sprite.SetSourceRect(AS_PL_FRAMES[animState].frameLoc[curAnimFrame]);
		
	}

}

void Player::UpdateCollision(){
	XMFLOAT2 temp = sprite.GetSprWH();
	col.x = pos.x - (temp.x - colOff.x);
	col.y = pos.y + (temp.y - colOff.y);
	col.z = pos.x + (temp.x - colOff.z);
	col.w = pos.y - (temp.y - colOff.w);

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

void Player::CollidedWith(int type, int value) {
	switch (type) {
	
	case GD_BT_ENEMY:
		
		break;
	}
}

bool Player::IsMeleeFunc() {
	return m_meleeWeapon.active;
}