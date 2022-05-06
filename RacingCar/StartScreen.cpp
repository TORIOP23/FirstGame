// StartScreen.cpp
// Menu Screen

#include "StartScreen.h"

StartScreen::StartScreen()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();
	
	mAudio->PlayMusic("Music/pickBan.wav");

	// Background
	mBkg = new Texture("bkg.jpg");
	mBkg->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));

	//Top Bar Entities
	mTopBar = new GameEntity(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.05f));
	mVersion = new Texture("Version 1.0 beta", "fonts/Starcraft.ttf", 22, { 200, 0, 0 });
	mDates = new Texture("2022 MADE BY TORIOP", "fonts/starcraft.ttf", 22, { 200, 0, 0 });

	mVersion->Parent(mTopBar);
	mDates->Parent(mTopBar);

	mVersion->Pos(VEC2_ZERO);
	mDates->Pos(Vector2(0.0f, - 30.0f));

	//this is a pointer to our startScreen
	//mTopBar->Parent(this);


	// Play mode Entities
	mPlayModes = new GameEntity(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.75f));
	mPlayButton = new Texture("UI/blue_button00.png");
	mPlayMode = new Texture("Play", "fonts/starcraft.ttf", 50, { 230, 230, 230 });
	mExitButton = new Texture("UI/blue_button00.png");
	mExitMode = new Texture("Exit", "fonts/starcraft.ttf", 50, { 230, 230, 230 });

	mPlayButton->Scale(Vector2(1.30f, 1.3f));
	mExitButton->Scale(Vector2(1.30f, 1.3f));

	mPlayButton->Parent(mPlayModes);
	mPlayMode->Parent(mPlayModes);
	mExitButton->Parent(mPlayModes);
	mExitMode->Parent(mPlayModes);

	mPlayButton->Pos(Vector2(0.0f, -40.0f));
	mPlayMode->Pos(Vector2(0.0f, -40.0f));
	mExitButton->Pos(Vector2(0.0f, 40.0f));
	mExitMode->Pos(Vector2(0.0f, 40.0f));

	mPlayModes->Parent(this);


	//Bottom Bar Entities
	mBotBar = new GameEntity(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.8f));
	mCompany = new Texture("RIOT", "fonts/LOL1.ttf", 30, { 200, 0, 0 });
	mRights = new Texture("ALL RIGHTS RESERVED", "fonts/starcraft.ttf", 20, { 129, 129, 129 });

	mCompany->Parent(mBotBar);
	mRights->Parent(mBotBar);

	mCompany->Pos(Vector2(0.0f, 100.0f));
	mRights->Pos(Vector2(0.0f, 130.0f));

	//mBotBar->Parent(this);

	ResetAnimation();
}

StartScreen::~StartScreen()
{
	mAudio = NULL;

	// Freeing background
	delete mBkg;
	mBkg = NULL;

	// Freeing Top Bar Entities
	delete mTopBar;
	mTopBar = NULL;

	delete mVersion;
	mVersion = NULL;

	delete mDates;
	mDates = NULL;

	// Freeing Play Mode Entities
	delete mPlayModes;
	mPlayModes = NULL;

	delete mPlayButton;
	mPlayButton = NULL;

	delete mPlayMode;
	mPlayMode = NULL;

	delete mExitButton;
	mExitButton = NULL;

	delete mExitMode;
	mExitMode = NULL;

	// Freeing Bot Bar Entities
	delete mBotBar;
	mBotBar = NULL;

	delete mCompany;
	mCompany = NULL;

	delete mRights;
	mRights = NULL;
}

void StartScreen::ResetAnimation()
{
	// Screen Animation Variables
	// scrren has pos VEC2_ZERO, everything setup with (0, 0) position in the world
	mAnimationStartPos = Vector2(0.0f, Graphics::SCREEN_HEIGHT * 0.5f);
	mAnimationEndPos = VEC2_ZERO;
	mAnimationTimer = 0.0f;
	mAnimationTotalTime = 4.0f;
	mAnimationDone = false;

	Pos(mAnimationStartPos);
}

void StartScreen::Mode()
{
	mSeLectedMode = NONE;

	float xPos = mInput->MousePos().x - mPlayButton->Pos().x;
	float yPos = mInput->MousePos().y;

	if ((xPos > (-mPlayButton->Width() * 0.5f)) && (xPos < (mPlayButton->Width() * 0.5f)))
	{
		if (yPos > (mPlayButton->Pos().y - mPlayButton->Height() * 0.5f) && yPos < (mPlayButton->Pos().y + mPlayButton->Height() * 0.5f))
		{
			mSeLectedMode = PLAY;
		}
		else if (yPos > (mExitButton->Pos().y - mExitButton->Height() * 0.5f) && yPos < (mExitButton->Pos().y + mExitButton->Height() * 0.5f))
		{
			mSeLectedMode = EXIT;
		}
	}
}

StartScreen::MODE StartScreen::SelectedMode()
{
	return mSeLectedMode;
}

void StartScreen::Update()
{
	if (!mAnimationDone)
	{
		mAnimationTimer += mTimer->DeltaTime();
		Pos(Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));

		if (mAnimationTimer >= mAnimationTotalTime)
			mAnimationDone = true;

		if (mInput->KeyPressed(SDL_SCANCODE_DOWN) || mInput->KeyPressed(SDL_SCANCODE_UP))
			mAnimationTimer = mAnimationTotalTime;
	}
	else
	{
		Mode();
	}
}

void StartScreen::Render()
{
	mBkg->Render();
	mVersion->Render();
	mDates->Render();

	mPlayButton->Render();
	mPlayMode->Render();
	mExitButton->Render();
	mExitMode->Render();

	mCompany->Render();
	mRights->Render();
}