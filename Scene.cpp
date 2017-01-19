#include "Scene.h"

Scene::Scene(){

}

Scene::~Scene(){
	modelMap.clear();
}

void Scene::ClearScene(){

	modelMap.clear();

}

void Scene::AddModel(std::string nameID, std::wstring fn, int tex, int vs, int ps){

	modelMap.insert(std::make_pair(nameID, new Model()));
	modelMap[nameID]->AssignResources(tex, vs, ps);
	modelMap[nameID]->LoadMesh(fn);


}



void Scene::DrawScene(){

	for (auto const& i : modelMap) i.second->Draw();
	
}

void Scene::UpdateScene(){

	for (auto const& i : modelMap) i.second->Update();

}
