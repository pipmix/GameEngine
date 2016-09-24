#pragma once
#include "Loader.h"
#include "Shape.h"


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

	LevelShapes	m_levelShapes;
};