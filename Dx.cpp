#include "Dx.h"

Dx::Dx(HWND h) : m_hWnd(h){}

void Dx::Initialize(){

	UpdateWindowInfo();


	// Device and Swapchain
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount								= 1;
	scd.BufferDesc.Width						= m_windowW;
	scd.BufferDesc.Height						= m_windowH;
	scd.BufferDesc.RefreshRate.Numerator		= 60;
	scd.BufferDesc.RefreshRate.Denominator		= 1;
	scd.BufferDesc.Format						= DXGI_FORMAT_R8G8B8A8_UNORM;;
	scd.BufferUsage								= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow							= m_hWnd;
	scd.SampleDesc.Count						= 1;
	scd.SampleDesc.Quality						= 0;
	scd.BufferDesc.Scaling						= DXGI_MODE_SCALING_CENTERED;
	scd.Windowed								= TRUE;
	D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0, 0, D3D11_SDK_VERSION, &scd, m_swapChain.GetAddressOf(), gDevice.GetAddressOf(), NULL, gContext.GetAddressOf());
	gDevice->CreateDeferredContext(0, &gDContext);

	// Backbuffer
	ComPtr<ID3D11Texture2D> backBufferTexture;
	m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBufferTexture.GetAddressOf()));
	gDevice->CreateRenderTargetView(backBufferTexture.Get(), nullptr, m_backBuffer.ReleaseAndGetAddressOf());

	// Zbuffer
	D3D11_TEXTURE2D_DESC zBufferDesc;
	ZeroMemory(&zBufferDesc, sizeof(zBufferDesc));
	zBufferDesc.Width							= m_windowW;
	zBufferDesc.Height							= m_windowH;
	zBufferDesc.ArraySize						= 1;
	zBufferDesc.MipLevels						= 1;
	zBufferDesc.SampleDesc.Count				= 1;
	zBufferDesc.Format							= DXGI_FORMAT_D24_UNORM_S8_UINT;
	zBufferDesc.BindFlags						= D3D11_BIND_DEPTH_STENCIL;
	ComPtr<ID3D11Texture2D> zbuffertexture;
	gDevice->CreateTexture2D(&zBufferDesc, nullptr, &zbuffertexture);

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory(&dsvd, sizeof(dsvd));
	dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	gDevice->CreateDepthStencilView(zbuffertexture.Get(), &dsvd, m_zBuffer.GetAddressOf());

	// Viewport
	m_viewport.Width = (float)m_windowW;
	m_viewport.Height = (float)m_windowH;
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;
	m_viewport.TopLeftX = 0;
	m_viewport.TopLeftY = 0;

	CreateStates();
	CreateConstantBuffers();

	gDat.LoadData();
	game.Load();

}

void Dx::UpdateWindowInfo(){

	RECT rc = { 0 };
	GetWindowRect(m_hWnd, &rc);
	m_windowW = rc.right - rc.left;
	m_windowH = rc.bottom - rc.top;

	GetClientRect(m_hWnd, &rc);
	m_clientW = rc.right - rc.left;
	m_clientH = rc.bottom - rc.top;


}

void Dx::CreateStates(){

	// Sampler States
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.MaxAnisotropy = 0;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.MaxLOD = 0.0f;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	gDevice->CreateSamplerState(&samplerDesc, &m_SS_pixelArt);

	// Rasterizer States
	D3D11_RASTERIZER_DESC rsd;
	ZeroMemory(&rsd, sizeof(rsd));
	rsd.FillMode = D3D11_FILL_SOLID;
	rsd.CullMode = D3D11_CULL_BACK;
	rsd.FrontCounterClockwise = false;
	rsd.DepthBias = false;
	rsd.DepthBiasClamp = 0;
	rsd.SlopeScaledDepthBias = 0;
	rsd.DepthClipEnable = true;
	rsd.ScissorEnable = false;
	rsd.MultisampleEnable = false;
	rsd.AntialiasedLineEnable = false;

	gDevice->CreateRasterizerState(&rsd, &m_RS_default);

	rsd.FillMode = D3D11_FILL_WIREFRAME;
	gDevice->CreateRasterizerState(&rsd, &m_RS_wireframe);

	// Blend States
	D3D11_BLEND_DESC bsd;
	ZeroMemory(&bsd, sizeof(D3D11_BLEND_DESC));
	bsd.RenderTarget[0].BlendEnable = FALSE;
	bsd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	gDevice->CreateBlendState(&bsd, &m_BS_solid);

	D3D11_DEPTH_STENCIL_DESC dsd;
	ZeroMemory(&dsd, sizeof(dsd));
	dsd.DepthEnable = true;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS;
	gDevice->CreateDepthStencilState(&dsd, m_DS_default.GetAddressOf());

	dsd.DepthEnable = false;;
	gDevice->CreateDepthStencilState(&dsd, m_DS_UI.GetAddressOf());

}

void Dx::CreateConstantBuffers(){




	D3D11_BUFFER_DESC bd_perFrame;
	ZeroMemory(&bd_perFrame, sizeof(bd_perFrame));
	bd_perFrame.Usage = D3D11_USAGE_DEFAULT;
	bd_perFrame.ByteWidth = sizeof(XMMATRIX);
	bd_perFrame.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	gDevice->CreateBuffer(&bd_perFrame, nullptr, &gcbPerFrame);

	D3D11_BUFFER_DESC bd_perMesh;
	ZeroMemory(&bd_perMesh, sizeof(bd_perMesh));
	bd_perMesh.Usage = D3D11_USAGE_DEFAULT;
	bd_perMesh.ByteWidth = sizeof(XMMATRIX);
	bd_perMesh.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	gDevice->CreateBuffer(&bd_perMesh, nullptr, &gcbPerMesh);

}


void Dx::Update() {
	m_Timer.Update();
	game.Update(m_Timer.GetDelta());

}


void Dx::Draw() {

	ClearFrame();
	gDat.Reset();

	gContext->PSSetSamplers(0, 1, m_SS_pixelArt.GetAddressOf());
	gContext->RSSetState(m_RS_default.Get());
	gContext->OMSetDepthStencilState(m_DS_default.Get(), 0);
	
	gContext->VSSetConstantBuffers(0, 1, gcbPerFrame.GetAddressOf());
	gContext->VSSetConstantBuffers(1, 1, gcbPerMesh.GetAddressOf());

	game.Draw();
	m_swapChain->Present(1, 0);


}




void Dx::ClearFrame() {

	float fill[4] = { 0.0f, 0.2f, 0.25f, 1.0f };
	gContext->ClearRenderTargetView(m_backBuffer.Get(), fill);
	gContext->ClearDepthStencilView(m_zBuffer.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	gContext->OMSetRenderTargets(1, m_backBuffer.GetAddressOf(), m_zBuffer.Get());
	gContext->RSSetViewports(1, &m_viewport);

}