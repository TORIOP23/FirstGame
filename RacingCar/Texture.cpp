// Texture.cpp
// The base class for all textures to be rendered on screen
// Can load full textures, or clipped textures from a spritesheet
// or convert a string into a texture to be rendered

#include "Texture.h"


Texture::Texture(std::string filename)
{
	mGraphics = Graphics::Instance();

	//Loads the texture from the AssetManager to avoid loading textures more than once
	mTex = AssetManager::Instance()->GetTexture(filename);

	//Gets the Width and Height of the texture
	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	//Clipped is false since the image is not loaded from a spritesheet
	mClipped = false;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}

Texture::Texture(std::string filename, int x, int y, int w, int h) 
{
	mGraphics = Graphics::Instance();

	//Loads the texture from the AssetManager to avoid loading textures more than once
	mTex = AssetManager::Instance()->GetTexture(filename);

	//Clipped is true since the image could be loaded from a spritesheet
	mClipped = true;

	mWidth = w;
	mHeight = h;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	//Setting the clipped rectangle to only get the needed texture from the spritesheet
	mClipRect.x = x;
	mClipRect.y = y;
	mClipRect.w = mWidth;
	mClipRect.h = mHeight;
}

Texture::Texture(std::string text, std::string fontPath, int size, SDL_Color color) 
{
	mGraphics = Graphics::Instance();

	//Loads the texture from the AssetManager to avoid loading textures more than once
	mTex = AssetManager::Instance()->GetText(text, fontPath, size, color);

	//Clipped is false since the image is not loaded from a spritesheet
	mClipped = false;

	//Gets the Width and Height of the texture
	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}

Texture::~Texture() 
{
	mTex = nullptr;
	mGraphics = nullptr;
}

int Texture::Width()
{
	return static_cast<int> (mWidth * Scale(world).x);
}

int Texture::Height()
{
	return static_cast<int> (mHeight * Scale(world).y);
}

Vector2 Texture::ScaleDimensions()
{
	Vector2 scaleDimension = Scale();
	scaleDimension.x *= mWidth;
	scaleDimension.y *= mHeight;

	return scaleDimension;
}

void Texture::Render() 
{
	Vector2 pos = Pos(world);
	Vector2 scale = Scale(world);

	//Centers the texture on the texture's world position so that its position is not the top left corner
	mRenderRect.x = static_cast<int>(pos.x - mWidth*scale.x*0.5f);
	mRenderRect.y = static_cast<int>(pos.y - mHeight*scale.y*0.5f);

	//Scales the width and height according to the scale of the GameEntity
	mRenderRect.w = static_cast<int>(mWidth * scale.x);
	mRenderRect.h = static_cast<int>(mHeight * scale.y);

	mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(world));
}

void Texture::Render(int x, int y)
{
	SDL_Rect DesRect;
	DesRect.x = x;
	DesRect.y = y;
	DesRect.w = Width();
	DesRect.h = Height();

	mGraphics->DrawTexture(mTex, NULL, &DesRect);
}