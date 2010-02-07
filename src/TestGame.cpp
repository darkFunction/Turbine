#include "TestGame.h"

TestGame::TestGame() : super()
{

}

TestGame::~TestGame() 
{

}

void TestGame::LoadResources()
{
	_pImgTest[0] = _pResManager->LoadImage("resources/graphics/test2.png");	

	
	_pResManager->GenerateTextures(Vector2i(MAX_TEXTURE_WIDTH, MAX_TEXTURE_HEIGHT));


}

void TestGame::Update()
{


}



void TestGame::Draw()
{	
	glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);

	_pGfx->DrawImage(_pImgTest[0], 160.0f, 240.0f);
}