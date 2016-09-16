#pragma once
#include "Headers.h"
using Microsoft::WRL::ComPtr;

extern ComPtr<ID3D11Device>			gDevice;
extern ComPtr<ID3D11DeviceContext>	gContext;
extern ComPtr<ID3D11Buffer>			gCBperMesh;

class UI {

public:

	UI();
	void Initialize();


private:

	ComPtr<ID3D11Buffer> m_indexBuffer;
	ComPtr<ID3D11Buffer> m_vertexBuffer;
	ComPtr<ID3D11InputLayout> m_inputLayout;
	size_t m_vbPosition;

	static std::vector<int> m_indices();

	UINT vsIndex;
	UINT psIndex;


};