// Texture.h
// The base class for all textures to be rendered on screen

#pragma once

#include "GameEntity.h"
#include "AssetManager.h"


class Texture : public GameEntity 
{
protected:

	//The SDL_Texture to be rendered
	SDL_Texture* mTex;

	//Used to render the texture
	Graphics* mGraphics;

	//Width of the texture
	int mWidth;
	//Height of the texture
	int mHeight;

	//True if the texture is loaded from a spritesheet
	bool mClipped;

	//Is used to render the texture on the screen
	SDL_Rect mRenderRect;
	//Is used to clip the texture from a spritesheet
	SDL_Rect mClipRect;

public:
	//Loads a whole texture from a file (relative to the exe path)
	//Note: For spritesheets use the other contructor
	Texture(std::string filename);

	//Loads a texture from from file (relative to the exe path)
	//Supports spritesheets
	//x : Start X
	//y : Start Y
	//w : the Width 
	//h	: the Height
	Texture(std::string filename, int x, int y, int w, int h);
	
	//Converts the given text into a texture to be rendered
	//Note: fontpath is relative to the exe path
	//size : The size of the text
	//color : The color of the text
	Texture(std::string text, std::string fontpath, int size, SDL_Color color);
	~Texture();

	// return the width after scale
	int Width();
	// return the height after scale
	int Height();

	Vector2 ScaleDimensions();

	//Called to render the texture to the screen, might want to inherit the texture class later 
	virtual void Render();

	// Use for tile Map
	void Render(int x, int y);

};
