#pragma once
#include "Headers.h"
#include "Sprite.h"



class Item {

public:
	Item();

	void		SetSize				(XMFLOAT2 s);
	void		Update				(double deltaTime);
	void		Draw();
	void		Create				(UINT tex, UINT vShader, UINT pShader);
	void		MoveBy				(XMFLOAT3 p);

	XMFLOAT4	GetCollision		();
	void		UpdateCollision		();

	bool avail = true;
	XMFLOAT4 m_collision;

private:

	XMFLOAT3 m_pos;
	XMFLOAT3 m_vel;
	

	XMFLOAT2 m_size;

	Sprite m_sprite;

};