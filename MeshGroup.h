#pragma once
#include <string>
#include "Data.h"
#include <map>
#include "SlimMesh.h"
#include <utility>

extern Data	gDat;

class MeshGroup{
public:
			MeshGroup();
	void	AddMesh(std::string idName, int num);
	void	Clear();

	void	Draw();


	SlimMesh* GetSlimMesh(std::string model_ID);

private:

	std::map<string, SlimMesh> m_meshes;


};