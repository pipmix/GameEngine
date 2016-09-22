#pragma once
#include "Sprite.h"
#include "Input.h"
#include "Collision.h"

extern Input gInput;

struct PlayerVariables {
	bool onGround;
	bool cLeft;
	bool cRight;
	bool cTop;
	bool cBottom;
	bool canJump;
	bool onWall;

};


class Player {

public:
			Player	();
	void	Create	(UINT tex, UINT vShader, UINT pShader);
	void	Update	(double deltaTime);
	void	Draw	();

	void	MoveBy	(XMFLOAT3 p);

	XMFLOAT3			pos;
	XMFLOAT3			vel;
	void	SetCollision(XMFLOAT4 c);

	XMFLOAT4 GetCollision();

	PlayerVariables pv;

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
	//RectCollider		collision;

	XMFLOAT4 col;


	

};