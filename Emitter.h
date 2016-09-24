#pragma once
#include "Headers.h"
#include "Sprite.h"


class Particle {

public:

			Particle	();
	void	Update		(float t);
	void	SetSpeed	(float spd);
	void	SetAngle	(float ang);
	void	SetAcc		(XMFLOAT3 acceleration);

private:

	bool		m_alive;
	float		m_lifeTime;
	XMFLOAT3	m_pos;
	XMFLOAT3	m_vel; //(spd, angle)
	XMFLOAT3	m_acc; //(spd, angle)

};


class Emitter {
public:


private:
	Sprite		m_sprite;
	XMFLOAT3	m_pos;
	XMFLOAT3	m_vel; 



};