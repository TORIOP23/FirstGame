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
	
	std::string filename = "PNG/Health_Bars/health_";
	for (int i = 0; i < 21; i++)
	{
		std::string file = filename + std::to_string(i) + ".png";
		mHealthBar.push_back(new Texture(file));
	}

	// full = 20
	mHealth = 20;

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

	for (int i = 0; i < 21; i++)
	{
		delete mHealthBar[i];
		mHealthBar[i] = NULL;
	}
	mHealthBar.clear();

	delete mLevel;
	mLevel = NULL;
}

void PlayScreen::StartNextLevel()
{
	mCurrentStage++;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;

	delete mLevel;
	mLevel = new Level(mCurrentStage, mTopBar);
}

void PlayScreen::StartNewGame()
{
	// Top Bar
	mTopBar->SetHightScore(3000);
	mTopBar->SetPlayerScore(0);
	mTopBar->SetLevel(0);

	mHealth = 20;

	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));
	mPlayer->Active(false);

	mGameStarted = false;
	mAudio->PlayMusic("Music/welcome.wav", 0);
	mCurrentStage = 0;


	for (int i = 0; i < 21; i++)
	{
		mHealthBar[i]->Parent(mPlayer);
		mHealthBar[i]->Pos(Vector2(0.0f, -50.0f));
		mHealthBar[i]->Scale(Vector2(0.25f, 0.3f));
	}
}


void PlayScreen::SetHealth(int health)
{
	mHealth = health;
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
			mTopBar->Update();
		}

		mPlayer->Update();

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


		mHealthBar[mHealth]->Render();
		mPlayer->Render();
	}
}