#pragma once

#include "Headers.h"
#include "Data.h"

extern ComPtr<ID3D11Device>				gDevice;
extern ComPtr<ID3D11DeviceContext>		gContext;
extern Data								gDat;
extern ComPtr<ID3D11Buffer>				gcbPerMesh;



class NewSprite{
public:

	
	void SetTexture(UINT tex);
	void SetTexCoord(int col, int row);
	void SetCBPerFrame(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 view, XMFLOAT4X4 projection);
	void SetCBPerMesh(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 world, int sliceIndex);

private:

	struct CbTexCoords{
		float sliceWidth;
		float sliceHeight;
	};

	struct CbPerObject{
		XMFLOAT4X4 world;
		int sliceIndex;
	};

	struct CbPerFrame{
		XMFLOAT4X4 view;
		XMFLOAT4X4 projection;
	};


	ComPtr<ID3D11Buffer>		m_cbPerMesh;
	ComPtr<ID3D11Buffer>		m_cbPerFrame;
	ComPtr<ID3D11Buffer>		m_cbTexCoords;

	//ComPtr<ID3D11Buffer>		m_vertexBuffer;
	//XMFLOAT3			m_pos;
	//XMFLOAT4			m_sourceRect;
	//XMFLOAT4			m_dim;
	//float				m_zd;
	//UINT				m_textureID;
	//UINT				m_vsID;
	//UINT				m_psID;
	//UINT				m_topoID;

};