#pragma once
#include "Sprite.h"
#include "Input.h"
#include "Collision.h"
#include "Emitter.h"
#include "Shape.h"
#include "GameData.h"

struct MeleeWeapon {
	XMFLOAT4 meleeCol;
	bool active = 0;
	XMFLOAT3* parent;
	float meleeTime = 500.0f;
	float curMeleeCounter = 0.0f;
	int facing = 0;

	float meleeX = 0.25f;
	float meleeY = 0.25f;
	float meleeOffsetX = 1.5f;
	float meleeOffsetY = 1.5f;
	XMFLOAT2 meleeOffset = {0.5f, 0.5f};

	void UpdateCollision() {

		XMFLOAT2 curCol = { parent->x + (facing * meleeOffset.x),  parent->y + (meleeOffset.y) };
		meleeCol = {
			curCol.x - meleeX,
			curCol.y + meleeY,
			curCol.x + meleeX,
			curCol.y - meleeY
		};
	}
	XMFLOAT4 GetCollision() {
		return meleeCol;
	}
};

enum STATE_PLAYER {
	PSTATE_IDLE, PSTATE_JUMPING, PSTATE_CLIMBING, PSTATE_DUCKING, PSTATE_BLOCKING, PSTATE_ONWALL, PSTATE_MELEE
};

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

	bool wallStart;
	bool leftLedgeTopCollide;
	bool leftLedgeUnderCollide;

	bool rightLedgeTopCollide;
	bool rightLedgeUnderCollide;

	bool leftLedgeCollide;
	bool rightLedgeCollide;

	int facing;
	int vFacing;
	bool canMelee;

	bool collidingWithDoor;
	int  doorIdCollidedWith;

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

	void GetItem(int msg, int value);
	void Damage(int value);
	void Heal(int value);
	void AddToInv(int value);

	void GetObstacle(int msg, int value);

	void CollidedWith(int type, int value);

	bool IsMeleeFunc();

	MeleeWeapon m_meleeWeapon;

	GD_BASIC_TYPES m_basicType;

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

	bool isDead;

	STATE_PLAYER m_curState;
	
	int m_statHP;




};