#include "Item.h"

Item::Item(){
	m_pos = m_vel = { 0.0f, 0.0f, 0.0f };

	m_pos = { 2.0f, 0.0f, 0.0f };
	//SetSize({ 0.5f,0.5f });
	UpdateCollision();
}

void Item::Create(UINT tex, UINT vShader, UINT pShader) {

	m_sprite.AssignResources(DT_COLORS, DV_BASICMATRX, DP_BASICMATRX);
	m_sprite.SetSourceRect(2);
	//m_sprite.SetDimensions(0.5f,0.5f);
	m_sprite.Create();


}

void Item::SetSize(XMFLOAT2 s) {
	m_size = s;
	UpdateCollision();

}

void Item::Update(double deltaTime){

	m_vel.y -= (deltaTime / 1000);

	if (m_vel.y < -0.218f)m_vel.y = -0.218f;
	MoveBy(m_vel);

}

void Item::Draw(){
	if(avail)m_sprite.Draw(m_pos);
}


XMFLOAT4 Item::GetCollision(){
	return m_collision;
}

void Item::UpdateCollision(){

	m_collision.x = m_pos.x;
	m_collision.y = m_pos.y;
	m_collision.z = m_pos.x + m_size.x;
	m_collision.w = m_pos.y - m_size.y;
}



void Item::MoveBy(XMFLOAT3 p) {

	m_pos.x += p.x;
	m_pos.y += p.y;
	m_pos.z += p.z;
	UpdateCollision();
}