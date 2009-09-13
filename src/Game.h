#ifndef GAME_H
#define GAME_H

#include "Types.h"
#include "ResourceManager.h"
#include "Graphics.h"

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

	Graphics			*_pGfx;
	ResourceManager		*_pResManager;
	Image				*_pImgTest;

};

#endif