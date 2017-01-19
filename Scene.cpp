#include "Scene.h"

Scene::Scene(){

}

Scene::~Scene(){
	modelMap.clear();
}

void Scene::ClearScene(){
	/// TODO: do I need to delete
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

void Scene::DrawModelAt(std::string model_ID, XMFLOAT3 locationToDrawAt){
	modelMap[model_ID]->DrawAt(locationToDrawAt);
}

void Scene::UpdateScene(){

	for (auto const& i : modelMap) i.second->Update();

}

Model* Scene::GetModel(std::string model_ID){

	if (modelMap.find(model_ID) == modelMap.end()) Error(L"Model does not exisit in scene", L"TODO: need to convert");
	return modelMap[model_ID];

}
