#pragma once

#include "GameManager.h"

class GameObject
{
public:
	GameObject(Colors color);
	~GameObject();

	void free();

protected:
	SDL_Texture* objTexture;
};

