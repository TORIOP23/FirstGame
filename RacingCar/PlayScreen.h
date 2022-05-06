#pragma once

#include <vector>
#include "Player.h"
#include "PlayTopBar.h"
#include "Level.h"


class PlayScreen : public GameEntity
{
private:
	// Manager 
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

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
	int mCurrentStage; // Level

	// Player Entitiy
	Player* mPlayer;


private:
	// Load the next level after we just finished 
	void StartNextLevel();

public:

	PlayScreen();

	~PlayScreen();

	void StartNewGame();

	void SetHealth(int health);

	void Update();

	void Render();

};
