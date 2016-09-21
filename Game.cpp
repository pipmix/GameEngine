#include "Game.h"

Game::Game(){}


void Game::Load(){

	gCam.Create();

	player.Create(DT_WALKTEST, DV_BASICMATRX, DP_BASICMATRX);
	player.SetCollision(XMFLOAT4{ 0.0f, 1.0f, 1.0f, 0.0f });



	// check all objects to see if initilized
	// hard overrides for states for ui

}

void Game::Update(double deltaTime) {
	gCam.Update(deltaTime);
	player.Update(deltaTime);

	cm.Collide(player);
	


}

void Game::Draw() {

	XMMATRIX tmpCameraScreen = gCam.GetCameraScreenMatrix();
	gContext->UpdateSubresource(gcbPerFrame.Get(), 0, 0, &tmpCameraScreen, 0, 0);



	player.Draw();



}

