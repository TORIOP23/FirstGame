#pragma once

#include "Game.h"
#include <string>

class Map
{
public:

	Map();
	//Map(std::string tID, int ms, int ts);
	~Map();


	void LoadMap(std::string filename);
	//void AddTile();
	void DrawMap();
private:
	/*std::string texID;
	int mapScale;
	int tileSize;
	int scaledSize;*/

	SDL_Rect src, dest;
	SDL_Texture* road[92];
	SDL_Texture* grass[14];
	int map[15][25];

};


