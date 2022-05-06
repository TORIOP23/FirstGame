#pragma once
#include "InputManager.h"
#include "PlayTopBar.h"

class Level : public GameEntity
{
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
	float mReadtLabelOffScreen;


private:

	void StartStage();

public:
	Level(int stage, PlayTopBar* topBar);

	~Level();

	void Update();

	void Render();
};

