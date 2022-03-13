#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 640, SDL_WINDOW_SHOWN);
	SDL_Delay(5000);
	std::cout << "works";
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}