#include "Game.h"



Game::Game() 
{
	Init();
	LoadResources();
}

Game::~Game()
{
	delete _pResManager;
}

void Game::Init()
{
	
	_pResManager = new ResourceManager();
	

}

void Game::LoadResources()
{
	_pImgTest = _pResManager->LoadImage("resources/graphics/test.png");
	
	_pResManager->GenerateTextures(Vector2i(1024, 1024));


}

void Game::Update()
{


}



void Game::Draw()
{

}