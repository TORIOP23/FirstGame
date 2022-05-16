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

	mScale = 1.0f;

}

Map::~Map()
{
	for (unsigned int i = 0; i < MAX_TILES; i++)
	{
		delete mMap[i];
		mMap[i] = NULL;
	}
}

void Map::Scale()
{
	for (unsigned int i = 0; i < MAX_TILES; i++)
	{
		mMap[i]->Scale(Vector2(mScale, mScale));
	}
}

void Map::SetScale(float scale)
{
	mScale = scale;
}

void Map::ChangeMap(std::string filename)
{
	int c;
	std::fstream mapFile;

	std::string fullPath = SDL_GetBasePath();
	fullPath.append("assets/" + filename);

	mapFile.open(fullPath);
	if (!mapFile.is_open()) 
		printf("Fail to load mapI.txt\n");
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

Vector2 Map::Dimension()
{
	return Vector2(mScale * mTileSize * MAX_COL, mScale * mTileSize * MAX_ROW);
}

void Map::Update()
{
	Scale();
}

void Map::Render()
{
	int type = 0;
	for (int row = 0; (row < MAX_ROW ); ++row)
	{
		for (int col = 0; (col < MAX_COL ); ++col)
		{
			type = mLayer1[row][col];
			if (type >= 0 && type < MAX_TILES) {
				mMap[type]->Render(col, row);
			}
		}
	}

}