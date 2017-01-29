#include "Dx.h"

Dx::Dx(HWND h) : m_hWnd(h){}

void Dx::Initialize(){

	UpdateWindowInfo();


	// Device and Swapchain
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount								= 1;
	scd.BufferDesc.Width						= m_clientW;
	scd.BufferDesc.Height						= m_clientW;
	scd.BufferDesc.RefreshRate.Numerator		= 60;
	scd.BufferDesc.RefreshRate.Denominator		= 1;
	scd.BufferDesc.Format						= DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferUsage								= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.OutputWindow							= m_hWnd;
	scd.SampleDesc.Count						= 1;
	scd.SampleDesc.Quality						= 0;
	scd.BufferDesc.Scaling						= DXGI_MODE_SCALING_CENTERED;
	scd.Windowed								= TRUE;
	D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0, 0, D3D11_SDK_VERSION, &scd, m_swapChain.GetAddressOf(), gDevice.GetAddressOf(), NULL, gContext.GetAddressOf());
	//gDevice->CreateDeferredContext(0, &gDContext);

	gDevice->CreateDeferredContext(0, &gDContext);

	// Backbuffer
	ComPtr<ID3D11Texture2D> backBufferTexture;
	m_swapChain->GetBuffer(0, IID_PPV_ARGS(backBufferTexture.GetAddressOf()));
	gDevice->CreateRenderTargetView(backBufferTexture.Get(), nullptr, m_backBuffer.ReleaseAndGetAddressOf());

	// Zbuffer
	D3D11_TEXTURE2D_DESC zBufferDesc;
	ZeroMemory(&zBufferDesc, sizeof(zBufferDesc));
	zBufferDesc.Width							= m_clientW;
	zBufferDesc.Height							= m_clientW;
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
	m_viewport.Width = static_cast<float>(m_clientW);
	m_viewport.Height = static_cast<float>(m_clientW);
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;
	m_viewport.TopLeftX = 0;
	m_viewport.TopLeftY = 0;

	CreateStates();
	CreateConstantBuffers();

	InitDeferred();


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

void Dx::InitDeferred(){

	D3D11_TEXTURE2D_DESC gBuf_desc{
		m_clientW, m_clientH, 1, 1, DXGI_FORMAT_UNKNOWN, 1, 0, D3D11_USAGE_DEFAULT,
		D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE, 0, 0 
	};

	gBuf_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	gBuf_desc.Format = DXGI_FORMAT_R24G8_TYPELESS; // depth stencil
	gDevice->CreateTexture2D(&gBuf_desc, nullptr, &m_depthTex);
	

	gBuf_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // colr spec int stencil
	gBuf_desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	gDevice->CreateTexture2D(&gBuf_desc, nullptr, &m_colorTex);

	gBuf_desc.Format = DXGI_FORMAT_R11G11B10_FLOAT; // colr spec int stencil
	gDevice->CreateTexture2D(&gBuf_desc, nullptr, &m_normalTex);

	gBuf_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // spec power
	gDevice->CreateTexture2D(&gBuf_desc, nullptr, &m_specTex);





	D3D11_DEPTH_STENCIL_VIEW_DESC ds_Desc = {
		DXGI_FORMAT_D24_UNORM_S8_UINT, D3D11_DSV_DIMENSION_TEXTURE2D, 0
	};


	gDevice->CreateDepthStencilView(m_depthTex.Get(), &ds_Desc, m_depthDSV.GetAddressOf());

	ds_Desc.Flags = D3D11_DSV_READ_ONLY_DEPTH | D3D11_DSV_READ_ONLY_STENCIL;
	gDevice->CreateDepthStencilView(m_depthTex.Get(), &ds_Desc, m_depthDSV_ro.GetAddressOf());




	D3D11_RENDER_TARGET_VIEW_DESC rt_desc = { DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_RTV_DIMENSION_TEXTURE2D };

	rt_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	gDevice->CreateRenderTargetView(m_colorTex.Get() , &rt_desc, &m_colorRTV );

	rt_desc.Format = DXGI_FORMAT_R11G11B10_FLOAT;
	gDevice->CreateRenderTargetView(m_normalTex.Get(), &rt_desc, &m_normalRTV );

	rt_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	gDevice->CreateRenderTargetView(m_specTex.Get(), &rt_desc, &m_specRTV );



	// Resources
	D3D11_SHADER_RESOURCE_VIEW_DESC res_desc = { DXGI_FORMAT_R24_UNORM_X8_TYPELESS, D3D11_SRV_DIMENSION_TEXTURE2D, 0, 0 };
	
	res_desc.Texture2D.MipLevels = 1;

	res_desc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	gDevice->CreateShaderResourceView(m_depthTex.Get(), &res_desc, &m_depthSRV);

	res_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	gDevice->CreateShaderResourceView(m_colorTex.Get(), &res_desc, &m_colorSRV);

	res_desc.Format = DXGI_FORMAT_R11G11B10_FLOAT;
	gDevice->CreateShaderResourceView(m_normalTex.Get(), &res_desc, &m_normalSRV);

	res_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	gDevice->CreateShaderResourceView(m_specTex.Get(), &res_desc, &m_specSRV);


	D3D11_DEPTH_STENCIL_DESC depth_desc;
	depth_desc.DepthEnable = TRUE;
	depth_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_desc.DepthFunc = D3D11_COMPARISON_LESS;
	depth_desc.StencilEnable = TRUE;
	depth_desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	depth_desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;
	depth_desc.FrontFace =	{ D3D11_STENCIL_OP_REPLACE, D3D11_STENCIL_OP_REPLACE, D3D11_STENCIL_OP_REPLACE, D3D11_COMPARISON_ALWAYS };
	depth_desc.BackFace =	{ D3D11_STENCIL_OP_REPLACE, D3D11_STENCIL_OP_REPLACE, D3D11_STENCIL_OP_REPLACE, D3D11_COMPARISON_ALWAYS };
	gDevice->CreateDepthStencilState(&depth_desc, m_DS_Tut.GetAddressOf());


	// Create constant buffers
	D3D11_BUFFER_DESC cb_desc;
	ZeroMemory(&cb_desc, sizeof(cb_desc));
	cb_desc.Usage = D3D11_USAGE_DYNAMIC;
	cb_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb_desc.ByteWidth = sizeof(TEMP_CBUF);
	gDevice->CreateBuffer(&cb_desc, nullptr, &m_gBuffer);



	D3D11_SAMPLER_DESC sampler_desc;
	ZeroMemory(&sampler_desc, sizeof(sampler_desc));
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = sampler_desc.AddressV = sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.MaxAnisotropy = 1;
	sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;
	gDevice->CreateSamplerState(&sampler_desc, &m_SS_linear);

	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	gDevice->CreateSamplerState(&sampler_desc, &m_SS_point);



}

void Dx::CreateStates(){

	// Sampler States
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.MaxAnisotropy = 0;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
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
	ZeroMemory(&bsd, sizeof(bsd));
	bsd.RenderTarget[0].BlendEnable = FALSE;
	bsd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	gDevice->CreateBlendState(&bsd, &m_BS_solid);


	D3D11_BLEND_DESC bsd_alpha;
	ZeroMemory(&bsd_alpha, sizeof(bsd_alpha));
	bsd_alpha.RenderTarget[0].BlendEnable = true;
	bsd_alpha.RenderTarget[0].SrcBlend = bsd_alpha.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bsd_alpha.RenderTarget[0].DestBlend = bsd_alpha.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	bsd_alpha.RenderTarget[0].BlendOp = bsd_alpha.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bsd_alpha.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	gDevice->CreateBlendState(&bsd_alpha, &m_BS_transparent);


	D3D11_DEPTH_STENCIL_DESC dsd;
	ZeroMemory(&dsd, sizeof(dsd));
	dsd.DepthEnable = true;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS;
	gDevice->CreateDepthStencilState(&dsd, m_DS_default.GetAddressOf());


	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	gDevice->CreateDepthStencilState(&dsd, m_DS_ReadNoWrite.GetAddressOf());

	dsd.DepthEnable = false;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	gDevice->CreateDepthStencilState(&dsd, m_DS_UI.GetAddressOf());

}

void Dx::CreateConstantBuffers(){


	// Vertex Shader Constant Buffers
	D3D11_BUFFER_DESC bd_perFrame;
	ZeroMemory(&bd_perFrame, sizeof(bd_perFrame));
	bd_perFrame.Usage = D3D11_USAGE_DEFAULT;
	bd_perFrame.ByteWidth = sizeof(CB_mmm);
	bd_perFrame.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	gDevice->CreateBuffer(&bd_perFrame, nullptr, &gcbPerFrame);

	D3D11_BUFFER_DESC bd_perMesh;
	ZeroMemory(&bd_perMesh, sizeof(bd_perMesh));
	bd_perMesh.Usage = D3D11_USAGE_DEFAULT;
	bd_perMesh.ByteWidth = sizeof(XMMATRIX);
	bd_perMesh.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	gDevice->CreateBuffer(&bd_perMesh, nullptr, &gcbPerMesh);

	D3D11_BUFFER_DESC bd_perResize;
	ZeroMemory(&bd_perResize, sizeof(bd_perResize));
	bd_perResize.Usage = D3D11_USAGE_DEFAULT;
	bd_perResize.ByteWidth = sizeof(XMFLOAT4);
	bd_perResize.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	gDevice->CreateBuffer(&bd_perResize, nullptr, &m_cbPerResize);


	// Pixel Shader Constant Buffers

	D3D11_BUFFER_DESC bd_cbPS_amb;
	ZeroMemory(&bd_cbPS_amb, sizeof(bd_cbPS_amb));
	bd_cbPS_amb.Usage = D3D11_USAGE_DYNAMIC;
	bd_cbPS_amb.ByteWidth = sizeof(XMFLOAT4)*2;
	bd_cbPS_amb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd_cbPS_amb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	gDevice->CreateBuffer(&bd_cbPS_amb, nullptr, &m_cbPS_amb);


	D3D11_BUFFER_DESC cbPS_lights;
	ZeroMemory(&cbPS_lights, sizeof(cbPS_lights));
	cbPS_lights.Usage = D3D11_USAGE_DYNAMIC;
	cbPS_lights.ByteWidth = sizeof(XMFLOAT4) * 2;
	cbPS_lights.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbPS_lights.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	gDevice->CreateBuffer(&cbPS_lights, nullptr, &m_cbPS_lights);


	


}


void Dx::Update() {

	if (!m_Active)return;

	m_Timer.Update();
	gInput.Update();
	game.Update(m_Timer.GetDelta());

}


void Dx::Draw() {

	if (!m_Active)return;

	ClearFrame();
	gDat.Reset();

	///gContext->PSSetSamplers(0, 1, m_SS_pixelArt.GetAddressOf());
	gContext->RSSetState(m_RS_default.Get());

	///gContext->OMSetDepthStencilState(m_DS_default.Get(), 0);

	//----
	ID3D11DepthStencilState* prevDepthSS;
	UINT nPrevStencilRef;
	gContext->OMGetDepthStencilState(&prevDepthSS, &nPrevStencilRef);
	gContext->PSSetSamplers(0, 1, &m_SS_linear);
	//-----



	gContext->OMSetBlendState(m_BS_transparent.Get(), 0, 0xFFFFFFFF);


	
	gContext->VSSetConstantBuffers(0, 1, gcbPerFrame.GetAddressOf());
	gContext->VSSetConstantBuffers(1, 1, gcbPerMesh.GetAddressOf());
	gContext->VSSetConstantBuffers(2, 1, m_cbPerResize.GetAddressOf());

	gContext->PSSetConstantBuffers(0, 1, m_cbPS_amb.GetAddressOf());
	gContext->PSSetConstantBuffers(1, 1, m_cbPS_lights.GetAddressOf());

	XMFLOAT4 screenDim = { static_cast<float>(m_windowW), static_cast<float>(m_windowH), static_cast<float>(m_clientW),static_cast<float>(m_clientH) };
	gContext->UpdateSubresource(m_cbPerResize.Get(), 0, 0, &screenDim, 0, 0);




	B_F4F4 tmp;
	tmp.f4a = { 0.0f, 0.0f, 0.0f, 0.0f };
	tmp.f4b = { 0.0f, 0.0f, 0.0f, 0.0f };

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	gContext->Map(m_cbPS_amb.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, &tmp, sizeof(XMFLOAT4)* 2);
	gContext->Unmap(m_cbPS_amb.Get(), 0);


	//DefStart();

	game.Draw();
	m_swapChain->Present(1, 0);




	//ID3D11RenderTargetView* rt[3] = { NULL, NULL, NULL };
	//gContext->OMSetRenderTargets(3, rt, m_depthDSV_ro.Get());

}


void Dx::ClearFrame() {
	UpdateWindowInfo();
	float fill[4] = { 0.0f, 0.2f, 0.25f, 1.0f };
	gContext->ClearRenderTargetView(m_backBuffer.Get(), fill);


	//gDContext->ClearRenderTargetView(g_pRenderTargetView, fill);

	gContext->ClearDepthStencilView(m_zBuffer.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	gContext->OMSetRenderTargets(1, m_backBuffer.GetAddressOf(), m_zBuffer.Get());
	gContext->RSSetViewports(1, &m_viewport);


}

void Dx::ResizeWindow() {

}

void Dx::MSG_InactiveWindow(){

	m_Active = false;
	m_Timer.Pause();
}


void Dx::MSG_ActiveWindow() {

	m_Active = true;
	m_Timer.Unpause();
}

void Dx::Msg_Shutdown(){
	CoUninitialize();
	gContext->ClearState();
	
}

float Dx::GetTicks()
{
	return 0.0f;
}

void Dx::DefStart(){


	gContext->ClearDepthStencilView(m_depthDSV.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0, 0);

	float fill[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	gContext->ClearRenderTargetView(m_colorRTV.Get(), fill);
	gContext->ClearRenderTargetView(m_normalRTV.Get(), fill);
	gContext->ClearRenderTargetView(m_specRTV.Get(), fill);

	ID3D11RenderTargetView* rt[3] = { m_colorRTV.Get(), m_normalRTV.Get(), m_specRTV.Get() };
	gContext->OMSetRenderTargets(3, rt, m_depthDSV.Get());

	gContext->OMSetDepthStencilState(m_DS_Tut.Get(), 1);
	//gContext->RSSetViewports(1, &m_viewport);
}

void Dx::DefCommit()
{
}
