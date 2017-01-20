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





	gCam.SetTarget(player.pos);



	//mainMenuScene.AddModel("triangleSelector", L"triangleSelector", DT_WALL01, DV_BASICLIGHTING, DP_BASICLIGHTING);
	//mainMenuScene.AddModel("titleMesh", L"titleMesh", DT_MAINMENU, DV_BASICLIGHTING, DP_BASICLIGHTING);

	//gameScene;

	//teamSelectScene.AddModel("teamSelect", L"teamSelect", DT_MAINMENU, DV_BASICLIGHTING, DP_BASICLIGHTING);
	//teamSelectScene.AddModel("circleSelect", L"circleSelect", DT_WALL01, DV_BASICLIGHTING, DP_BASICLIGHTING);
	//teamSelectScene.AddModel("cirCurrentSelect", L"cirCurrentSelect", DT_WALL01, DV_BASICLIGHTING, DP_BASICLIGHTING);
	//teamSelectScene.AddModel("rectSelect", L"rectSelect", DT_WALL01, DV_BASICLIGHTING, DP_BASICLIGHTING);

	ChangeState(GS_MAINMENU);



	mainMenuMeshGroup.AddMesh("triangleSelector", DMOD_TRIANGLESELECTOR);
	mainMenuMeshGroup.AddMesh("titleMesh", DMOD_TITLEMESH);

	teamSelectMeshGroup.AddMesh("teamSelect", DMOD_TEAMSELECT);
	teamSelectMeshGroup.AddMesh("circleSelect", DMOD_CIRCLE_SELCT);
	teamSelectMeshGroup.AddMesh("cirCurrentSelect", DMOD_CIRCURRENTSELECT);
	teamSelectMeshGroup.AddMesh("rectSelect", DMOD_RECTSELECT);


	

	//enum D_MODELS { DMOD_TRIANGLESELECTOR, DMOD_TITLEMESH, DMOD_TEAMSELECT, DMOD_CIRCLE_SELCT, DMOD_CIRCURRENTSELECT, DMOD_RECTSELECT, D_MOD_SIZE };


}

void Game::Update(double deltaTime) {

	switch (m_gameState) {

		
		
	case GS_MAINMENU:
		UpdateMainMenu(deltaTime);
		break;
	case GS_TEAMSELECT:
		UpdateTeamSelect(deltaTime);
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

		mainMenuMeshGroup.Draw();
		//gDat.DrawModel(0);
		//gDat.DrawModel(1);
		//gDat.DrawModel(2);
	break;
	case GS_TEAMSELECT:

		teamSelectMeshGroup.Draw();
		//teamSelectScene.DrawScene();

		//for (int i = 0; i < 8; i++) {
		//	if (charSelected[i]) teamSelectScene.DrawModelAt("cirCurrentSelect", teamSelectLocationPoints[i]);//teamSelectScene.GetModel("modId_cirCurrentSelect")->DrawAt(teamSelectLocationPoints[i]);
		//}

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

void Game::ChangeState(GAMESTATE g) {
	int prevGameState = m_gameState;
	m_gameState = g;

	switch (g) {
		case GS_MAINMENU:
			break;
		case GS_TEAMSELECT:
			gCam.MoveTo(0.0f, -3.0f, -32.0f);


			teamSelectMeshGroup.GetSlimMesh("cirCurrentSelect")->MoveTo(XMFLOAT3(-50.0f, 3.0f, 0.0f));
			teamSelectMeshGroup.GetSlimMesh("circleSelect")->MoveTo(XMFLOAT3(-12.0f, 3.0f, 0.0f));


			//teamSelectScene.GetModel("cirCurrentSelect")->MoveTo(XMFLOAT3(-50.0f, 3.0f, 0.0f));
			//teamSelectScene.GetModel("circleSelect")->MoveTo(XMFLOAT3(-12.0f, 3.0f, 0.0f));

			///Reset if re-entering
			for (int i = 0; i < 8; i++) charSelected[i] = 0;
			curNumOfCharSelected = 0;
			
			break;
		case GS_GAME:
			break;

	}

}




void Game::UpdateMainMenu(double dt) {

	gCam.MoveTo(0.0f, 0.0f, -17.0f);


	menuControl.Update(dt);

	switch (menuControl.GetCurrentDirection()) {
	case MCD_UP:
		mainMenuCurSelection--;
		if (mainMenuCurSelection < 0)mainMenuCurSelection = ES_MAINMENU_SELECTION_COUNT - 1;
		break;
	case MCD_DOWN:
		mainMenuCurSelection++;
		if (mainMenuCurSelection > ES_MAINMENU_SELECTION_COUNT-1)mainMenuCurSelection = 0;
		break;

	}

	if (menuControl.IsButtonActionPressed()) {

		switch (mainMenuCurSelection) {
		case ES_MAINMENU_SELECTION_CAMPAIGN:
			ChangeState(GS_TEAMSELECT);
			return;
			break;
		case ES_MAINMENU_SELECTION_SKIRMISH:
			ChangeState(GS_GAME);
			return;
			break;
		case ES_MAINMENU_OPTIONS:
			ChangeState(GS_OPTIONS);
			return;
			break;
		case ES_MAINMENU_SELECTION_EXIT:
			ChangeState(GS_EXIT);
			return;
			break;
		};

	}

	if (mainMenuPrevSelection != mainMenuCurSelection) {
		//mainMenuScene.AddModel("modId_triangleSelector", L"triangleSelector", DT_WALL01, DV_BASICLIGHTING, DP_BASICLIGHTING);
		mainMenuMeshGroup.GetSlimMesh("triangleSelector")->MoveTo(mainMenuLocationPoints[mainMenuCurSelection]);
		//mainMenuScene.GetModel("triangleSelector")->MoveTo(mainMenuLocationPoints[mainMenuCurSelection]);
		//triSelectModel.MoveTo(mainMenuLocationPoints[mainMenuCurSelection]);
	}


	mainMenuPrevSelection = mainMenuCurSelection;





}

//modId_circleSelect
//modId_cirCurrentSelect
void Game::UpdateTeamSelect(double dt) {

	menuControl.Update(dt);

	switch (menuControl.GetCurrentDirection()) {
	case MCD_UP:
		currentTeamSelectCursorLocation--;
		if (currentTeamSelectCursorLocation < 0)currentTeamSelectCursorLocation = maxLocations - 1;
		break;
	case MCD_DOWN:
		currentTeamSelectCursorLocation++;
		if (currentTeamSelectCursorLocation > maxLocations - 1 )currentTeamSelectCursorLocation = 0;
		break;

	}
	teamSelectMeshGroup.GetSlimMesh("circleSelect")->MoveTo(teamSelectLocationPoints[currentTeamSelectCursorLocation]);
	//teamSelectScene.GetModel("circleSelect")->MoveTo(teamSelectLocationPoints[currentTeamSelectCursorLocation]);



	if (menuControl.IsButtonActionPressed()) {

		if (curNumOfCharSelected <= maxCharSelection) { // If already selected, deselect
			if (charSelected[currentTeamSelectCursorLocation] == true) {
				charSelected[currentTeamSelectCursorLocation] = false;
				curNumOfCharSelected--;
			}
			else { // select
				curNumOfCharSelected++;
				charSelected[currentTeamSelectCursorLocation] = true;
			}

		}
			//currentTeamSelectCursorLocation
	}


}

/*

///Team Select
bool charSelected[8] = { 0 };
const int maxCharSelection = 4;
int curNumOfCharSelected = 0;
int currentTeamSelectCursorLocation = 0;
const int maxLocations = 10;

const XMFLOAT3 teamSelectLocationPoints[10] = {
XMFLOAT3{ -12.0f, 3.0f, 0.0f},
XMFLOAT3{ -4.0f, 3.0f, 0.0f },
XMFLOAT3{  4.0f, 3.0f, 0.0f },
XMFLOAT3{ 12.0f, 3.0f, 0.0f },
XMFLOAT3{ -12.0f, -4.0f, 0.0f },
XMFLOAT3{ -4.0f, -4.0f, 0.0f },
XMFLOAT3{ 4.0f, -4.0f, 0.0f },
XMFLOAT3{ 12.0f, -4.0f, 0.0f },
XMFLOAT3{ -13.0f, -11.0f, 0.0f },
XMFLOAT3{ 13.0f, -11.0f, 0.0f },
};

*/