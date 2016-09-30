#include "Geo.h"

void SphereGeo::Create(int horzSeg, int vertSeg, float radius){

	float begin = 0;
	float end = XM_2PI;

	float begin2 = 0;
	float end2 = XM_PI;
	float end3 = XM_PI;

	int numVerts = (horzSeg + 1)*(vertSeg + 1);

	XMFLOAT3* pos = new XMFLOAT3[numVerts];
	XMFLOAT3* normal = new XMFLOAT3[numVerts];
	XMFLOAT2* txcoord = new XMFLOAT2[numVerts];

	VertexPNU* verts;
	verts = new VertexPNU[numVerts];

	for (int i = 0; i < vertSeg; i++) {


	}
}

/// Cube Geometry

CubeGeo::CubeGeo(){

	m_rIds.m_topoID = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	m_pos = { 0.0f, 0.0f, 0.0f };
}


void CubeGeo::AssignResources(int texID, int vsID, int psID) {

	m_rIds.m_textureID = texID;
	m_rIds.m_vsID = vsID;
	m_rIds.m_psID = psID;

}

void CubeGeo::Create(float width, float height, float depth) {

	VertexPNU verts[] = {
		{ XMFLOAT3(-width, -height, -depth),	XMFLOAT3(0, 0, -1),		XMFLOAT2(0, 1) },
		{ XMFLOAT3(width, -height, -depth),		XMFLOAT3(0, 0, -1),		XMFLOAT2(1, 1) },
		{ XMFLOAT3(-width, height, -depth),		XMFLOAT3(0, 0, -1),		XMFLOAT2(0, 0) },
		{ XMFLOAT3(width, height, -depth),		XMFLOAT3(0, 0, -1),		XMFLOAT2(1, 0) },
		{ XMFLOAT3(-width, height, -depth),		XMFLOAT3(0, 1, -0),		XMFLOAT2(0, 0) },
		{ XMFLOAT3(width, height, -depth),		XMFLOAT3(0, 1, -0),		XMFLOAT2(0, 1) },
		{ XMFLOAT3(-width, height, depth),		XMFLOAT3(0, 1, -0),		XMFLOAT2(1, 0) },
		{ XMFLOAT3(width, height, depth),		XMFLOAT3(0, 1, -0),		XMFLOAT2(1, 1) },
		{ XMFLOAT3(-width, height, depth),		XMFLOAT3(0, 0, 1),		XMFLOAT2(1, 0) },
		{ XMFLOAT3(width, height, depth),		XMFLOAT3(0, 0, 1),		XMFLOAT2(0, 0) },
		{ XMFLOAT3(-width, -height, depth),		XMFLOAT3(0, 0, 1),		XMFLOAT2(1, 1) },
		{ XMFLOAT3(width, -height, depth),		XMFLOAT3(0, 0, 1),		XMFLOAT2(0, 1) },
		{ XMFLOAT3(-width, -height, depth),		XMFLOAT3(0, -1, -0),	XMFLOAT2(1, 0) },
		{ XMFLOAT3(width, -height, depth),		XMFLOAT3(0, -1, -0),	XMFLOAT2(1, 1) },
		{ XMFLOAT3(-width, -height, -depth),	XMFLOAT3(0, -1, -0),	XMFLOAT2(0, 0) },
		{ XMFLOAT3(width, -height, -depth),		XMFLOAT3(0, -1, -0),	XMFLOAT2(0, 1) },
		{ XMFLOAT3(width, -height, -depth),		XMFLOAT3(1, 0, -0),		XMFLOAT2(0, 1) },
		{ XMFLOAT3(width, -height, depth),		XMFLOAT3(1, 0, -0),		XMFLOAT2(1, 1) },
		{ XMFLOAT3(width, height, -depth),		XMFLOAT3(1, 0, -0),		XMFLOAT2(0, 0) },
		{ XMFLOAT3(width, height, depth),		XMFLOAT3(1, 0, -0),		XMFLOAT2(1, 0) },
		{ XMFLOAT3(-width, -height, depth),		XMFLOAT3(-1, 0, -0),	XMFLOAT2(0, 1) },
		{ XMFLOAT3(-width, -height, -depth),	XMFLOAT3(-1, 0, -0),	XMFLOAT2(1, 1) },
		{ XMFLOAT3(-width, height, depth),		XMFLOAT3(-1, 0, -0),	XMFLOAT2(0, 0) },
		{ XMFLOAT3(-width, height, -depth),		XMFLOAT3(-1, 0, -0),	XMFLOAT2(1, 0) },
	}; m_numOfVertices = ARRAYSIZE(verts);

	unsigned short indices[] = {
		2, 1, 0, 3, 1, 2, 6, 5, 4, 7, 5, 6, 10, 9, 8, 11, 9, 10, 14, 13, 12, 15, 13, 14, 18, 17, 16, 19, 17, 18, 22, 21, 20, 23, 21, 22,
	}; m_numOfIndices = ARRAYSIZE(indices); //36

	D3D11_SUBRESOURCE_DATA vertexBufferData = { 0 };
	vertexBufferData.pSysMem = verts;
	vertexBufferData.SysMemPitch = 0;
	vertexBufferData.SysMemSlicePitch = 0;

	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(VertexPNU)*m_numOfVertices, D3D11_BIND_VERTEX_BUFFER);


	D3D11_SUBRESOURCE_DATA indexBufferData = { 0 };
	indexBufferData.pSysMem = indices;
	indexBufferData.SysMemPitch = 0;
	indexBufferData.SysMemSlicePitch = 0;
	CD3D11_BUFFER_DESC indexBufferDesc(sizeof(unsigned short)*m_numOfIndices, D3D11_BIND_INDEX_BUFFER);

	gDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &m_vertexBuffer);
	gDevice->CreateBuffer(&indexBufferDesc, &indexBufferData, &m_indexBuffer);

}

void CubeGeo::Draw() {

	SetResources();

	XMMATRIX tmpWorldMatrix = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	gContext->UpdateSubresource(gcbPerMesh.Get(), 0, 0, &tmpWorldMatrix, 0, 0);
	gContext->DrawIndexed(m_numOfIndices, 0, 0);

}

void CubeGeo::SetResources() {
	gDat.SetResources(m_rIds);

	UINT stride = sizeof(VertexPNU); // make automatic
	UINT offset = 0;

	gContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	gContext->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);


}
