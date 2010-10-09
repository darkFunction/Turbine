#ifndef TESTGAME_H
#define TESTGAME_H

#include "Game.h"
#include "tilegame/Board.h"
#include "tilegame/Resources.h"

class TestGame : public Game
{
public: 

	TestGame();
	~TestGame();

	void Update();
	void Draw();
	void LoadResources();	
	void UnloadResources();

private:

	typedef	Game super;		
	
};

#endif