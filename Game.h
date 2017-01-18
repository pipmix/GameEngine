#pragma once
#include "Headers.h"
#include "Timer.h"
#include "Data.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "Input.h"
#include "UI.h"
#include "Map.h"
#include "Model.h"
#include "Item.h"
#include "Geo.h"
#include "Obstacles.h"
#include "MenuControl.h"

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
	GS_TITLE, GS_MAINMENU, GS_GAME 
};

class Game {
public:

			Game();
	void	Load();
	void	Update(double deltaTime);
	void	Draw();
	void	Collisions(double deltaTime);




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

	Model model_TitleMesh;
	Model mainMenuCursor;

	vector<Player>		playerList;
	vector<Enemy>		enemyList;
	vector<Item>		itemList;
	vector<Obstacle>	obstacleList;
	vector<Map>			mapList;
	GAMESTATE m_gameState;

	MenuControl menuControl;



	/// Main Menu 
	float mainMenuTimeCounter = 0.0f;
	int mainMenuCurSelection = 0;
	int mainMenuPrevSelection = -1;
	const int mainMenuNumOfSelection = 5;
	const XMFLOAT3 mainMenuLocationPoints[5] = {
		XMFLOAT3{0.0f,2.0f,0.0f},
		XMFLOAT3{0.0f,0.0f,0.0f},
		XMFLOAT3{0.0f,-2.0f,0.0f},
		XMFLOAT3{0.0f,-4.0f,0.0f},
		XMFLOAT3{0.0f,-5.0f,0.0f}
	};

};