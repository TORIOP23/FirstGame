#include <string>
#include <fstream>
#include "Map.h"

Map* Map::sInstance = NULL;

Map* Map::Instance()
{
	if (sInstance == NULL)
		sInstance = new Map();
	return sInstance;
}

void Map::Release()
{
	delete sInstance;
	sInstance = NULL;
}

Map::Map()
{
	std::string path = "PNG/environment/map/map";
	for (unsigned int i = 0; i < MAX_TILES; i++)
	{
		std::string file = path + std::to_string(i) + ".png";
		mMap[i] = new Texture(file);
	}

	ChangeMap("PNG/Environment/Map0.txt");
}

Map::~Map()
{
	for (unsigned int i = 0; i < MAX_TILES; i++)
	{
		delete mMap[i];
		mMap[i] = NULL;
	}
}

void Map::ChangeMap(std::string filename)
{
	int c;
	std::fstream mapFile;

	std::string fullPath = SDL_GetBasePath();
	fullPath.append("assets/" + filename);

	mapFile.open(fullPath);
	if (!mapFile.is_open()) 
		printf("Fail to load map0.txt\n");
	for (int row = 0; row < MAX_ROW; ++row)
	{
		for (int col = 0; col < MAX_COL; ++col)
		{
			mapFile >> c;
			mLayer1[row][col] = c;
			mapFile.ignore();
		}
	}
	mapFile.close();
}

void Map::Update()
{

}

void Map::Render()
{
	int type = 0;
	for (int row = 0; row < MAX_ROW; ++row)
	{
		for (int col = 0; col < MAX_COL; ++col)
		{
			type = mLayer1[row][col];
			if (type >= 0 && type < MAX_TILES) {
				mMap[type]->Render(col, row);
			}
			
		}
	}

}



//#include "GameManager.h"
//#include "Map.h"
//#include "TextureManager.h"
//#include <fstream>
//
//
//Map::Map()
//{
//	road[0] = NULL;
//	for (int i = 1; i < 92; i++)
//	{
//		std::string temp = "assets/PNG/Tiles/asphaltRoad/asphaltRoad_(" + std::to_string(i) + ").png";
//		road[i] = TextureManager::LoadTexture(temp.c_str());
//	}
//
//	for (int i = 0; i < 14; i++)
//	{
//		grass[i] = NULL;
//	}
//
//	LoadMap("assets/map.txt");
//	src.x = src.y = 0;
//	src.w = src.h = 128;
//
//	dest.w = dest.h = 64;
//	dest.x = dest.y = 0;
//}
//
//Map::~Map()
//{
//	for (int i = 0; i < 92; i++)
//	{
//		if (road[i] != NULL)
//		{
//			SDL_DestroyTexture(road[i]);
//			road[i] = NULL;
//		}
//	}
//
//	for (int i = 0; i < 14; i++)
//	{
//		if (grass[i] != NULL)
//		{
//			SDL_DestroyTexture(grass[i]);
//			grass[i] = NULL;
//		}
//	}
//}
//
//void Map::LoadMap(std::string filename)
//{
//	int c;
//	std::fstream mapFile;
//	mapFile.open(filename);
//	if (!mapFile.is_open()) std::cout << "Fail to load map.txt\n";
//	for (int row = 0; row < 15; ++row)
//	{
//		for (int col = 0; col < 25; ++col)
//		{
//			mapFile >> c;
//			map[row][col] = c;
//			mapFile.ignore();
//		}
//	}
//	mapFile.close();
//	
//}
//
//void Map::DrawMap()
//{
//	int type = 0;
//	for (int row = 0; row < 15; ++row)
//	{
//		for (int col = 0; col < 25; ++col)
//		{
//			type = map[row][col];
//			dest.x = col * 64;
//			dest.y = row * 64;
//			if (type > 0 && type < 92) {
//				TextureManager::Draw(road[type], src, dest);
//			}
//			
//		}
//	}
//}

