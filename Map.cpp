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
	
		
		
	//left = [0].x
	//top = [3].y
	//right = [2].x
	//bottom = [0].y
	//XMFLOAT4 t1 = { 3, -11, 4, -12 };
	//XMFLOAT4 t2 = { -9, -11, -8, -12 };
	//XMFLOAT4 t3 = { -14, -9, -11, -12 };
	XMFLOAT4 t1;
	t1.x = m_collisionRects[5].x;
	t1.y = m_collisionRects[5].y;
	t1.z = m_collisionRects[5].x + m_collisionRects[5].z ;
	t1.w = m_collisionRects[5].y - m_collisionRects[5].w;
	XMFLOAT4 t2;
	t2.x = m_collisionRects[9].x;
	t2.y = m_collisionRects[9].y;
	t2.z = m_collisionRects[9].x + m_collisionRects[9].z ;
	t2.w = m_collisionRects[9].y - m_collisionRects[9].w ;
	XMFLOAT4 t3;
	t3.x = m_collisionRects[8].x;
	t3.y = m_collisionRects[8].y;
	t3.z = m_collisionRects[8].x + m_collisionRects[8].z;
	t3.w = m_collisionRects[8].y - m_collisionRects[8].w;


	rs01.Create(t1);
	rs02.Create(t2);
	rs03.Create(t3);


	//v 3.000000 - 12.000000 0.000000
	//	v 4.000000 - 12.000000 0.000000
	//	v 3.000000 - 11.000000 0.000000
	//	v 4.000000 - 11.000000 0.000000


	//v - 9.000000 - 12.000000 0.000000
	//	v - 8.000000 - 12.000000 0.000000
	//	v - 9.000000 - 11.000000 0.000000
	//	v - 8.000000 - 11.000000 0.000000

	//v - 14.000000 - 12.000000 0.000000
	//	v - 11.000000 - 12.000000 0.000000
	//	v - 14.000000 - 9.000000 0.000000
	//	v - 11.000000 - 9.000000 0.000000




}

void Map::Update(){

}

void Map::Draw(){
	rs01.Draw();
	rs02.Draw();
	rs03.Draw();
}
