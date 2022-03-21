#include "Map.h"
#include "TextureManager.h"
#include "Game.h"
#include <fstream>

int lvl1[20][25] = {
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	
};

Map::Map()
{
	//scaledSize = ms * ts;
	dirt = TextureManager::LoadTexture("assets/dirt.png");
	grass = TextureManager::LoadTexture("assets/grass.png");
	water = TextureManager::LoadTexture("assets/water.png");
}

Map::~Map()
{
}


void Map::LoadMap()
{
	
}

void Map::DrawMap()
{}


