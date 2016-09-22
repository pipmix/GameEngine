#include "Map.h"

Map::Map(){
}

Map::~Map(){
	delete[] m_collisionRects;
	m_collisionRects = nullptr;
}

void Map::Load(){

	m_numCollisionRects = LoadCollision(m_collisionRects, m_mapName);

}

void Map::Update(){

}

void Map::Draw(){
}
