#include "Level.h"

Level::Level(int stage)
{
	mTimer = Timer::Instance();

	mStage = stage;
	mStageStarted = false;

	mLabelTimer = 0.0f;
}

Level::~Level()
{
	mTimer = NULL;
}

void Level::Update()
{

}

void Level::Render()
{

}