#include "Game.h"

Game::Game()
{
}


void Game::Load() {


	vs.Load(L"Standard_PU_v", VT_P);
	ps.Load(L"Standard_PU_p");


	float left = -0.5f;
	float top = 0.5f;
	float right = 0.5f;
	float bottom = -0.5f;
	float depth = 0.0f;


	VertexP verts[] = {

		{ XMFLOAT3{left,top,depth}},
		{ XMFLOAT3{right,top,depth} },
		{ XMFLOAT3{ left,bottom,depth } },
		{ XMFLOAT3{right,bottom,depth} },
		


	}; _numElements = ARRAYSIZE(verts);






	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VertexP) * _numElements;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = verts;
	gDevice->CreateBuffer(&bd, &InitData, &_vertexBuffer);


}

void Game::Update(double deltaTime) {


}

void Game::Draw() {

	

	gContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	UINT stride = sizeof(VertexP);
	UINT offset = 0;


	vs.Set();
	ps.Set();

	gContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);
	gContext->IASetInputLayout(vs.inputLayout.Get());


	gContext->Draw(_numElements, 0);


}
