
#include "Board.h"

Board::Board(int aWidth, int aHeight)
{
	width = aWidth;
	height = aHeight;

	tiles = new Tile**[aHeight];
	for (int i=0; i<aWidth; ++i)
		tiles[i] = new Tile*[aWidth];

	Generate();
}

Board::~Board()
{
	for (int y=0; y<height; ++y)		
		for (int x=0; x<width; ++x)		
		{
			if (tiles[y][x])
				delete tiles[y][x];	
		}
	
	for (int i=0; i<width; ++i)
		delete[] tiles[i];
	delete[] tiles;
}

void Board::Generate()
{
	// make tiles
	for (int y=0; y<height; ++y)
	{		
		for (int x=0; x<width; ++x)
		{			
			tiles[y][x] = new Tile(TrianglePos(TRI_RED, TRI_BLUE, TRI_GREEN, TRI_YELLOW));
		}
	}
}

void Board::Draw(Graphics* aGfx, Vector2i &aPos)
{
	Vector2i tileSize = Tile::Size();
	Vector2i boardSize= Vector2i(width * tileSize.x, height * tileSize.y);
	Vector2i startPos = Vector2i(
		aPos.x - ( ((float)boardSize.x)/2 ) + (tileSize.x/2), 
		aPos.y - ( ((float)boardSize.y)/2 ) + (tileSize.y/2)
	);
	Vector2i pos = startPos;

	for (int y=0; y<height; ++y)
	{		
		pos.x = startPos.x;
		for (int x=0; x<width; ++x)
		{			
			tiles[y][x]->Draw(aGfx, pos);
			pos.x += tileSize.x;
		}
		pos.y += tileSize.y;
	}
}