#include "RenderStates.h"

RenderStates::RenderStates(){
	m_curBS = m_curSS = m_curRS = m_curDS = -1;
	m_defBS = m_defSS = m_defRS = m_defDS = -1;;
}

void RenderStates::SetDefaults(){
	gContext->PSSetSamplers(0, 1, m_SS_pixelArt.GetAddressOf());
	gContext->RSSetState(m_RS_default.Get());
	gContext->OMSetDepthStencilState(m_DS_ReadNoWrite.Get(), 0);
	gContext->OMSetBlendState(m_BS_transparent.Get(), 0, 0xFFFFFFFF);

}

void RenderStates::Create(){
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

void RenderStates::SetAll() {

}

void RenderStates::SetBlendState(RS_BS_STATES bs){
}

void RenderStates::SetRasterizerState(RS_RS_STATES rs){
	switch (rs){
		case RS_RS_STATES::RS_RS_DEFAULT:
			gContext->RSSetState(m_RS_default.Get());
			break;
		case RS_RS_STATES::RS_RS_WIREFRAME:
			gContext->RSSetState(m_RS_wireframe.Get());
			break;
	}
	
}

void RenderStates::SetSamplerState(RS_SS_STATES ss){
}

void RenderStates::SetDepthStencilState(RS_DS_STATES ds){
}
