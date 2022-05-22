#pragma once
#include "InputManager.h"
#include "PlayTopBar.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

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

	// Stage Label
	Texture* mStageLabel;
	Scoreboard* mStageNumber;
	float mStageLabelOnScreen;
	float mStageLabelOffScreen;

	// Ready Label
	Texture* mReadyLabel;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

	// Player
	Player* mPlayer;
	bool mPlayerDeath;

	// Enemy
	const int ENEMIES;
	int mCntEnemy;
	std::vector<Enemy*> mEnemy;
	Texture* mEnemyLabel;
	Scoreboard* mEnemyNumber;

	// Respawn
	//float mPlayerRespawnDelay;
	//float mPlayerRespawnTimer;
	//float mPlayerRespawnLabelOnScreen;

	Texture* mGameOverLabel;
	bool mGameOver;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverLabelOnScreen;

	LEVEL_STATES mCurrentState;

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

