#include "Map.h"
using namespace std;

Map::Map(){
}

Map::~Map(){
	delete[] m_collisionRects;
	m_collisionRects = nullptr;
}

void Map::Load(){

	//m_numCollisionRects = LoadCollision(m_collisionRects, m_mapName);


	wstring completePathAndName = L"C:/Box/Box Sync/Data/Exporters/BoxCollision/ex1.col";
	string completeName(completePathAndName.begin(), completePathAndName.end());
	string fileName;


	ifstream file(completeName);

	if (file) {



		file >> fileName >> m_numCollisionRects;
		m_collisionRects = new XMFLOAT4[m_numCollisionRects];

		for (int i = 0; i < m_numCollisionRects; i++) {
			file >> m_collisionRects[i].x >> m_collisionRects[i].y >> m_collisionRects[i].z >> m_collisionRects[i].w;
		}
		file.close();

	}
	else {
		Error(L"Cannot open collision", completePathAndName.c_str());
	}





}

void Map::Update(){

}

void Map::Draw(){
}
