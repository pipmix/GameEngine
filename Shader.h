#pragma once
#include "Headers.h"
#include "DataTypes.h"
#include "Helpers.h"
using Microsoft::WRL::ComPtr;


extern ComPtr<ID3D11Device>			gDevice;
extern ComPtr<ID3D11DeviceContext>	gContext;
extern ComPtr<ID3D11Buffer>			gCBperMesh;


class PixelShader {
public:

	PixelShader();
	void Load(std::wstring fn);
	void Set();

	ComPtr<ID3D11PixelShader>	pixelShader;

};

class VertexShader {
public:
	VertexShader();
	void Load(std::wstring fn, VertexType vt);
	void Set();

	ComPtr<ID3D11VertexShader>	vertexShader;
	ComPtr<ID3D11InputLayout>	inputLayout;

};