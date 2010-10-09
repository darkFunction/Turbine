#include "TileGame.h"

#include "Tile.h"

TileGame::TileGame() : super()
{
	pBoard = new Board(3, 3);
}

TileGame::~TileGame() 
{
	UnloadResources();
}

void TileGame::LoadResources()
{	
	pImgTriangle[TRI_RED] = _pResManager->LoadImage("resources/graphics/tiles/red.png");	
	pImgTriangle[TRI_BLUE] = _pResManager->LoadImage("resources/graphics/tiles/blue.png");
	pImgTriangle[TRI_GREEN] = _pResManager->LoadImage("resources/graphics/tiles/green.png");	
	pImgTriangle[TRI_YELLOW] = _pResManager->LoadImage("resources/graphics/tiles/yellow.png");	
	pImgTriangle[TRI_DARKBLUE] = _pResManager->LoadImage("resources/graphics/tiles/dark_blue.png");	
	pImgTriangle[TRI_DARKGREEN] = _pResManager->LoadImage("resources/graphics/tiles/dark_green.png");	
	pImgTriangle[TRI_PURPLE] = _pResManager->LoadImage("resources/graphics/tiles/purple.png");	
	pImgTriangle[TRI_ORANGE] = _pResManager->LoadImage("resources/graphics/tiles/orange.png");	
	
	_pResManager->GenerateTextures(Vector2i(MAX_TEXTURE_WIDTH, MAX_TEXTURE_HEIGHT));
}

void TileGame::UnloadResources()
{
	for (int i=0; i<NUM_TRIANGLE_TYPES; ++i)
	{
		if (pImgTriangle[i])
			delete pImgTriangle[i];
	}
}

void TileGame::Update()
{


}



void TileGame::Draw()
{	
	glClear(GL_COLOR_BUFFER_BIT);


	pBoard->Draw(_pGfx, Vector2i(0,0));
}
