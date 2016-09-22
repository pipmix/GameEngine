#include "Game.h"

Game::Game(){}


void Game::Load(){

	gCam.Create();
	ui.Create();

	player.Create(DT_WALKTEST, DV_BASICMATRX, DP_BASICMATRX);
	player.SetCollision(XMFLOAT4{ 0.0f, 1.0f, 1.0f, 1.0f });
	player.pos = { 0.0f, 10.0f, 0.0f };

	map1.Load();

	model.AssignResources(DT_QUICKTEST, DV_BASICNORMAL, DP_BASICNORMAL);
	model.LoadMesh();


	
	gCam.MoveBy(0.0f,10.0f,-30.0f);

	// check all objects to see if initilized
	// hard overrides for states for ui

}

void Game::Update(double deltaTime) {

	gCam.Update(deltaTime);
	player.Update(deltaTime);
	model.Update();
	cm.Collide(player, map1);
	ui.Update(deltaTime);
}

void Game::Draw() {

	XMMATRIX tmpCameraScreen = gCam.GetCameraScreenMatrix();
	gContext->UpdateSubresource(gcbPerFrame.Get(), 0, 0, &tmpCameraScreen, 0, 0);

	model.Draw();


	player.Draw();


	// UI
	XMMATRIX tmpScreen = gCam.GetScreenMatrix();
	gContext->UpdateSubresource(gcbPerFrame.Get(), 0, 0, &tmpScreen, 0, 0);

	ui.Draw();



}

