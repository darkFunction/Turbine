
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
	for (int i=0; i<width; ++i)
		delete[] tiles[i];
	delete[] tiles;
}

void Board::Generate()
{
	

}

void Board::Draw(Graphics* aGfx)
{
	for (int y=0; y<height; ++y)
	{
		for (int x=0; x<width; ++x)
		{
			tiles[y][x]->Draw(aGfx);
		}
	}
}