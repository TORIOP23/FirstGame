#pragma once

#include "Game.h"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture*& tex, SDL_Rect src, SDL_Rect dest);
	//static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
	// static hoat dong nhu cac ham khong phai thanh vien nhung truy cap duoc cac bien thanh vien

};
