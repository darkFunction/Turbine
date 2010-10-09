#include "Tile.h"
#include "../TestGame.h"

Tile::Tile(TrianglePos aTriPos)
{
	triPositions = aTriPos;	
}


Tile::~Tile()
{
	
}

Vector2i Tile::Size()
{
	return Vector2i(60, 60);
}

void Tile::Draw(Graphics* aGfx, Vector2i &aPos)
{	
	int triHeight = pImgTriangle[triPositions.top]->_height;

	aGfx->DrawImage(pImgTriangle[triPositions.top], aPos.x, aPos.y, 0.0f);
	aGfx->DrawImage(pImgTriangle[triPositions.bottom], aPos.x, aPos.y + triHeight, 180.0f);

	aGfx->DrawImage(pImgTriangle[triPositions.left], aPos.x - triHeight/2, aPos.y + triHeight/2, 90.0f);
	aGfx->DrawImage(pImgTriangle[triPositions.right], aPos.x + triHeight/2, aPos.y + triHeight/2, 270.0f);
	
}