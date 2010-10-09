#ifndef TILEGAME_H
#define TILEGAME_H

#include "../Game.h"
#include "Board.h"
#include "Resources.h"

class TileGame : public Game
{
public: 

	TileGame();
	~TileGame();

	void Update();
	void Draw();
	void LoadResources();	
	void UnloadResources();

private:

	typedef	Game super;		
	
	Board*	pBoard;

};

#endif