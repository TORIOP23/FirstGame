#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mStartLabel = new Texture("START", "fonts/lol2.ttf", 40, { 150, 0, 0 });
	mStartLabel->Parent(this);
	mStartLabel->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));

	mLevelStartDelay = 1.0f;
	mLevelStarted = false;

	mPlayer = NULL;
}

PlayScreen::~PlayScreen()
{
	mTimer = NULL;
	mInput = NULL;
	mAudio = NULL;

	delete mStartLabel;
	mStartLabel = NULL;

	// Freeing Player
	delete mPlayer;
	mPlayer = NULL;
}

void PlayScreen::StartNextLevel()
{
	mCurrentStage++;
	mLevelStartTimer = 0.0f;
	mLevelStartDelay = true;
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
			// mLevel->Update();
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
		mPlayer->Render();
	}
}