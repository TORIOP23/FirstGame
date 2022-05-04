#pragma once
#include "InputManager.h"
#include "Texture.h"
#include "Timer.h"
#include "Scoreboard.h"

class Level : public GameEntity
{
private:
	Timer* mTimer;

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
	Level(int stage);
	~Level();

	void Update();

	void Render();
};

