#ifndef TESTGAME_H
#define TESTGAME_H

#include "Game.h"

class TestGame : public Game
{
public: 

	TestGame();
	~TestGame();

	void Update();
	void Draw();
	void LoadResources();	

private:

	typedef	Game super;
	Image				*_pImgTest[17];

};

#endif