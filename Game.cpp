#include "Game.h"

Game::Game(){}


void Game::Load(){

	gCam.Create(CT_PERSP);
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





	//gCam.SetTarget(player.pos, 0);



	ChangeState(GS_MAINMENU);


	mainMenuMeshGroup.AddMesh("triangleSelector", DMOD_TRIANGLESELECTOR);
	mainMenuMeshGroup.AddMesh("titleMesh", DMOD_TITLEMESH);

	teamSelectMeshGroup.AddMesh("teamSelect", DMOD_TEAMSELECT);
	teamSelectMeshGroup.AddMesh("circleSelect", DMOD_CIRCLE_SELCT);
	teamSelectMeshGroup.AddMesh("cirCurrentSelect", DMOD_CIRCURRENTSELECT);
	teamSelectMeshGroup.AddMesh("rectSelect", DMOD_RECTSELECT);

	MG_campaign.AddMesh("roundBaseHighlight", DMOD_ROUNDBASEHIGHLIGHT);
	MG_campaign.AddMesh("roundBase", DMOD_ROUNDBASE);
	MG_campaign.AddMesh("squarePiece", DMOD_SQUAREPIECE);

	MG_C01.AddMesh("areaC01", DMOD_AREAC01);







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
	case GS_CAMPAIGN:
		UpdateCampaign(deltaTime);
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

	if (m_isStateChanging) {
		m_isStateChanging = false;
		return;
	}
	//Set Current frame matrices
	CB_mmm perFrame;
	perFrame.mat1 = gCam.GetCameraScreenMatrix();
	perFrame.mat2 = gCam.GetCameraMatrix();
	perFrame.mat3 = gCam.GetScreenMatrix();
	gContext->UpdateSubresource(gcbPerFrame.Get(), 0, 0, &perFrame, 0, 0);

	//Draw Depending on State
	switch (m_gameState) {
		case GS_MAINMENU:
			mainMenuMeshGroup.Draw();
		break;
		case GS_TEAMSELECT:
			teamSelectMeshGroup.Draw();
			for (int i = 0; i < 8; i++) if (charSelected[i]) gDat.DrawModelAt(DMOD_CIRCURRENTSELECT, teamSelectLocationPoints[i]);
		break;
		case GS_GAME: {
			map1.Draw();
			player.Draw();
			enemy.Draw();
			itm01.Draw();
			circShape.Draw();
			em01.Draw();
			XMMATRIX tmpScreen = gCam.GetScreenMatrix();
			gContext->UpdateSubresource(gcbPerFrame.Get(), 0, 0, &tmpScreen, 0, 0);
			ui.Draw();
		}
		break;
		case GS_CAMPAIGN:
			MG_campaign.Draw();
			MG_C01.Draw();
		break;

	}
}

void Game::ChangeState(GAMESTATE g) {
	int prevGameState = m_gameState;
	m_gameState = g;
	m_isStateChanging = true;

	switch (g) {
		case GS_MAINMENU:
			gCam.MoveTo(0.0f, 0.0f, -17.0f);
			gCam.SetLookAt(XMFLOAT3{ 0.0f, 0.0f, 0.0f });
			//mainMenuCurSelection = 0;
			break;
		case GS_TEAMSELECT:
			gCam.MoveTo(0.0f, -3.0f, -32.0f);
			gCam.SetLookAt(XMFLOAT3{ 0.0f, -3.0f, 0.0f });

			for (int i = 0; i < 8; i++) charSelected[i] = 0;
			curNumOfCharSelected = 0;
			currentTeamSelectCursorLocation = 0;
			
			teamSelectMeshGroup.GetSlimMesh("cirCurrentSelect")->MoveTo(XMFLOAT3(-50.0f, 3.0f, 0.0f));
			teamSelectMeshGroup.GetSlimMesh("circleSelect")->MoveTo(XMFLOAT3(-12.0f, 3.0f, 0.0f));
			break;
		case GS_GAME:
			break;

		case GS_CAMPAIGN:
			gCam.MoveTo(0.0f, 30.0f, -17.0f);
			m_selectionCoord = { 0.0f, 0.0f, 0.0f };


			break;

	}

}




void Game::UpdateMainMenu(double dt) {


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

	int buttonsPressed = menuControl.GetCurrentButtonsPressed();
	if (buttonsPressed != 0) {
		if (buttonsPressed & CBP_CONFIRM) {

			switch (mainMenuCurSelection) {
			case ES_MAINMENU_SELECTION_CAMPAIGN:
				ChangeState(GS_TEAMSELECT);
				return;
				break;
			case ES_MAINMENU_SELECTION_SKIRMISH:
				ChangeState(GS_CAMPAIGN);
				return;
				break;
			case ES_MAINMENU_OPTIONS:
				ChangeState(GS_CAMPAIGN);
				return;
				break;
			case ES_MAINMENU_SELECTION_EXIT:
				ChangeState(GS_TEAMSELECT);
				return;
				break;
			};
		}
	}


	if (mainMenuPrevSelection != mainMenuCurSelection) {

		mainMenuMeshGroup.GetSlimMesh("triangleSelector")->MoveTo(mainMenuLocationPoints[mainMenuCurSelection]);

	}


	mainMenuPrevSelection = mainMenuCurSelection;





}


void Game::UpdateTeamSelect(double dt) {

	menuControl.Update(dt);
	int buttonsPressed = menuControl.GetCurrentButtonsPressed();
// Menu Flow
	switch (menuControl.GetCurrentDirection()) {
		case MCD_UP:
				if (currentTeamSelectCursorLocation < 8 && currentTeamSelectCursorLocation >= 4) currentTeamSelectCursorLocation -= 4;
				else if (currentTeamSelectCursorLocation == 9)currentTeamSelectCursorLocation == 7;
			break;
		case MCD_DOWN:
			if (currentTeamSelectCursorLocation < 4)currentTeamSelectCursorLocation += 4;
			else if (currentTeamSelectCursorLocation < 8) currentTeamSelectCursorLocation = 9;
			break;
		case MCD_LEFT:
			currentTeamSelectCursorLocation--;
			if (currentTeamSelectCursorLocation < 0)currentTeamSelectCursorLocation = maxLocations - 1;
			break;
		case MCD_RIGHT:
			currentTeamSelectCursorLocation++;
			if (currentTeamSelectCursorLocation > maxLocations - 1)currentTeamSelectCursorLocation = 0;
			break;
	}
/// Menu Flow




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

	//if (currentTeamSelectCursorLocation == 9) {
	//	ChangeState(GS_CAMPAIGN);
	//	return;
	//}

	if (currentTeamSelectCursorLocation == 9) {
		if (buttonsPressed & CBP_CONFIRM) {
			ChangeState(GS_CAMPAIGN);
			return;
		}

		if (buttonsPressed & CBP_CANCEL) {
			ChangeState(GS_MAINMENU);
			return;
		}
	}

}

void Game::UpdateCampaign(double dt) {
	
	menuControl.Update(dt);

	int buttonsPressed = menuControl.GetCurrentButtonsPressed();

	if (buttonsPressed & CBP_CONFIRM) {

	}
	if (buttonsPressed & CBP_CANCEL) {
		ChangeState(GS_MAINMENU);
		return;
	}



	switch (menuControl.GetCurrentDirection()) {
	case MCD_UP:
		m_selectionCoord.z += 1.0f;
		break;
	case MCD_DOWN:
		m_selectionCoord.z -= 1.0f;
		break;
	case MCD_LEFT:
		m_selectionCoord.x -= 1.0f;
		break;
	case MCD_RIGHT:
		m_selectionCoord.x += 1.0f;
		break;
	}


	MG_campaign.GetSlimMesh("squarePiece")->MoveTo(m_selectionCoord);

	//float moveZ = (-gInput.b.leftTriggerFloat) + gInput.b.rightTriggerFloat;
	//gCam.MoveBy(gInput.b.rightStickFloatX, gInput.b.rightStickFloatY, moveZ);

	gCam.MoveAlongX(gInput.b.rightStickFloatX);
	gCam.MoveAlongZ(gInput.b.rightStickFloatY);
	gCam.MoveAlongY(gInput.b.leftTriggerFloat + -gInput.b.rightTriggerFloat);
}