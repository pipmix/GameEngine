#include "Emitter.h"


Particle::Particle() : m_pos(0.0f, 0.0f, 0.0f), m_vel(0.0f, 0.0f, 0.0f), m_acc(0.0f, -0.06f, 0.0f), m_alive(false) {

}

void	Particle::SetPos(XMFLOAT3 p) {
	m_pos = p;
}


void		Particle::Update(float t){

	m_pos.x += m_vel.x * 0.01f * t;
	m_pos.y += m_vel.y * 0.01f * t;

	m_vel.x += m_acc.x;
	m_vel.y += m_acc.y;
}
bool		Particle::GetAlive() {
	return m_alive;
}


void		Particle::SetSpeed(float spd) {
	float a = atan2(m_vel.y, m_vel.x); // angle
	m_vel.x = cos(a) * spd;
	m_vel.y = sin(a) * spd;
}

void		Particle::SetAngle(float ang) {
	float s = sqrt(m_vel.x*m_vel.x + m_vel.y * m_vel.y); // speed
	m_vel.x = cos(ang) * s;
	m_vel.y = sin(ang) * s;

}

void		Particle::SetAcc(XMFLOAT3 acceleration) {
	m_acc = acceleration;

}
void		Particle::SetAlive(bool alive) {
	m_alive = alive;
}

XMFLOAT3	Particle::GetPos() {

	return m_pos;
}
//----------------------------------------------------------------
/// Emitter
//----------------------------------------------------------------

Emitter::Emitter() {
		m_pos = { 0.0f,0.0f,0.0f };
		m_followPos = nullptr;
		m_followAngle = nullptr;
		m_numParticles = 25;
}


void	Emitter::SetFollowPos(XMFLOAT3* p) {

	m_useFollowPos = true;
	m_followPos = p;
}

void	Emitter::SetFollowAngle(float* a) {
	m_followAngle = a;
	m_useFollowAngle = true;

}

XMFLOAT4 Emitter::GetCollision(int i) {

	XMFLOAT3 partCol;
	XMFLOAT4 temp;


		partCol = m_particles[i].GetPos();
		temp.x = partCol.x;
		temp.y = partCol.y;
		temp.z = temp.x + 1.0f;
		temp.w = temp.y - 1.0f;

		return temp;

	
}
void	Emitter::Create		() {

	
	m_sprite.AssignResources(DT_COLORS, DV_BASICMATRX, DP_BASICMATRX);
	m_sprite.SetSourceRect(1);
	m_sprite.Create();
	m_particles = new Particle[m_numParticles];
	
}
void	Emitter::Reset		() {

}
void	Emitter::Update		(double deltaTime) {

	m_timeSinceLastFrame += deltaTime;
	if (m_timeSinceLastFrame > m_hold) {

		m_canFire = true;

	}

	if (gInput.b.b)Fire();


	for (int i = 0; i < m_numParticles; i++)
		if (m_particles[i].GetAlive()) {
			m_sprite.Update(deltaTime);
			m_particles[i].Update(deltaTime);
		}

}
void	Emitter::Draw		() {

	for (int i = 0; i < m_numParticles; i++)
		if (m_particles[i].GetAlive()) m_sprite.Draw(m_particles[i].GetPos());
		
		
	
	
}


void Emitter::Fire() {
	

	if (m_canFire) {
		m_timeSinceLastFrame = 0.0f;
		m_useFollowPos ? m_particles[m_partCounter].SetPos(*m_followPos) : m_particles[m_partCounter].SetPos(m_pos);
		m_particles[m_partCounter].SetSpeed(2.0f);
		m_useFollowAngle ? m_particles[m_partCounter].SetAngle(*m_followAngle) : m_particles[m_partCounter].SetAngle(XM_PI);
		
		m_particles[m_partCounter].SetAlive(true);
		m_partCounter++;
		if (m_partCounter >= m_numParticles)m_partCounter = 0;
		m_canFire = false;


	}

}

void	Emitter::ParticleMoveBy(XMFLOAT3 pos, int index) {
	m_particles[index].SetPos(pos);

}