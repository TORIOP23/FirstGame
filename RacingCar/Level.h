#pragma once
#include "InputManager.h"
#include "Texture.h"
#include "Timer.h"

class Level : public GameEntity
{
private:
	Timer* mTimer;

	int mStage;
	bool mStageStarted;

	float mLabelTimer;

	Texture* mStageLabel;
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

