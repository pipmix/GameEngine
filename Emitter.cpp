#include "Emitter.h"


Particle::Particle() : m_pos(0.0f, 0.0f, 0.0f), m_vel(0.0f, 0.0f, 0.0f), m_acc(0.0f, -0.06f, 0.0f) {

}


void Particle::Update(float t){

	m_pos.x += m_vel.x * 0.01f * t;
	m_pos.y += m_vel.y * 0.01f * t;

	m_vel.x += m_acc.x;
	m_vel.y += m_acc.y;
}


void Particle::SetSpeed(float spd) {
	float a = atan2(m_vel.y, m_vel.x); // angle
	m_vel.x = cos(a) * spd;
	m_vel.y = sin(a) * spd;
}

void Particle::SetAngle(float ang) {
	float s = sqrt(m_vel.x*m_vel.x + m_vel.y * m_vel.y); // speed
	m_vel.x = cos(ang) * s;
	m_vel.y = sin(ang) * s;

}

void Particle::SetAcc(XMFLOAT3 acceleration) {
	m_acc = acceleration;

}