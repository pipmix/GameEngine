#include "Shape.h"


//-------------------------------------------------------------------------------------------
/// RECTSHAPE
//-------------------------------------------------------------------------------------------
RectShape::RectShape(){

	m_rIds.m_textureID = -1;
	m_rIds.m_vsID = DV_BASICMATRX;
	m_rIds.m_psID = DP_BASIC;;
	m_rIds.m_topoID = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
}

void RectShape::Create(XMFLOAT4 r){

	float left = r.x;
	float top = r.y;
	float right = r.z;
	float bottom = r.w;
	float z = 0.0f;

	VertexP verts[] = {

		VertexP{ XMFLOAT3(left,top,z)},
		VertexP{ XMFLOAT3(right,top,z)},

		VertexP{ XMFLOAT3(right,bottom,z)},
		VertexP{ XMFLOAT3(left,bottom,z)},
		VertexP{ XMFLOAT3(left,top,z)},


	}; m_numElements = ARRAYSIZE(verts);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VertexP) * m_numElements;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = verts;
	gDevice->CreateBuffer(&bd, &InitData, &m_vertexBuffer);


}

void RectShape::Draw() {

	SetResources();
	XMFLOAT3 m_pos = { 0.0f,0.0f,0.0f };
	XMMATRIX tmpWorldMatrix = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	gContext->UpdateSubresource(gcbPerMesh.Get(), 0, 0, &tmpWorldMatrix, 0, 0);
	gContext->Draw(m_numElements, 0);
}

void RectShape::SetResources() {

	gDat.SetResources(m_rIds);
	UINT stride = sizeof(VertexP);
	UINT offset = 0;
	gContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
}


//-------------------------------------------------------------------------------------------
/// LEVEL SHAPES
//-------------------------------------------------------------------------------------------

LevelShapes::LevelShapes() {

	m_rIds.m_textureID = -1;
	m_rIds.m_vsID = DV_BASICMATRX;
	m_rIds.m_psID = DP_BASIC;;
	m_rIds.m_topoID = D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
}

void LevelShapes::Create(XMFLOAT4* rects, int numOfRects) {
	float left, top, right, bottom;
	float z = 0.0f;

	VertexP* verts;
	verts = new VertexP[numOfRects*8];

	for (int i = 0; i < numOfRects; i++) {

		left = rects[i].x;
		top = rects[i].y;
		right = rects[i].z;
		bottom = rects[i].w;

		verts[i * 8 + 0] = VertexP{ XMFLOAT3(left,top,z) };
		verts[i * 8 + 1] = VertexP{ XMFLOAT3(right,top,z) };
		verts[i * 8 + 2] = VertexP{ XMFLOAT3(right,top,z) };
		verts[i * 8 + 3] = VertexP{ XMFLOAT3(right,bottom,z) };
		verts[i * 8 + 4] = VertexP{ XMFLOAT3(right,bottom,z) };
		verts[i * 8 + 5] = VertexP{ XMFLOAT3(left,bottom,z) };
		verts[i * 8 + 6] = VertexP{ XMFLOAT3(left,bottom,z) };
		verts[i * 8 + 7] = VertexP{ XMFLOAT3(left,top,z) };



	}


	m_numElements = numOfRects * 8;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VertexP) * m_numElements;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = verts;
	gDevice->CreateBuffer(&bd, &InitData, &m_vertexBuffer);

	delete[] verts;
	verts = nullptr;
}

void LevelShapes::Draw() {

	SetResources();
	XMFLOAT3 m_pos = { 0.0f,0.0f,0.0f };
	XMMATRIX tmpWorldMatrix = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	gContext->UpdateSubresource(gcbPerMesh.Get(), 0, 0, &tmpWorldMatrix, 0, 0);
	gContext->Draw(m_numElements, 0);
}

void LevelShapes::SetResources() {

	gDat.SetResources(m_rIds);
	UINT stride = sizeof(VertexP);
	UINT offset = 0;
	gContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
}

//-------------------------------------------------------------------------------------------
/// CIRCLE SHAPE
//-------------------------------------------------------------------------------------------
CircleShape::CircleShape() {

	m_rIds.m_textureID = -1;
	m_rIds.m_vsID = DV_BASICMATRX;
	m_rIds.m_psID = DP_BASIC;
	m_rIds.m_topoID = D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP;
}

void CircleShape::SetSegments(int s) {


}
void CircleShape::Create(float rad, int seg) {



	float z = 0.0f;

	VertexP* verts;
	verts = new VertexP[seg+1];
	float tX, tY;

	for (int i = 0; i < seg+1; i++) {
		tX = rad*cos(XM_PI*(i / (seg / 2.0f)));
		tY = rad*sin(XM_PI*(i / (seg / 2.0f)));
	
		verts[i] = VertexP{ XMFLOAT3{ tX, tY, z } };

	}

	m_numElements = seg+1;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VertexP) * m_numElements;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = verts;
	gDevice->CreateBuffer(&bd, &InitData, &m_vertexBuffer);

	delete[] verts;
	verts = nullptr;
}

void CircleShape::Draw() {

	SetResources();
	XMFLOAT3 m_pos = { 0.0f,0.0f,0.0f };
	XMMATRIX tmpWorldMatrix = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
	gContext->UpdateSubresource(gcbPerMesh.Get(), 0, 0, &tmpWorldMatrix, 0, 0);
	gContext->Draw(m_numElements, 0);
}

void CircleShape::Draw(XMFLOAT3 p) {

	SetResources();

	XMMATRIX tmpWorldMatrix = XMMatrixTranslation(p.x, p.y, p.z);
	gContext->UpdateSubresource(gcbPerMesh.Get(), 0, 0, &tmpWorldMatrix, 0, 0);
	gContext->Draw(m_numElements, 0);
}

void CircleShape::SetResources() {

	gDat.SetResources(m_rIds);
	UINT stride = sizeof(VertexP);
	UINT offset = 0;
	gContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
}

//-------------------------------------------------------------------------------------------
/// POINT SHAPES
//-------------------------------------------------------------------------------------------


PointShapes::PointShapes() {

	m_rIds.m_textureID = -1;
	m_rIds.m_vsID = DV_BASICMATRX;
	m_rIds.m_psID = DP_BASIC;
	m_rIds.m_topoID = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;

}

PointShapes::~PointShapes() {

	delete[] m_points;
	m_points = nullptr;


}


void	PointShapes::Create(XMFLOAT3* points, int numOfPoints) {


	VertexP* verts;
	verts = new VertexP[numOfPoints];

	for (int i = 0; i < numOfPoints; i++) {

		verts[i] = VertexP{ points[i] };

	}


	m_numElements = numOfPoints;

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VertexP) * m_numElements;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = verts;
	gDevice->CreateBuffer(&bd, &InitData, &m_vertexBuffer);

	delete[] verts;
	verts = nullptr;

}

void PointShapes::Draw(XMFLOAT3 p) {

	SetResources();
	XMMATRIX tmpWorldMatrix = XMMatrixTranslation(p.x, p.y, p.z);
	gContext->UpdateSubresource(gcbPerMesh.Get(), 0, 0, &tmpWorldMatrix, 0, 0);
	gContext->Draw(m_numElements, 0);


}


void PointShapes::SetResources() {

	gDat.SetResources(m_rIds);
	UINT stride = sizeof(VertexP);
	UINT offset = 0;
	gContext->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
}