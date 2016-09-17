#pragma once
#include "Game.h"


extern ComPtr<ID3D11Device>				gDevice;
extern ComPtr<ID3D11DeviceContext>		gContext;
extern ComPtr<ID3D11DeviceContext>		gDContext;
extern HWND								hWnd;
extern Data								gDat;
extern ComPtr<ID3D11Buffer>				gcbPerMesh;

class Dx {


public:

			Dx(HWND h);
	void	Initialize();
	void	Update();
	void	Draw();
	void	ClearFrame();
	void	UpdateWindowInfo();

	void	CreateStates();
	void	CreateConstantBuffers();


private:

	//Device Resources
	ComPtr<IDXGISwapChain>			m_swapChain;
	ComPtr<ID3D11RenderTargetView>	m_backBuffer;
	ComPtr<ID3D11DepthStencilView>	m_zBuffer;

	//States
	ComPtr<ID3D11SamplerState>		m_SS_pixelArt;
	ComPtr<ID3D11RasterizerState>	m_RS_default;
	ComPtr<ID3D11RasterizerState>	m_RS_wireframe;
	ComPtr<ID3D11DepthStencilState> m_DS_default;
	ComPtr<ID3D11DepthStencilState> m_DS_UI;
	ComPtr<ID3D11BlendState>		m_BS_solid;
	ComPtr<ID3D11BlendState>		m_BS_transparent;

	//Constant Buffers
	
	ComPtr<ID3D11Buffer>			m_cbPerFrame;

	//Other
	D3D11_VIEWPORT					m_viewport;
	ComPtr<ID3D11CommandList>		m_commandList;


	Game game;

	HWND m_hWnd;
	Timer m_Timer;

	long m_clientW, m_clientH, m_windowH, m_windowW;



};