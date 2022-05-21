#pragma once

#include "Player.h"
#include "PlayTopBar.h"
#include "Level.h"
#include "Map.h"


class PlayScreen : public GameEntity
{
private:
	// Manager 
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	// Map
	Map* mMap;

	// Top bar Entities
	PlayTopBar* mTopBar;

	// Start 
	Texture* mStartLabel;

	float mLevelStartTimer;
	float mLevelStartDelay;

	bool mGameStarted;

	// Level contain enermy
	Level* mLevel;
	bool mLevelStarted;
	unsigned int mCurrentStage; // Level

	// Player Entitiy
	Player* mPlayer;

	// zoom 
	//float mZoom;


private:

	// Load the next level after we just finished 
	void StartNextLevel();

public:

	PlayScreen();

	~PlayScreen();

	void StartNewGame();

	bool GameOver();

	//void Zoom();

	void Update();

	void Render();

};
