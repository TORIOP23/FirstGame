#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

enum Colors
{
	BLACK,
	BLUE,
	GREEN,
	RED,
	YELLOW
};

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int width, int height);
	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }


	static SDL_Renderer* renderer; // su dung chung
	static SDL_Event event;			// khong khoi tao dc bien static trong class
	static bool isRunning;
	//static SDL_Rect camera;


private:
	SDL_Window* window;
};

