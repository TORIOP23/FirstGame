#pragma once

#include "Game.h"
class GameObject
{
public:
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();
	void Update();   // di chuyen 
	void Render();
private:
	// vị trí ban đầu của bức ảnh
	int xpos;
	int ypos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
};

