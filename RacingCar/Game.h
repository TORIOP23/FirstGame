#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


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


	static SDL_Renderer* renderer; // sẽ dùng ở nhiều nơi 
	static SDL_Event event;			// khong khoi tao dc bien static trong class
	static bool isRunning;
	//static SDL_Rect camera;

	/*enum groupLabels : std::size_t
	{
		groupMap,
		groupPlayers,
		groupColliders,
		groupProjectiles
	};*/

private:
	SDL_Window* window;
};

