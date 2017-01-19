#pragma once
#include <vector>
#include "Model.h"
#include <string>
#include <map>

class Scene {



public:
	Scene();
	~Scene();


	void ClearScene();
	void AddModel(std::string name, std::wstring fn, int tex, int vs, int ps);

	void DrawScene();
	void UpdateScene();



private:

	std::vector <Model> m_models;
	std::map <std::string, Model*> modelMap;

};