#pragma once
#include "Headers.h"
using namespace DirectX;

enum VertexType {

	VT_P = 0, 
	VT_PU = 1, 
	VT_PNU = 2

};

struct VertexP {

	XMFLOAT3 position;

};

struct VertexPU {

	XMFLOAT3 position;
	XMFLOAT2 texCoord;

};

struct VertexPNU {

	XMFLOAT3 position;
	XMFLOAT3 normal;
	XMFLOAT2 texCoord;

};


static const D3D11_INPUT_ELEMENT_DESC VertexP_Layout[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

static const D3D11_INPUT_ELEMENT_DESC VertexPU_Layout[] = {

	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }

};

static  D3D11_INPUT_ELEMENT_DESC VertexPNU_Layout[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


struct Box {
	float x;
	float y;
	float w;
	float h;
};

struct TexProp {
	int noCols;
	int noRows;
	int tileW;
	int tileH;
};

struct ResourceIDs {
	int m_textureID;
	int m_vsID;
	int m_psID;
	int m_topoID;

};

struct RefrenceData {
	XMFLOAT3*	m_pos;
	float*		m_direction;
};


struct B_F4F4 {
	XMFLOAT4 f4a;
	XMFLOAT4 f4b;
};