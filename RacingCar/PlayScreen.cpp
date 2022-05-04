#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	// manager
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	// Top Bar
	mTopBar = new GameEntity(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.05f));
	mScoreboard = new Scoreboard();

	mScoreboard->Parent(mTopBar);

	mScoreboard->Pos(VEC2_ZERO);

	mScoreboard->Score(300);

	mTopBar->Parent(this);

	// Start Label
	mStartLabel = new Texture("START", "fonts/lol2.ttf", 60, { 150, 0, 0 });
	mStartLabel->Parent(this);
	mStartLabel->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));

	mLevel = NULL;
	mLevelStartDelay = 1.0f;
	mLevelStarted = true;   // false;

	mPlayer = NULL;
}

PlayScreen::~PlayScreen()
{
	// Manager
	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;

	// TopBar
	delete mTopBar;
	mTopBar = NULL;

	delete mScoreboard;
	mScoreboard = NULL;

	delete mStartLabel;
	mStartLabel = NULL;

	delete mLevel;
	mLevel = NULL;

	// Freeing Player
	delete mPlayer;
	mPlayer = NULL;
}

void PlayScreen::StartNextLevel()
{
	mCurrentStage++;
	mLevelStartTimer = 0.0f;
	mLevelStartDelay = true;

	//delete mLevel;
	mLevel = new Level(mCurrentStage);
}

void PlayScreen::StartNewGame()
{
	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));
	mPlayer->Active(false);

	mGameStarted = false;
	mAudio->PlayMusic("SFX/tribe_d.wav", 0);
	mCurrentStage = 0;
}
void PlayScreen::Update()
{
	if (mGameStarted)
	{
		if (!mLevelStarted)
		{
			mLevelStartTimer += mTimer->DeltaTime();
			if (mLevelStartTimer >= mLevelStartDelay)
			{
				StartNextLevel();
			}
		}
	}
	else
	{
		if (!Mix_PlayingMusic())
		{
			mGameStarted = true;
		}
	}

	if (mGameStarted)
	{
		if (mCurrentStage > 0)
		{

		}

		if (mLevelStarted)
		{
			mLevel->Update();
		}

		mPlayer->Update();

	}
}

void PlayScreen::Render()
{
	if (!mGameStarted)
		mStartLabel->Render();

	if (mGameStarted)
	{
		if (mLevelStarted)
		{
			mLevel->Render();
		}
		mScoreboard->Render();
		mPlayer->Render();
	}
}