#include "MeshGroup.h"

MeshGroup::MeshGroup(){

}

void MeshGroup::AddMesh(std::string idName, int num){

	
	//m_meshes.insert()
	m_meshes.insert(std::make_pair(idName, SlimMesh()));
	m_meshes[idName].SetMeshID(num);



}

void MeshGroup::Clear(){

	m_meshes.clear();
}

void MeshGroup::Draw(){

	for (auto& i : m_meshes) gDat.DrawModelAt(i.second.ReturnMeshID(), i.second.ReturnPOS());
}

SlimMesh * MeshGroup::GetSlimMesh(std::string model_ID){

		if (m_meshes.find(model_ID) == m_meshes.end()) Error(L"Model does not exisit in scene", L"TODO: need to convert");
		return & m_meshes[model_ID];


}
