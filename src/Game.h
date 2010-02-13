#ifndef GAME_H
#define GAME_H

#include "Types.h"
#include "ResourceManager.h"
#include "Graphics.h"

class Game
{
public: 

	Game() 
	{	
		_pResManager = new ResourceManager();
		_pGfx = new Graphics();
	}
	virtual ~Game()
	{
		delete _pResManager;
		delete _pGfx;
	}

	
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void LoadResources() = 0;	

protected:

	Graphics			*_pGfx;
	ResourceManager		*_pResManager;
	

};

#endif