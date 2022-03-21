#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::isRunning = false;

GameObject* player;

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int width, int height)
{
	int flags = SDL_WINDOW_SHOWN;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}
		isRunning = true;
	}
	// Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		std::cout << "Error : SDL_TTF" << std::endl;
	}
	// Initialize SDL_imgage
	int imgFlags = IMG_INIT_PNG;  //  = 2
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		// IMG_Init returns the flags that loaded successfully. 
		//If the flags that are returned do not contain the flags we requested, 
		//that means there's an error.
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		isRunning = false;
	}

	//
	player = new GameObject("assets/car2.png", 300, 200);


}

void Game::handleEvents()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	player->Update();
}

void Game::render()
{
	SDL_RenderClear(renderer);
	player->Render();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}


