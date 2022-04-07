#pragma once

#include "Game.h"
class GameObject
{
public:
	GameObject(Colors color);
	~GameObject();

	void free();

protected:
	SDL_Texture* objTexture;
};

