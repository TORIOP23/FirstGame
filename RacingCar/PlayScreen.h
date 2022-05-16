#pragma once

#include <vector>
#include "Player.h"
#include "PlayTopBar.h"
#include "Level.h"
#include "Map.h"
#include "Enermy.h"


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

	// Level
	Level* mLevel;
	bool mLevelStarted;
	unsigned int mCurrentStage; // Level

	// Player Entitiy
	Player* mPlayer;

	// zoom 
	//float mZoom;


private:

	void MoveScreen();

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
