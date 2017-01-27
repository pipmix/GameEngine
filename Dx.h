#pragma once
#include "Game.h"


extern ComPtr<ID3D11Device>				gDevice;
extern ComPtr<ID3D11DeviceContext>		gContext;
extern ComPtr<ID3D11DeviceContext>		gDContext;
extern HWND								ghWnd;
extern Data								gDat;
extern ComPtr<ID3D11Buffer>				gcbPerMesh;
extern ComPtr<ID3D11Buffer>				gcbPerFrame;
extern Input gInput;


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
	void	ResizeWindow();

	void	MSG_InactiveWindow();
	void	MSG_ActiveWindow();
	void	Msg_Shutdown();

	float	GetTicks();


	void	DefStart();
	void	DefCommit();

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
	ComPtr<ID3D11DepthStencilState> m_DS_ReadNoWrite;
	ComPtr<ID3D11BlendState>		m_BS_solid;
	ComPtr<ID3D11BlendState>		m_BS_transparent;

	//Constant Buffers
	ComPtr<ID3D11Buffer>			m_cbPerResize;

	ComPtr<ID3D11Buffer>			m_cbPS_amb;
	ComPtr<ID3D11Buffer>			m_cbPS_lights;


	//Other
	D3D11_VIEWPORT					m_viewport;
	ComPtr<ID3D11CommandList>		m_commandList;


	Game game;

	HWND m_hWnd;
	Timer m_Timer;

	long m_clientW, m_clientH, m_windowH, m_windowW;

	bool m_Active = true;

	UINT m_maxFPS = 60;


	ComPtr<ID3D11Buffer> m_gBuffer;
	ComPtr<ID3D11Texture2D> m_depthTex;
	ComPtr<ID3D11Texture2D> m_colorTex;
	ComPtr<ID3D11Texture2D> m_normalTex;
	ComPtr<ID3D11Texture2D> m_specTex;
	ComPtr<ID3D11DepthStencilView> m_depthDSV_ro;
	ComPtr<ID3D11RenderTargetView> m_colorRTV;
	ComPtr<ID3D11RenderTargetView> m_normalRTV;
	ComPtr<ID3D11RenderTargetView> m_specRTV;
	ComPtr<ID3D11ShaderResourceView> m_depthSRV;
	ComPtr<ID3D11ShaderResourceView> m_colorSRV;
	ComPtr<ID3D11ShaderResourceView> m_normalSRV;
	ComPtr<ID3D11ShaderResourceView> m_specSRV;



};