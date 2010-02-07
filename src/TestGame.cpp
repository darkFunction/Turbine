#include "TestGame.h"

TestGame::TestGame() : super()
{

}

TestGame::~TestGame() 
{

}

void TestGame::LoadResources()
{
	_pImgTest[0] = _pResManager->LoadImage("resources/graphics/11.png");
	_pImgTest[1] = _pResManager->LoadImage("resources/graphics/2.png");
	_pImgTest[2] = _pResManager->LoadImage("resources/graphics/3png");
	_pImgTest[3] = _pResManager->LoadImage("resources/graphics/4.png");
	_pImgTest[4] = _pResManager->LoadImage("resources/graphics/5.png");
	_pImgTest[5] = _pResManager->LoadImage("resources/graphics/6.png");
	_pImgTest[6] = _pResManager->LoadImage("resources/graphics/7.png");
	_pImgTest[7] = _pResManager->LoadImage("resources/graphics/8.png");
	_pImgTest[8] = _pResManager->LoadImage("resources/graphics/9.png");
	_pImgTest[9] = _pResManager->LoadImage("resources/graphics/10.png");
	

	

	
	_pResManager->GenerateTextures(Vector2i(MAX_TEXTURE_WIDTH, MAX_TEXTURE_HEIGHT));


}

void TestGame::Update()
{


}



void TestGame::Draw()
{	
	glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);

	_pGfx->DrawImage(_pImgTest[0], 30.0f, 30.0f);
}