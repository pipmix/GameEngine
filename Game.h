#pragma once
#include "Headers.h"
#include "Timer.h"
#include "Data.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "Input.h"
#include "UI.h"
#include "Map.h"
#include "Item.h"
#include "Geo.h"
#include "Obstacles.h"
#include "MenuControl.h"
#include "Scene.h"

extern ComPtr<ID3D11Device>				gDevice;
extern ComPtr<ID3D11DeviceContext>		gContext;
extern ComPtr<ID3D11DeviceContext>		gDContext;
extern HWND								ghWnd;
extern ComPtr<ID3D11Buffer>				gcbPerMesh;
extern ComPtr<ID3D11Buffer>				gcbPerFrame;
extern Camera gCam;
extern Input gInput;

class Dx;

enum GAMESTATE {
	GS_TITLE, GS_MAINMENU, GS_TEAMSELECT, GS_GAME, GS_OPTIONS, GS_EXIT
};

enum E_MAINMENU_SELECTION {

	ES_MAINMENU_SELECTION_CAMPAIGN, ES_MAINMENU_SELECTION_SKIRMISH, ES_MAINMENU_OPTIONS, ES_MAINMENU_SELECTION_EXIT, ES_MAINMENU_SELECTION_COUNT

};

class Game {
public:

			Game();
	void	Load();
	void	Update(double deltaTime);
	void	Draw();
	void	Collisions(double deltaTime);

	void	ChangeState(GAMESTATE g);


	///updates
	void UpdateMainMenu(double dt);
	void UpdateTeamSelect(double dt);


	Player player;
	Enemy enemy;
	UI		ui;
	Map		map1;
	Item	itm01;
	CircleShape	circShape;
	Emitter	em01;

	CollisionManager cm;


	CubeGeo geo01;

	Model md01;
	Model md02;
	Model md03;
	Model triSelectModel;

	Model model_TitleMesh;
	Model mainMenuCursor;

	vector<Player>		playerList;
	vector<Enemy>		enemyList;
	vector<Item>		itemList;
	vector<Obstacle>	obstacleList;
	vector<Map>			mapList;
	GAMESTATE m_gameState;

	MenuControl menuControl;


	Scene mainMenuScene;
	Scene gameScene;
	Scene teamSelectScene;

	/// Main Menu 
	float mainMenuTimeCounter = 0.0f;
	int mainMenuCurSelection = 0;
	int mainMenuPrevSelection = -1;
	const int mainMenuNumOfSelection = 5;
	const XMFLOAT3 mainMenuLocationPoints[5] = {

		XMFLOAT3{-2.5f, -1.5f,0.0f},
		XMFLOAT3{ -2.5f, -2.5f,0.0f },
		XMFLOAT3{ -2.5f, -3.5f,0.0f },
		XMFLOAT3{ -2.5f, -4.5f,0.0f },
		XMFLOAT3{ 0.0f,2.0f,0.0f },
	};

	///Team Select
	bool charSelected[8];
	const int maxCharSelection = 4;
	int curNumOfCharSelected = 0;
	int currentTeamSelectCursorLocation = 0;
	const int maxLocations = 10;


	const XMFLOAT3 teamSelectLocationPoints[10] = {
		XMFLOAT3{ -12.0f, 3.0f, 0.2f},
		XMFLOAT3{ -4.0f, 3.0f, 0.2f },
		XMFLOAT3{  4.0f, 3.0f, -0.2f },
		XMFLOAT3{ 12.0f, 3.0f, -0.2f },
		XMFLOAT3{ -12.0f, -4.0f, 0.0f },
		XMFLOAT3{ -4.0f, -4.0f, 0.0f },
		XMFLOAT3{ 4.0f, -4.0f, 0.0f },
		XMFLOAT3{ 12.0f, -4.0f, 0.0f },
		XMFLOAT3{ -13.0f, -11.0f, 0.0f },
		XMFLOAT3{ 13.0f, -11.0f, 0.0f },
	};



};