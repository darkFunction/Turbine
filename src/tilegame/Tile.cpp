#include "Tile.h"
#include "../TestGame.h"

Tile::Tile(TrianglePos aTriPos)
{
	_positions = aTriPos;
	
}


Tile::~Tile()
{
	
}

void Tile::Draw(Graphics* aGfx)
{
	TriangleType type;

	aGfx->DrawImage(pImgTriangle[TRI_ORANGE], SCREENWIDTH/2, SCREENHEIGHT/2);

	
}