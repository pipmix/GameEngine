#pragma once
#include "Headers.h"
#include "DataTypes.h"
#include "Data.h"

extern ComPtr<ID3D11Device>				gDevice;
extern ComPtr<ID3D11DeviceContext>		gContext;
extern Data								gDat;
extern ComPtr<ID3D11Buffer>				gcbPerMesh;

class RectShape {

public:
			RectShape();
	void	Create(XMFLOAT4 r);
	void	Draw();
private:
	UINT						m_numElements;
	ComPtr<ID3D11Buffer>		m_vertexBuffer;


	void SetResources();

	UINT				m_textureID;
	UINT				m_vsID;
	UINT				m_psID;
	UINT				m_topoID;

};