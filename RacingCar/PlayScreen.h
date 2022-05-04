#pragma once

#include "InputManager.h"
#include "Texture.h"
#include "Timer.h"
#include "AudioManager.h"
#include "Player.h"
#include "Scoreboard.h"
#include "Level.h"


class PlayScreen : public GameEntity
{
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	// Top bar
	GameEntity* mTopBar;
	Scoreboard* mScoreboard;

	// 
	Texture* mStartLabel;

	float mLevelStartTimer;
	float mLevelStartDelay;

	bool mGameStarted;

	Level* mLevel;
	bool mLevelStarted;
	int mCurrentStage;

	Player* mPlayer;

private:

	void StartNextLevel();

public:
	PlayScreen();
	~PlayScreen();

	void StartNewGame();

	void Update();
	void Render();

};
