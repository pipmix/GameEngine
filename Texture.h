#pragma once
#include "Headers.h"
#include "Helpers.h"
#include "DataTypes.h"
#include "Strings.h"
using Microsoft::WRL::ComPtr;
using namespace DirectX;

extern ComPtr<ID3D11Device>			gDevice;
extern ComPtr<ID3D11DeviceContext>	gContext;


class Texture {



public:

	Texture();
	void Load(std::wstring fn);
	void LoadAsync(std::wstring fn);
	void SetInfo(int columns, int rows, int width, int height);
	XMFLOAT4 GetSourceRectIndex(int index);
	XMFLOAT4 GetSourceRectIndex(int index_X, int index_Y);

	ComPtr<ID3D11ShaderResourceView>	textureResource;
	ComPtr<ID3D11Resource>	texRes;
	int _columns, _rows, _width, _height;

	float _nX, _nY, _nW, _nH;
	bool _IsTileMap;
	UINT pixelW;
	UINT pixelH;
	bool hasAlpha;
	bool usesPreMul;


private:








};


