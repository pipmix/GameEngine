#include "Game.h"

Game::Game(){

}


void Game::Load(){

	spr01.AssignResources(DT_WALKTEST, DV_BASICMATRX, DP_BASICMATRX);
	spr01.SetSourceRect(2);
	spr01.Create();

	

}

void Game::Update(double deltaTime) {
	camera.Update(deltaTime);
	spr01.Update(deltaTime);
	


}

void Game::Draw() {

	XMMATRIX tmpCameraScreen = camera.GetCameraScreenMatrix();
	gContext->UpdateSubresource(gcbPerFrame.Get(), 0, 0, &tmpCameraScreen, 0, 0);
	gContext->VSSetConstantBuffers(0, 1, gcbPerFrame.GetAddressOf());


	spr01.Draw();



}

