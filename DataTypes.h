#pragma once
#include "Headers.h"
using namespace DirectX;

struct ConstantBufferMatrixStruct {
	XMFLOAT4X4 mat;
};

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


static const D3D11_INPUT_ELEMENT_DESC VertexP_Layout[] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};


static const D3D11_INPUT_ELEMENT_DESC VertexPU_Layout[] = {

	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }

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