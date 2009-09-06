#ifndef GAME_H
#define GAME_H

#include "Globals.h"
#include "Resources.h"

class Game
{
public: 

	Game();
	~Game();

	void Update();
	void Init();
	void Draw();


private:

	Sprite* testSprite;

};

#endif