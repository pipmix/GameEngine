#pragma once
#include "Headers.h"
#include "DataTypes.h"
#include "Data.h"

extern ComPtr<ID3D11Device>				gDevice;
extern ComPtr<ID3D11DeviceContext>		gContext;
extern Data								gDat;
extern ComPtr<ID3D11Buffer>				gcbPerMesh;

class Geo {

public:

	void					Draw				();
	void					AssignResources		(int texID, int vsID, int psID);

private:

	void					SetResources();

	ResourceIDs				m_rIds;
	UINT					m_numOfVertices;
	UINT					m_numOfIndices;
	ComPtr<ID3D11Buffer>	m_vertexBuffer;
	ComPtr<ID3D11Buffer>	m_indexBuffer;
	XMFLOAT3				m_pos;


};

class SphereGeo {


public:

	void Create(int horzSeg, int vertSeg, float radius);

private:


};

class CubeGeo {


public:
							CubeGeo			();
	void					Create			(float width, float height, float depth);
	void					Draw			();

	void					AssignResources	(int texID, int vsID, int psID);

private:

	void					SetResources();

	ResourceIDs				m_rIds;							
	UINT					m_numOfVertices;
	UINT					m_numOfIndices;
	ComPtr<ID3D11Buffer>	m_vertexBuffer;
	ComPtr<ID3D11Buffer>	m_indexBuffer;
	XMFLOAT3				m_pos;

};