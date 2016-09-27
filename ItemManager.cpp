#include "ItemManager.h"

ItemManager::ItemManager(){
	m_locations = nullptr;
}

ItemManager::~ItemManager(){
	delete[] m_locations;
}

void ItemManager::SpawnItem()
{
}

void ItemManager::Load(wstring fn){


	wstring completePathAndName = L"C:/Box/Box Sync/Data/Exporters/BoxCollision/lev.loc";



	ifstream file(completePathAndName);

	if (file) {

		file >> m_numLocations;
		m_locations = new Location[m_numLocations];


		for (int i = 0; i < m_numLocations; i++) {
			file >> m_locations[i].m_pos.x >> m_locations[i].m_pos.y >> m_locations[i].m_pos.z >> m_locations[i].m_locName;
		}
		file.close();

	}
	else Error(L"Cannot open location", completePathAndName.c_str());
	


}
