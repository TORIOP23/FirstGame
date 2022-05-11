#pragma once

#include "Texture.h"

class Map
{
private:

	static Map* sInstance;

	static const unsigned int MAX_TILES = 299;

	Texture* mMap[MAX_TILES];

	static const int MAX_ROW = 15;
	static const int MAX_COL = 25;

	int mLayer1[MAX_ROW][MAX_COL];

public:

	static Map* Instance();

	static void Release();

	void ChangeMap(std::string filename);

	void Update();

	void Render();


private:
	Map();

	~Map();
};



//#include "GameManager.h"
//#include <string>
//
//class Map
//{
//public:
//
//	Map();
//	//Map(std::string tID, int ms, int ts);
//	~Map();
//
//	int map[15][25];
//
//	void LoadMap(std::string filename);
//	void DrawMap();
//	
//private:
//	/*std::string texID;
//	int mapScale;
//	int tileSize;
//	int scaledSize;*/
//
//	SDL_Rect src, dest;
//	SDL_Texture* road[92];
//	SDL_Texture* grass[14];
//
//	//int map[15][25];
//};


