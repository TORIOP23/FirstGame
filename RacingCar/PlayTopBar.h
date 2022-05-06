#pragma once
#include "Timer.h"
#include "Scoreboard.h"
#include "AudioManager.h"

class PlayTopBar : public GameEntity
{
private:
	Timer* mTimer;
	AudioManager* mAudio;


	Texture* mLevelLabel;
	Scoreboard* mLevelScoreboard;

	Texture* mHighScoreLabel;
	Scoreboard* mHighScoreboard;

	Texture* mPlayerScoreLabel;
	Scoreboard* mPlayerScoreBoard;

public:
	PlayTopBar();

	~PlayTopBar();

	void SetHightScore(int score);

	void SetPlayerScore(int score);

	void SetLevel(int level);

	void Update();

	void Render();
};

