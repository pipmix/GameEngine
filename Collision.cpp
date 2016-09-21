#include "Collision.h"

RectCollider::RectCollider(){

}

void RectCollider::SetCollision(XMFLOAT4 c){
	m_collision = c;
}

XMFLOAT4 RectCollider::GetCollision(){

	return m_collision;
}
