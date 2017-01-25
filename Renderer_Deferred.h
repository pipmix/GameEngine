#pragma once
#include "Headers.h"

class Renderer_Deferred {

public:
private:




	ComPtr<ID3D11Texture2D>	m_backBuffer;
	ComPtr<ID3D11RenderTargetView>	m_backBuffer;
	ComPtr<ID3D11ShaderResourceView>	m_backBuffer;
};