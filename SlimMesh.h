#pragma once
#include "Headers.h"

class SlimMesh {


public:
	SlimMesh();

	void Hide();
	void Unhide();
	void MoveTo(XMFLOAT3 moveTo);
	void MoveBy(XMFLOAT3 moveBy);

	int ReturnMeshID();
	XMFLOAT3 ReturnPOS();


	void SetMeshID(int mID);


private:
	int m_meshID;
	XMFLOAT3 m_pos;
	bool m_visible;

};