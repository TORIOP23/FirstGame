#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	// manager
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	// Map
	mMap = Map::Instance();

	// Top Bar
	mTopBar = new PlayTopBar();

	mTopBar->Parent(this);
	mTopBar->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.05f));

	mTopBar->SetHightScore(3000);
	mTopBar->SetPlayerScore(0);

	// Start Label
	mStartLabel = new Texture("START", "fonts/lol2.ttf", 60, { 150, 0, 0 });
	mStartLabel->Parent(this);
	mStartLabel->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));

	mLevelStartTimer = 0.0f;
	mLevelStartDelay = 5.0f;
	mGameStarted = false;

	mLevel = nullptr;
	mLevelStarted =  false;
	mCurrentStage = 0;

	// Player 
	mPlayer = nullptr;

	//mZoom = 1.0f;
}

PlayScreen::~PlayScreen()
{
	// Manager
	mTimer = nullptr;
	mInput = nullptr;
	mAudio = nullptr;

	Map::Release();
	mMap = nullptr;

	// TopBar
	delete mTopBar;
	mTopBar = nullptr;

	// start label
	delete mStartLabel;
	mStartLabel = nullptr;

	// Level
	delete mLevel;
	mLevel = nullptr;

	// Freeing Player
	delete mPlayer;
	mPlayer = nullptr;

}

void PlayScreen::StartNextLevel()
{
	mCurrentStage++;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;

	delete mLevel;
	mLevel = new Level(mCurrentStage, mTopBar, mPlayer);

	mMap->PosCamera(VEC2_ZERO);

	mPlayer->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));

	//mAudio->PlaySFX("SFX/levelUp.wav", 0, 0);
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

//void PlayScreen::Zoom()
//{
//
//	mPlayer->Scale(Vector2(mZoom, mZoom));
//	mMap->SetScale(mZoom);
//
//	if (mInput->MouseButtonDown(InputManager::FORWARD) && mZoom < 3.0f)
//	{
//		printf("Zoom in\n");
//		mZoom += 0.2f;
//	}
//	else if (mInput->MouseButtonDown(InputManager::BACK) && mZoom > 0.5f)
//	{
//		printf("Zoom out\n");
//		mZoom -= 0.2f;
//	}
//}

void PlayScreen::Update()
{

	if (mGameStarted)
	{
		if (mCurrentStage > 0)
		{
			mTopBar->Update();
		}

		if (!mLevelStarted)
		{
			mLevelStartTimer += mTimer->DeltaTime();
			if (mLevelStartTimer >= mLevelStartDelay)
			{
				StartNextLevel();
			}
		}
		else {

			//Zoom();

			// Update first to move camera
			mPlayer->Update();

			// Move Enermy 
			mLevel->Update();

			// Update mPrePosCamera
			mMap->Update();

			mTopBar->SetPlayerScore(mPlayer->Score());

			if (mLevel->State() == Level::FINISHED)
			{
				mLevelStarted = false;
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

}

void PlayScreen::Render()
{
	mMap->Render();
	mTopBar->Render();

	if (!mGameStarted)
		mStartLabel->Render();

	if (mGameStarted)
	{
		if (mLevelStarted)
		{
			mLevel->Render();
			mPlayer->Render();
		}

	}
}