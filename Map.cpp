#include "Map.h"
using namespace std;

Map::Map(){
	m_collisionRects = nullptr;
}

Map::~Map(){
	delete[] m_collisionRects;
	m_collisionRects = nullptr;
}

void Map::Load(wstring fN){


	LoadCollision(fN);
	LoadModel(fN);

}

void Map::Update(){
	model.Update();
}

void Map::Draw(){
	model.Draw();
	m_levelShapes.Draw();
}

void Map::LoadCollision(wstring fN){

	wstring completePathAndName = CV_baseDir + CV_collisionDir + fN + CV_collisionFileType;

	ifstream file(completePathAndName);

	if (file) {

		file >> m_mapName >> m_numCollisionRects;
		m_collisionRects = new XMFLOAT4[m_numCollisionRects];

		for (int i = 0; i < m_numCollisionRects; i++) {
			file >> m_collisionRects[i].x >> m_collisionRects[i].y >> m_collisionRects[i].z >> m_collisionRects[i].w;
		}
		file.close();

	}
	else {
		Error(L"Cannot open collision", completePathAndName.c_str());
	}

	// WireFrameDebug
	m_levelShapes.Create(m_collisionRects, m_numCollisionRects);
}

void Map::LoadModel(wstring fN){

	model.AssignResources(DT_QUICKTEST, DV_BASICNORMAL, DP_BASICNORMAL);
	model.LoadMesh(fN);

}
