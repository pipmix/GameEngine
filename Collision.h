#pragma once
#include "Headers.h"


class RectCollider {
public:


				RectCollider	();
	void		SetCollision	(XMFLOAT4 c);
	XMFLOAT4	GetCollision	();

private:

	XMFLOAT4 m_collision;


};