#include "Loader.h"
using namespace std;


int LoadCollision(XMFLOAT4* data, std::string fn){

	wstring completePathAndName = L"C:/Box/Box Sync/Data/Exporters/BoxCollision/ex1.col";
	string completeName(completePathAndName.begin(), completePathAndName.end());
	int numOfRects;
	string fileName;


	ifstream file(completeName);

	if (file) {

		file >> fileName >> numOfRects;
		data = new XMFLOAT4[numOfRects];

		for (int i = 0; i < numOfRects; i++) {
			file >> data[i].x >> data[i].y >> data[i].z >> data[i].w;
		}
		file.close();

	}
	else {
		Error(L"Cannot open collision", completePathAndName.c_str());
	}

	return numOfRects;

}
