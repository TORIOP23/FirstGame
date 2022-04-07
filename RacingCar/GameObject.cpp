#include "GameObject.h"
#include "TextureManager.h"	
#include "Game.h"

GameObject::GameObject(Colors color)
{
	std::string filename = "assets/PNG/Cars/car_";
	switch (color)
	{
	case BLACK:
		filename += "black_1.png";
		break;
	case BLUE:
		filename += "blue_1.png";
		break;
	case GREEN:
		filename += "green_1.png";
		break;
	case RED:
		filename += "red_1.png";
		break;
	case YELLOW:
		filename += "yellow_1.png";
		break;
	default:
		break;
	}
	objTexture = TextureManager::LoadTexture(filename.c_str());
}

GameObject::~GameObject()
{
	free();
}


void GameObject::free()
{
	//Free texture if it exists
	if (objTexture != NULL)
	{
		SDL_DestroyTexture(objTexture);
		objTexture = NULL;
	}
}
