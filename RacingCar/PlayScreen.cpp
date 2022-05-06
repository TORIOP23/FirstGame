#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	// manager
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	// Top Bar
	mTopBar = new PlayTopBar();

	mTopBar->Parent(this);
	mTopBar->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.05f));

	mTopBar->SetHightScore(3000);
	mTopBar->SetPlayerScore(0);
	//mTopBar->SetLevel(3);

	// Start Label
	mStartLabel = new Texture("START", "fonts/lol2.ttf", 60, { 150, 0, 0 });
	mStartLabel->Parent(this);
	mStartLabel->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));


	// Player 
	mPlayer = NULL;
	mBoxCollision = new Texture("PNG/boxCollision.png");

	mLevel = NULL;
	mLevelStartTimer = 0.0f;
	mLevelStartDelay = 1.0f;
	mLevelStarted =  false;
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

	// start label
	delete mStartLabel;
	mStartLabel = NULL;

	// Freeing Player
	delete mPlayer;
	mPlayer = NULL;

	delete mBoxCollision;
	mBoxCollision = NULL;

	delete mLevel;
	mLevel = NULL;
}

void PlayScreen::StartNextLevel()
{
	mCurrentStage++;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;

	delete mLevel;
	mLevel = new Level(mCurrentStage, mTopBar, mPlayer);

	//mAudio->PlaySFX("SFX/levelUp.wav");
}

void PlayScreen::StartNewGame()
{
	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));
	mPlayer->Active(true);
	mPlayer->Visible(false);

	// Top Bar
	mTopBar->SetHightScore(3000);
	mTopBar->SetPlayerScore(mPlayer->Score());
	mTopBar->SetLevel(0);
	
	mBoxCollision->Parent(mPlayer);
	mBoxCollision->Pos(Vector2(VEC2_ZERO));
	mBoxCollision->Active(true);


	mGameStarted = false;
	mLevelStarted = false;
	mLevelStartTimer = 0.0f;
	mCurrentStage = 0;

	mAudio->PlayMusic("Music/welcome.wav", 0);
	

}

bool PlayScreen::GameOver()
{
	if (!mLevelStarted)
		return false;

	return (mLevel->State() == Level::GAMEOVER);
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
			mTopBar->Update();
		}

		if (mLevelStarted)
		{
			mLevel->Update();

			if (mLevel->State() == Level::FINISHED)
			{
				mLevelStarted = false;
			}
		}

		mPlayer->Update();

		/*if (mInput->KeyPressed(SDL_SCANCODE_U))
		{
			mLevelStarted = false;
		}*/
	}
}

void PlayScreen::Render()
{
	mTopBar->Render();

	if (!mGameStarted)
		mStartLabel->Render();

	if (mGameStarted)
	{
		if (mLevelStarted)
		{
			mLevel->Render();
		}

		if (mBoxCollision->Active())
		{
			mBoxCollision->Render();
		}
		mPlayer->Render();

	}
}