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
	_pGfx = new Graphics();

}

void Game::LoadResources()
{
	_pImgTest = _pResManager->LoadImage("resources/graphics/test.png");
	
	_pResManager->GenerateTextures(Vector2i(MAX_TEXTURE_WIDTH, MAX_TEXTURE_HEIGHT));


}

void Game::Update()
{


}



void Game::Draw()
{
	_pGfx->DrawImage(_pImgTest, 30.0f, 30.0f);
}