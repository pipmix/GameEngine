#include "Game.h"

Game::Game(){}


void Game::Load(){

	gCam.Create();

	player.Create(DT_WALKTEST, DV_BASICMATRX, DP_BASICMATRX);





	

}

void Game::Update(double deltaTime) {
	gCam.Update(deltaTime);
	player.Update(deltaTime);
	


}

void Game::Draw() {

	XMMATRIX tmpCameraScreen = gCam.GetCameraScreenMatrix();
	gContext->UpdateSubresource(gcbPerFrame.Get(), 0, 0, &tmpCameraScreen, 0, 0);



	player.Draw();



}

