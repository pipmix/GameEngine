#include "Game.h"

Game::Game(){}


void Game::Load(){

	gCam.Create();
	ui.Create();

	player.Create(DT_WALKTEST, DV_BASICMATRX, DP_BASICMATRX);
	enemy.Create(DT_WALKTEST, DV_BASICMATRX, DP_BASICMATRX);
	
	map1.Load();





}

void Game::Update(double deltaTime) {

	gCam.Update(deltaTime);
	player.Update(deltaTime);
	enemy.Update(deltaTime);

	cm.Collide(player, map1);
	cm.Collide(enemy, map1);
	cm.Collide(player, enemy);

	ui.Update(deltaTime);
}

void Game::Draw() {

	XMMATRIX tmpCameraScreen = gCam.GetCameraScreenMatrix();
	gContext->UpdateSubresource(gcbPerFrame.Get(), 0, 0, &tmpCameraScreen, 0, 0);


	map1.Draw();
	player.Draw();
	enemy.Draw();




	// UI
	XMMATRIX tmpScreen = gCam.GetScreenMatrix();
	gContext->UpdateSubresource(gcbPerFrame.Get(), 0, 0, &tmpScreen, 0, 0);

	ui.Draw();



}

