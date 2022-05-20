// Graphics.h
// Singleton
// Handle the initialization of the graphics related SDL libraries
// and their release
// Also handles texture and text loading

#pragma once

#include <string>
#include <cstdio>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

class Graphics
{
public:

	static const int SCREEN_WIDTH = 1600;

	static const int SCREEN_HEIGHT = 960;

	const char* WINDOW_TITLE = "Bang Bang";

private:
	//Needed to make Graphics a singleton class
	static Graphics* sInstance;
	//Is set to true if all the graphics libraries initialized correctly
	static bool sInitialized;

	//The window created using SDL
	SDL_Window* mWindow;
	//The renderer used to render all textures
	SDL_Renderer* mRenderer;

public:
	//Returns a pointer to the class instance
	static Graphics* Instance();

	//Release the class instance and sets it back to NULL
	//Set Initialized to false
	static void Release();
	
	//Is true if the SDL libraries initialized correctly 
	static bool Initialized();

	//Loads a texture from file using the given path
	//Note: Shoule only be used by the AssetManager to cache the textures for reuse
	SDL_Texture* LoadTexture(std::string path);	
	
	//renders a texture from using the given font and text
	//cache the text
	//Note: Should only be used by the AssetManager to cache the textures for reuse
	SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);

	//Clears all rendered textures from the back buffer
	//usually used at the begining of the frame's render
	void ClearBackBuffer();


	//Draws the given texture to the back buffer
	void DrawTexture(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Refreshes the back buffer
	//Usually called at then end of the frame's render
	void Render();

private:
	//Constructor is private so that Instance() must be used to get an instance when needed
	Graphics();
	
	//Destructor is private so that the instance can only be destroyed using Release()  
	~Graphics();

	//Used to initialize all the SDL graphic libraries
	bool Init();
};