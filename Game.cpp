#include "Game.h"

Game::Game(){
}


void Game::Load(){

	spr01.AssignResources(DT_WALKTEST, DV_BASICMATRX, DP_BASICMATRX);
	spr01.SetSourceRect(10);
	spr01.Create();



}

void Game::Update(double deltaTime) {

	


}

void Game::Draw() {

	spr01.Draw();



}

