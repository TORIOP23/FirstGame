#include "PlayTopBar.h"


PlayTopBar::PlayTopBar()
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mLevelLabel = new Texture("LEVEL ", "fonts/lol2.ttf", 30, { 255, 0, 0 });
	mLevelLabel->Parent(this); 
	mLevelLabel->Pos(Vector2(-60.0f, 0.0f));

	mLevelScoreboard = new Scoreboard({ 255, 0, 0 });
	mLevelScoreboard->Parent(this);
	mLevelScoreboard->Pos(Vector2(30.0f, -2.0f));

	mHighScoreLabel = new Texture("HIGH SCORE: ", "fonts/lol1.ttf", 30, { 255, 255, 255 });
	mHighScoreLabel->Parent(this);
	mHighScoreLabel->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f - 300.0f, 0.0f));

	mHighScoreboard = new Scoreboard();
	mHighScoreboard->Parent(this);
	mHighScoreboard->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f - 50.0f, 0.0f));

	mPlayerScoreLabel = new Texture("YOUR SCORE: ", "fonts/lol1.ttf", 30, { 255, 255, 255 });
	mPlayerScoreLabel->Parent(this);
	mPlayerScoreLabel->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f - 300.0f, 70.0f));

	mPlayerScoreBoard = new Scoreboard();
	mPlayerScoreBoard->Parent(this);
	mPlayerScoreBoard->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f - 50.0f, 70.0f));



	mPlayerScoreBoard->Score(0);
}

PlayTopBar::~PlayTopBar()
{
	mTimer = nullptr;
	mAudio = nullptr;

	delete mLevelLabel;
	mLevelLabel = nullptr;

	delete mLevelScoreboard;
	mLevelScoreboard = nullptr;

	delete mHighScoreLabel;
	mHighScoreLabel = nullptr;

	delete mHighScoreboard;
	mHighScoreboard = nullptr;

	delete mPlayerScoreLabel;
	mPlayerScoreLabel = nullptr;

	delete mPlayerScoreBoard;
	mPlayerScoreBoard = nullptr;
}

void PlayTopBar::SetHightScore(int score)
{
	mHighScoreboard->Score(score);
}

void PlayTopBar::SetPlayerScore(int score)
{
	mPlayerScoreBoard->Score(score);
}

void PlayTopBar::SetLevel(int level)
{
	mLevelScoreboard->Score(level);
}

void PlayTopBar::Update()
{

}

void PlayTopBar::Render()
{
	if (mLevelScoreboard->Score() > 0)
	{
		mLevelLabel->Render();
		mLevelScoreboard->Render();
	}
	mHighScoreLabel->Render();
	mHighScoreboard->Render();

	mPlayerScoreLabel->Render();
	mPlayerScoreBoard->Render();
}