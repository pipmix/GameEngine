#pragma once
#include "Sprite.h"
#include "Input.h"
#include "Collision.h"
#include "Emitter.h"
#include "Shape.h"


extern Input gInput;

struct ObjectVariables {

	bool collidingLeft;
	bool collidingRight;
	bool collidingAbove;
	bool collidingBelow;
	bool collidingLadder;


};


class BlankObject {

public:
				BlankObject		();
	void		Create			(UINT tex, UINT vShader, UINT pShader);
	void		Update			(double deltaTime);
	void		Draw			();

	XMFLOAT3&	GetPosRef		();
	XMFLOAT3	GetPosition		();
	void		MoveBy			(XMFLOAT3 p);
	void		MoveTo			(XMFLOAT3 p);

	void		SetCollision	(XMFLOAT4 c);
	XMFLOAT4	GetCollision	();

	ObjectVariables ov;

	float dir = 0.0f;
	PointShapes ps1;

private:

	void	Animate				(double deltaTime);
	void	UpdateCollision		();
	




	int					curAnimFrame;
	double				elapsedTime = 0.0f;


	Sprite m_sprite;
	XMFLOAT3 m_pos;
	XMFLOAT3 m_vel;
	XMFLOAT4 m_collision;
	CircleShape	m_cirle;;


};