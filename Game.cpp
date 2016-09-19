#include "Game.h"

Game::Game(){
}


void Game::Load(){

	spr01.AssignResources(DT_WALKTEST, DV_BASICMATRX, DP_BASICMATRX);
	spr01.SetSourceRect(10);
	spr01.Create();

	
	/*
	float left = -0.5f;
	float top = 0.5f;
	float right = 0.5f;
	float bottom = -0.5f;
	float depth = 0.0f;


	VertexP verts[] = {

		{ XMFLOAT3{ left,top,depth } },
		{ XMFLOAT3{ right,top,depth } },
		{ XMFLOAT3{ left,bottom,depth } },
		{ XMFLOAT3{ right,bottom,depth } },



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
	*/
	

}

void Game::Update(double deltaTime) {

	


}

void Game::Draw() {

	spr01.Draw();
	/*
	gContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	UINT stride = sizeof(VertexP);
	UINT offset = 0;


	gContext->VSSetShader(gDat.GetVertexShader(DV_BASIC)->vertexShader.Get(), 0, 0);
	gContext->PSSetShader(gDat.GetPixelShader(DP_BASIC)->pixelShader.Get(), 0, 0);

	gContext->IASetVertexBuffers(0, 1, _vertexBuffer.GetAddressOf(), &stride, &offset);
	gContext->IASetInputLayout(gDat.GetVertexShader(DV_BASIC)->inputLayout.Get());

	


	gContext->Draw(_numElements, 0);
	*/


}

