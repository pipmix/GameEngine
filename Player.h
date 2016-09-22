#pragma once
#include "Sprite.h"
#include "Input.h"
#include "Collision.h"

extern Input gInput;

class Player {

public:
			Player	();
	void	Create	(UINT tex, UINT vShader, UINT pShader);
	void	Update	(double deltaTime);
	void	Draw	();

	XMFLOAT3			pos;
	void	SetCollision(XMFLOAT4 c);

private:

	void	Animate(double deltaTime);
	void	UpdateCollision();
	Sprite		sprite;

	
	XMFLOAT3			vel;
	XMFLOAT3			acc;

	XMFLOAT3			prev_pos;
	XMFLOAT3			prev_vel;

	AS_PLAYER			animState = AS_PL_IDLE;
	AS_PLAYER			prev_animState = AS_PL_IDLE;
	int					curAnimFrame;
	double				elapsedTime = 0.0f;
	RectCollider		collision;
	

};