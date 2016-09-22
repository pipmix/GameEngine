#pragma once
#include "Loader.h"


class Map {

public:

	Map();
	~Map();
	void Load();
	void Update();
	void Draw();


	XMFLOAT4*	m_collisionRects;
	int			m_numCollisionRects;

	std::string		m_mapName;
};