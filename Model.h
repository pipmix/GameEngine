#pragma once
#include "Headers.h"
#include "Data.h"
#include "DataTypes.h"



extern ComPtr<ID3D11Device>				gDevice;
extern ComPtr<ID3D11DeviceContext>		gContext;
extern Data								gDat;
extern ComPtr<ID3D11Buffer>				gcbPerMesh;



class Model{

public:
			Model();
	void	AssignResources(int texID, int vsID, int psID);
	


	void	MoveBy(XMFLOAT3 moveBy);
	void	MoveTo(XMFLOAT3 moveTo);


	void	LoadMesh(wstring fN);

	void	Draw();
	void	DrawAt(XMFLOAT3 toDrawAt);
	void	Update();


	void	Hide();
	void	Unhide();

	



private:

	void SetResources();

	ComPtr<ID3D11Buffer>		m_vertexBuffer;
	ComPtr<ID3D11Buffer>		m_indexBuffer;

	int indexCount;

	float time = 0.0f;

	XMFLOAT3 m_position;
	XMFLOAT3 m_velocity;


	int numOfVertices;
	int numOfIndices;

	ResourceIDs	m_rIds;

	bool m_isVisible = 1;
};

