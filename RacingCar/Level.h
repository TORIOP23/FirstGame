#pragma once
#include "InputManager.h"
#include "PlayTopBar.h"
#include "Player.h"
#include "Enermy.h"

class Level : public GameEntity
{

public:

	enum LEVEL_STATES { RUNNING, FINISHED, GAMEOVER };

private:
	Timer* mTimer;

	PlayTopBar* mTopBar;

	int mStage;
	bool mStageStarted;

	float mLabelTimer;

	Texture* mStageLabel;
	Scoreboard* mStageNumber;
	float mStageLabelOnScreen;
	float mStageLabelOffScreen;

	Texture* mReadyLabel;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

	Player* mPlayer;
	bool mPlayerHit;
	//float mPlayerRespawnDelay;
	//float mPlayerRespawnTimer;
	//float mPlayerRespawnLabelOnScreen;

	Texture* mGameOverLabel;
	bool mGameOver;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverLabelOnScreen;

	LEVEL_STATES mCurrentState;

	Enermy* mEnermy;

private:

	void StartStage();

	void HandleStartLabels();

	void HandleCollisions();

	void HandlePlayerDeath();

public:
	Level(int stage, PlayTopBar* topBar, Player* player);

	~Level();

	LEVEL_STATES State();

	void Update();

	void Render();
};

