#ifndef BOARD_H
#define BOARD_H

#include "Tile.h"
#include "../Graphics.h"

class Board
{
public:
	Board::Board(int aWidth, int aHeight);
	~Board();
	
	void Draw(Graphics* aGfx, Vector2i &pos);

private:	

	void Generate();

	int width;
	int height;

	Tile ***tiles;

};

#endif