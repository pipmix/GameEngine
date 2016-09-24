#include "Game.h"

Game::Game(){}


void Game::Load(){

	gCam.Create();
	ui.Create();
	player.pos = { -2.0f,0.0f,0.0f };

	player.Create(DT_WALKTEST, DV_BASICMATRX, DP_BASICMATRX);
	enemy.Create(DT_WALKTEST, DV_BASICMATRX, DP_BASICMATRX);
	
	map1.Load();

	itm01.Create(DT_COLORS, DV_BASICMATRX, DP_BASICMATRX);





}

void Game::Update(double deltaTime) {

	gCam.Update(deltaTime);
	player.Update(deltaTime);
	enemy.Update(deltaTime);
	itm01.Update(deltaTime);

	cm.Collide(player, map1);
	cm.Collide(enemy, map1);
	cm.Collide(player, enemy);
	cm.Collide(itm01, map1);
	cm.Collide(player, itm01);

	ui.Update(deltaTime);
}

void Game::Draw() {

	XMMATRIX tmpCameraScreen = gCam.GetCameraScreenMatrix();
	gContext->UpdateSubresource(gcbPerFrame.Get(), 0, 0, &tmpCameraScreen, 0, 0);


	map1.Draw();
	player.Draw();
	enemy.Draw();
	itm01.Draw();



	// UI
	XMMATRIX tmpScreen = gCam.GetScreenMatrix();
	gContext->UpdateSubresource(gcbPerFrame.Get(), 0, 0, &tmpScreen, 0, 0);

	ui.Draw();



}

