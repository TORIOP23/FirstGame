#include "GameObject.h"
#include "TextureManager.h"	
#include "GameManager.h"

GameObject::GameObject(Colors color)
{
	std::string filename = "assets/PNG/Cars/car_";
	switch (color)
	{
	case Colors::BLACK:
		filename += "black_1.png";
		break;
	case Colors::BLUE:
		filename += "blue_1.png";
		break;
	case Colors::GREEN:
		filename += "green_1.png";
		break;
	case Colors::RED:
		filename += "red_1.png";
		break;
	case Colors::YELLOW:
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
