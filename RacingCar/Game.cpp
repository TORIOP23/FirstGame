#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "Map.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
bool Game::isRunning = false;

Map* map;
Player* player;

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
		//Set texture filtering to linear
		/*if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}*/
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
	map = new Map();
	player = new Player(RED);
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
	player->HandleInput();
}

void Game::update()
{
	player->Update();
}

void Game::render()
{
	SDL_SetRenderDrawColor(Game::renderer, 50, 160, 97, 255);
	SDL_RenderClear(renderer);
	map->DrawMap();
	player->Draw();
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	window = NULL;
	renderer = NULL;
	IMG_Quit();
	SDL_Quit();
}


