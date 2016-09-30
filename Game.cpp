#include "Game.h"

Game::Game(){}


void Game::Load(){

	gCam.Create();
	ui.Create();
	player.pos = { -3.0f,0.0f,0.0f };

	player.Create(DT_WALKTEST, DV_BASICMATRX, DP_BASICMATRX);
	enemy.Create(DT_WALKTEST, DV_BASICMATRX, DP_BASICMATRX);
	
	map1.Load(L"level1");

	itm01.Create(DT_COLORS, DV_BASICMATRX, DP_BASICMATRX);

	circShape.Create(2.0f, 32);
	
	em01.SetFollowPos(&player.pos);
	em01.SetFollowAngle(&player.dir);
	em01.Create();

	geo01.AssignResources(DT_COLORS, DV_BASICNORMAL, DP_BASICNORMAL);
	geo01.Create(3.0f,2.0f,1.0f);


}

void Game::Update(double deltaTime) {

	

	gCam.Update(deltaTime);
	player.Update(deltaTime);
	enemy.Update(deltaTime);
	itm01.Update(deltaTime);
	em01.Update(deltaTime);

	Collisions(deltaTime);


	ui.Update(deltaTime);
}


void Game::Collisions(double deltaTime) {

	cm.Collide(player, map1);
	cm.Collide(enemy, map1);
	//cm.Collide(player, enemy);
	cm.Collide(itm01, map1);
	//cm.Collide(player, itm01);
	//cm.Collide(enemy, em01);

	//if (cm.RectCircleIntersect(player.GetCollision(), XMFLOAT3{ 0.0f,0.0f,0.0f }, 2.0f))itm01.avail = false;



}
void Game::Draw() {

	XMMATRIX tmpCameraScreen = gCam.GetCameraScreenMatrix();
	gContext->UpdateSubresource(gcbPerFrame.Get(), 0, 0, &tmpCameraScreen, 0, 0);


	map1.Draw();
	player.Draw();
	enemy.Draw();
	itm01.Draw();
	circShape.Draw();
	em01.Draw();

	geo01.Draw();


	// UI
	XMMATRIX tmpScreen = gCam.GetScreenMatrix();
	gContext->UpdateSubresource(gcbPerFrame.Get(), 0, 0, &tmpScreen, 0, 0);

	ui.Draw();



}

