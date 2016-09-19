#include "Sprite.h"

Sprite::Sprite(){
	m_sourceRect = { 0.0f, 0.0f, 1.0f, 1.0f };
	m_topoID = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;
	m_pos = { 0.0f,	0.0f, 0.0f }; 


}

void Sprite::Create(){

	m_dim.x = 0.0f;
	m_dim.y = 1.0f;
	m_dim.z = 1.0f;
	m_dim.w = 0.0f;



	m_zd = 0.0f;

	VertexPU verts[] = {

		{ XMFLOAT3(m_dim.x, m_dim.y, m_zd),		XMFLOAT2(m_sourceRect.x	, m_sourceRect.y) },
		{ XMFLOAT3(m_dim.z, m_dim.y, m_zd),		XMFLOAT2(m_sourceRect.x + m_sourceRect.z, m_sourceRect.y) },
		{ XMFLOAT3(m_dim.x, m_dim.w, m_zd),		XMFLOAT2(m_sourceRect.x	, m_sourceRect.y + m_sourceRect.w) },
		{ XMFLOAT3(m_dim.z, m_dim.w, m_zd),		XMFLOAT2(m_sourceRect.x + m_sourceRect.z, m_sourceRect.y + m_sourceRect.w) }


	};
	m_numElements = ARRAYSIZE(verts);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage				= D3D11_USAGE_DYNAMIC;
	bd.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;
	bd.ByteWidth			= sizeof(VertexPU) * m_numElements;
	bd.BindFlags			= D3D11_BIND_VERTEX_BUFFER;


	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = verts;
	gDevice->CreateBuffer(&bd, &InitData, &m_vertexBuffer);


}

void Sprite::Draw(){

	SetResources();

	
	XMMATRIX worldMatrix = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);// *camera->GetCameraScreenMatrix();
	gContext->UpdateSubresource(gcbPerMesh.Get(), 0, 0, &worldMatrix, 0, 0);
	


	gContext->Draw(m_numElements, 0);

}

void Sprite::MovePos(XMFLOAT3 p)
{
	m_pos.x += p.x;
	m_pos.y += p.y;
	m_pos.z += p.z;
}

void Sprite::SetPos(XMFLOAT3 p){
	m_pos = { p.x, p.y, p.z };
}

XMFLOAT3 Sprite::GetPos()
{
	return XMFLOAT3();
}

void Sprite::AssignResources(UINT texID, UINT vsID, UINT psID){

	m_textureID = texID;
	m_vsID = vsID;
	m_psID = psID;

}

void Sprite::SetSourceRect(int i){
	m_sourceRect = gDat.GetTexture(m_textureID)->GetSourceRectIndex(i);

}

void Sprite::SetResources(){


	if (gDat.m_curTex != m_textureID) {
		gContext->PSSetShaderResources(0, 1, gDat.GetTexture(m_textureID)->textureResource.GetAddressOf());
		gDat.m_curTex = m_textureID;
	}
	if (gDat.m_curVS != m_vsID) {

		gDat.GetVertexShader(m_vsID)->Set();
		gDat.m_curVS = m_vsID;
	}
	if (gDat.m_curPS != m_psID) {
		gDat.GetPixelShader(m_psID)->Set();
		gDat.m_curPS = m_psID;
	}
	if (gDat.m_curTopo != m_topoID) {
		gContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		gDat.m_curTopo = m_topoID;
	}

	UINT stride = sizeof(VertexPU);
	UINT offset = 0;

	gContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);


}

void Sprite::UpdateVertexBuffer() {

	VertexPU verts[] = {


		{ XMFLOAT3(m_dim.x, m_dim.y, m_zd),		XMFLOAT2(m_sourceRect.x	, m_sourceRect.y) },
		{ XMFLOAT3(m_dim.z, m_dim.y, m_zd),		XMFLOAT2(m_sourceRect.x + m_sourceRect.z, m_sourceRect.y) },
		{ XMFLOAT3(m_dim.x, m_dim.w, m_zd),		XMFLOAT2(m_sourceRect.x	, m_sourceRect.y + m_sourceRect.w) },
		{ XMFLOAT3(m_dim.z, m_dim.w, m_zd),		XMFLOAT2(m_sourceRect.x + m_sourceRect.z, m_sourceRect.y + m_sourceRect.w) }


	};
	m_numElements = ARRAYSIZE(verts);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	gContext->Map(m_vertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	memcpy(mappedResource.pData, verts, sizeof(VertexPU) * m_numElements);
	gContext->Unmap(m_vertexBuffer.Get(), 0);


}
