#include "Game.h"

Game::Game(){}


void Game::Load(){

	gCam.Create();
	ui.Create();
	player.pos = { -3.0f,0.0f,0.0f };

	player.Create(DT_CHAR, DV_BASICMATRX, DP_BASICMATRX);
	enemy.Create(DT_WALKTEST, DV_BASICMATRX, DP_BASICMATRX);
	
	map1.Load(L"level1");

	itm01.Create(DT_COLORS, DV_BASICMATRX, DP_BASICMATRX);

	circShape.Create(2.0f, 32);
	
	em01.SetFollowPos(&player.pos);
	em01.SetFollowAngle(&player.dir);
	em01.Create();

	geo01.AssignResources(DT_WALL01, DV_BASICLIGHTING, DP_BASICLIGHTING);
	geo01.Create(3.0f,2.0f,1.0f);

	md01.AssignResources(DT_WALL01, DV_BASICLIGHTING, DP_BASICLIGHTING);
	md01.LoadMesh(L"plane");

	md02.AssignResources(DT_WALL01, DV_BASICLIGHTING, DP_BASICLIGHTING);
	md02.LoadMesh(L"b_sphere");

	md03.AssignResources(DT_WALL01, DV_BASICLIGHTING, DP_BASICLIGHTING);
	md03.LoadMesh(L"b_sphere");

	md03.MoveTo(XMFLOAT3{ -5.0f, 0.0f, 0.0f });


	

	model_TitleMesh.AssignResources(DT_MAINMENU, DV_BASICLIGHTING, DP_BASICLIGHTING);
	model_TitleMesh.LoadMesh(L"titleMesh");
	model_TitleMesh.MoveTo(XMFLOAT3{ 0.0f, 0.0f, 0.0f });

	mainMenuCursor.AssignResources(DT_WALL01, DV_BASICLIGHTING, DP_BASICLIGHTING);
	mainMenuCursor.LoadMesh(L"b_sphere");
	mainMenuCursor.MoveTo(XMFLOAT3{ 0.0f, 0.0f, 0.0f });



	gCam.SetTarget(player.pos);

	m_gameState = GS_MAINMENU;

}

void Game::Update(double deltaTime) {

	switch (m_gameState) {
	case GS_MAINMENU:
		menuControl.Update(deltaTime);

		switch (menuControl.GetCurrentDirection()) {
		case MCD_UP:
			mainMenuCurSelection--;
			if (mainMenuCurSelection < 0)mainMenuCurSelection = mainMenuNumOfSelection;
			break;
		case MCD_DOWN:
			mainMenuCurSelection++;
			if (mainMenuCurSelection > mainMenuNumOfSelection)mainMenuCurSelection = 0;
			break;

		}

		if (mainMenuPrevSelection != mainMenuCurSelection) 
			mainMenuCursor.MoveTo(mainMenuLocationPoints[mainMenuCurSelection]);

		mainMenuPrevSelection = mainMenuCurSelection;


		break;
	case GS_GAME:
		player.Update(deltaTime);
		enemy.Update(deltaTime);
		itm01.Update(deltaTime);
		em01.Update(deltaTime);
		Collisions(deltaTime);
		gCam.Update(deltaTime);
		ui.Update(deltaTime);

		break;
	}

	

}


void Game::Collisions(double deltaTime) {

	cm.Collide(player, map1);
	cm.Collide(enemy, map1);
	cm.Collide(player, enemy);
	cm.Collide(itm01, map1);
	cm.Collide(player, itm01);
	cm.Collide(em01, map1);

	//cm.Collide(enemy, em01);

	//if (cm.RectCircleIntersect(player.GetCollision(), XMFLOAT3{ 0.0f,0.0f,0.0f }, 2.0f))itm01.avail = false;



}
void Game::Draw() {

	CB_mmm perFrame;
	perFrame.mat1 = gCam.GetCameraScreenMatrix();
	perFrame.mat2 = gCam.GetCameraMatrix();
	perFrame.mat3 = gCam.GetScreenMatrix();

	gContext->UpdateSubresource(gcbPerFrame.Get(), 0, 0, &perFrame, 0, 0);


	switch (m_gameState) {
	case GS_MAINMENU:
		model_TitleMesh.Draw();
		mainMenuCursor.Draw();
	break;
	case GS_GAME:
		map1.Draw();
		player.Draw();
		enemy.Draw();
		itm01.Draw();
		circShape.Draw();
		em01.Draw();
		
		XMMATRIX tmpScreen = gCam.GetScreenMatrix();
		gContext->UpdateSubresource(gcbPerFrame.Get(), 0, 0, &tmpScreen, 0, 0);

		ui.Draw();
	break;

	}







}

