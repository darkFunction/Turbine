#ifndef TILE_H
#define TILE_H

#include "../Graphics.h"
#include "../Vector2D.h"

enum TriangleType
{
	TRI_RED = 0,
	TRI_BLUE,		
	TRI_GREEN,
	TRI_YELLOW, 
	TRI_DARKBLUE,
	TRI_DARKGREEN,
	TRI_PURPLE,
	TRI_ORANGE,

	NUM_TRIANGLE_TYPES
};


struct TrianglePos
{
	TrianglePos() 
	{
		top = bottom = right = left = TRI_RED;
	}
	TrianglePos(TriangleType aTop, TriangleType aBottom, TriangleType aLeft, TriangleType aRight)
	{
		top = aTop;
		bottom = aBottom;
		left = aLeft;
		right = aRight;
	};	

	TriangleType top;
	TriangleType bottom;
	TriangleType left;
	TriangleType right;
};

class Tile
{
public:
	Tile(TrianglePos aTriPos);
	~Tile();

	static Vector2i Size();

	void Draw(Graphics* aGfx, Vector2i &pos);
	

private:	
	
	TrianglePos triPositions;
};

#endif