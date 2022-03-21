#pragma once

#include "Game.h"
#include <string>

class Map
{
public:

	Map();
	~Map();

	void LoadMap();
	//void AddTile();
	void DrawMap();
private:
	/*std::string texID;
	int mapScale;
	int tileSize;
	int scaledSize;*/

	SDL_Rect src, dest;
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;
	int map[20][25];

};


