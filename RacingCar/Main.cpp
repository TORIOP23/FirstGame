#include <SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	std::cout << "works";
	return 0;
}