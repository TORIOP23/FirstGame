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

	float mScale;

	const float mTileSize = 64;

	// position upper left conner 
	//Vector2 mPosCamera;

private:

	void Scale();

public:

	static Map* Instance();

	static void Release();

	void SetScale(float scale);

	void ChangeMap(std::string filename);

	Vector2 Dimension();

	void Update();

	void Render();


private:
	Map();

	~Map();
};


