#pragma once
#include "Sprite.h"
#include "Input.h"
#include "Collision.h"
#include "Shape.h"


struct EnemyVariables {
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
	bool onWall;
	bool collidingLadder;
	int facing;

};


class Enemy {

public:
	Enemy();
	void	Create(UINT tex, UINT vShader, UINT pShader);
	void	Update(double deltaTime);
	void	Draw();

	void	MoveBy(XMFLOAT3 p);
	void	MoveTo(XMFLOAT3 p);

	XMFLOAT3			pos;
	XMFLOAT3			vel;
	void	SetCollision(XMFLOAT4 c);

	XMFLOAT4 GetCollision();

	EnemyVariables ev;

	PointShapes ps1;

private:

	void		Animate(double deltaTime);
	void		UpdateCollision();
	Sprite		sprite;



	XMFLOAT3			acc;

	XMFLOAT3			prev_pos;
	XMFLOAT3			prev_vel;

	AS_PLAYER			animState = AS_PL_IDLE;
	AS_PLAYER			prev_animState = AS_PL_IDLE;
	int					curAnimFrame;
	double				elapsedTime = 0.0f;
	XMFLOAT4 col;

	int xdir = 1;

	float				m_lookRadius;




};