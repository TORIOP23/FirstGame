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

	const int mTileSize = 64;

	// position upper left conner 
	Vector2 mPrePosCamera;
	Vector2 mPosCamera;

private:
	// Scale every tilemap
	void Scale();

public:

	static Map* Instance();

	static void Release();

	// Setter
	void SetScale(float scale);
	void ChangeMap(std::string filename);
	void PosCamera(Vector2 pos);

	Vector2 Dimension() const;

	Vector2 PosCamera() const;

	// return mPos - mPrePos
	Vector2 MoveCamera() const;

	void MoveCamera(Vector2 move);

	void Update();

	void Render();


private:
	Map();

	~Map();
};


