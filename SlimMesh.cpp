#include "SlimMesh.h"

SlimMesh::SlimMesh(){
	m_meshID = -1;
	m_pos = { 0.0f, 0.0f, 0.0f };
	m_visible = 1;
}

void SlimMesh::Hide(){
	m_visible = false;
}

void SlimMesh::Unhide(){
	m_visible = true;
}

void SlimMesh::MoveTo(XMFLOAT3 moveTo){
	m_pos.x = moveTo.x;
	m_pos.y = moveTo.y;
	m_pos.z = moveTo.z;
}

void SlimMesh::MoveBy(XMFLOAT3 moveBy){
	m_pos.x += moveBy.x;
	m_pos.y += moveBy.y;
	m_pos.z += moveBy.z;
}

int SlimMesh::ReturnMeshID()
{
	return m_meshID;
}

XMFLOAT3 SlimMesh::ReturnPOS()
{
	return m_pos;
}

void SlimMesh::SetMeshID(int mID){

	m_meshID = mID;
}

