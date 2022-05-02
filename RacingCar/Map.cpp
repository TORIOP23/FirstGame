#include "GameManager.h"
#include "Map.h"
#include "TextureManager.h"
#include <fstream>


Map::Map()
{
	road[0] = NULL;
	for (int i = 1; i < 92; i++)
	{
		std::string temp = "assets/PNG/Tiles/asphaltRoad/asphaltRoad_(" + std::to_string(i) + ").png";
		road[i] = TextureManager::LoadTexture(temp.c_str());
	}

	for (int i = 0; i < 14; i++)
	{
		grass[i] = NULL;
	}

	LoadMap("assets/map.txt");
	src.x = src.y = 0;
	src.w = src.h = 128;

	dest.w = dest.h = 64;
	dest.x = dest.y = 0;
}

Map::~Map()
{
	for (int i = 0; i < 92; i++)
	{
		if (road[i] != NULL)
		{
			SDL_DestroyTexture(road[i]);
			road[i] = NULL;
		}
	}

	for (int i = 0; i < 14; i++)
	{
		if (grass[i] != NULL)
		{
			SDL_DestroyTexture(grass[i]);
			grass[i] = NULL;
		}
	}
}

void Map::LoadMap(std::string filename)
{
	int c;
	std::fstream mapFile;
	mapFile.open(filename);
	if (!mapFile.is_open()) std::cout << "Fail to load map.txt\n";
	for (int row = 0; row < 15; ++row)
	{
		for (int col = 0; col < 25; ++col)
		{
			mapFile >> c;
			map[row][col] = c;
			mapFile.ignore();
		}
	}
	mapFile.close();
	
}

void Map::DrawMap()
{
	int type = 0;
	for (int row = 0; row < 15; ++row)
	{
		for (int col = 0; col < 25; ++col)
		{
			type = map[row][col];
			dest.x = col * 64;
			dest.y = row * 64;
			if (type > 0 && type < 92) {
				TextureManager::Draw(road[type], src, dest);
			}
			
		}
	}
}

