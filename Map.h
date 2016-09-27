#pragma once
#include "Loader.h"
#include "Shape.h"
#include "Model.h"


class Map {

public:

					Map				();
					~Map			();
	void			Load			(wstring fN);


	void			Update			();
	void			Draw			();



	
	XMFLOAT4*		m_collisionRects;
	int				m_numCollisionRects;

	string			m_mapName;
	wstring			m_fileName;

	LevelShapes		m_levelShapes;
	Model			model;

private:

	void			LoadCollision	(wstring fN);
	void			LoadModel		(wstring fN);

};