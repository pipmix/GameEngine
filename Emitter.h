#pragma once
#include "Headers.h"
#include "Sprite.h"
#include "Input.h"

extern Input gInput;


class Particle {

public:

			Particle	();
	void	Update		(float t);
	void	SetPos		(XMFLOAT3 p);
	void	SetSpeed	(float spd);
	void	SetAngle	(float ang);
	void	SetAlive	(bool alive);
	void	SetAcc		(XMFLOAT3 acceleration);
	XMFLOAT3	GetPos();
	bool		GetAlive();
	void	MovePos		(XMFLOAT3 v);

private:

	bool		m_alive;
	float		m_lifeTime;
	XMFLOAT3	m_pos;
	XMFLOAT3	m_vel; //(spd, angle)
	XMFLOAT3	m_acc; //(spd, angle)
	bool hit = 0;

};


class Emitter {
public:

			Emitter();
	void	SetFollowPos(XMFLOAT3* p);
	void	SetFollowAngle(float* a);
	void	Create();
	void	Reset();
	void	Update(double deltaTime);
	void	Draw();
	void	Fire();
	XMFLOAT4	GetCollision(int i);
	void MoveBy(int i, XMFLOAT3 v);

	void	ParticleMoveBy(XMFLOAT3 pos, int index);

	Particle	*m_particles;
	int			m_numParticles;


private:

	int			m_partCounter = 0;
	Sprite		m_sprite;
	XMFLOAT3	m_pos;
	XMFLOAT3	m_vel; 

	float 		m_timeSinceLastFrame = 0.0f;
	float		m_hold = 80.0f;
	bool		m_canFire = true;

	XMFLOAT3*	m_followPos;
	float*		m_followAngle;
	bool		m_useFollowPos = 0;
	bool		m_useFollowAngle = 0;




};