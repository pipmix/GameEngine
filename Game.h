#pragma once
#include "Headers.h"
#include "Shader.h"


extern ComPtr<ID3D11Device>				gDevice;
extern ComPtr<ID3D11DeviceContext>		gContext;
extern ComPtr<ID3D11DeviceContext>		gDContext;
extern HWND								hWnd;


class Game {
public:

			Game();
	void	Load();
	void	Update(double deltaTime);
	void	Draw();

	VertexShader vs;
	PixelShader ps;

	ComPtr<ID3D11Buffer>		_vertexBuffer;
	UINT						_numElements;
};