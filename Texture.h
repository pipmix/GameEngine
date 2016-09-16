
#include "Headers.h"
#include "Helpers.h"
#include "DataTypes.h"

using Microsoft::WRL::ComPtr;
using namespace DirectX;

extern ComPtr<ID3D11Device>			gDevice;
extern ComPtr<ID3D11DeviceContext>	gContext;
extern ComPtr<ID3D11Buffer>			gCBperMesh;

class Texture {



public:
			Texture();
	void LoadDDS(std::wstring fn);
	void SetInfo(int columns, int rows, int width, int height);
	Box GetSourceRectIndex(int index);
	Box GetSourceRectIndex(int index_X, int index_Y);

	ComPtr<ID3D11ShaderResourceView>	textureResource;
	int _columns, _rows, _width, _height;
	//normalized x y width height 
	float _nX, _nY, _nW, _nH;
	bool _IsTileMap;

};


#pragma once
