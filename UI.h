#pragma once
#include "Headers.h"
#include "Sprite.h"
using Microsoft::WRL::ComPtr;

extern ComPtr<ID3D11Device>			gDevice;
extern ComPtr<ID3D11DeviceContext>	gContext;

class UI {

public:

	UI();
	void Initialize();


private:

	Sprite spr;

};