#ifndef GAME_H
#define GAME_H

#include "Types.h"
#include "ResourceManager.h"

class Game
{
public: 

	Game();
	~Game();

	void Update();
	void Init();
	void Draw();

	void LoadResources();

private:

	ResourceManager		*_pResManager;
	Image				*_pImgTest;

};

#endif