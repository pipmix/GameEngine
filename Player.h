#pragma once
#include "Sprite.h"
#include "Input.h"
#include "Collision.h"
#include "Emitter.h"
#include "Shape.h"


extern Input gInput;

struct PlayerVariables {
	bool jumping;
	bool falling;
	bool doubleJumping;
	bool wallJumping;
	bool climbing;
	bool ducking;
	bool running;
	bool onGround;
	bool collidingLeft;
	bool collidingRight;
	bool collidingAbove;
	bool collidingBelow;
	bool collidingLadder;
	bool onWall;
	bool holdDirection;
	bool applyGrav;


	bool leftLedgeTopCollide;
	bool leftLedgeUnderCollide;

	bool rightLedgeTopCollide;
	bool rightLedgeUnderCollide;

	bool leftLedgeCollide;
	bool rightLedgeCollide;

	int facing;

};


class Player {

public:
			Player	();
	void	Create	(UINT tex, UINT vShader, UINT pShader);
	void	Update	(double deltaTime);
	void	Draw	();
	

	void	MoveBy	(XMFLOAT3 p);
	void	MoveTo	(XMFLOAT3 p);

	XMFLOAT3			pos;
	XMFLOAT3			vel;
	void	SetCollision(XMFLOAT4 c);

	XMFLOAT4 GetCollision();

	PlayerVariables pv;

	float dir = 0.0f;
	PointShapes ps1;

private:

	void	Animate(double deltaTime);
	void	UpdateCollision();
	Sprite		sprite;

	

	XMFLOAT3			acc;

	XMFLOAT3			prev_pos;
	XMFLOAT3			prev_vel;

	AS_PLAYER			animState = AS_PL_IDLE;
	AS_PLAYER			prev_animState = AS_PL_IDLE;
	int					curAnimFrame;
	double				elapsedTime = 0.0f;

	void				Animation(double deltaTime);

	XMFLOAT4 col;

	int oGround = 0;

	bool jumpReleased = 1;

	
	CircleShape	cs1;

	//Emitter	em01;

	

};