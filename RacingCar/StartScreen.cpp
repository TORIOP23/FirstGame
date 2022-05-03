#include "StartScreen.h"

StartScreen::StartScreen()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	//Top Bar Entities
	mTopBar = new GameEntity(Vector2(Graphics::SCREEN_WIDTH * 0.5f, 80.0f));
	mVersion = new Texture("Version 1.0 beta", "fonts/Starcraft.ttf", 22, { 200, 0, 0 });

	mVersion->Parent(mTopBar);

	mVersion->Pos(VEC2_ZERO);

	//this is a pointer to our startScreen
	mTopBar->Parent(this);

	// Logo Entities
	mLogo = new Texture("logo.jpg");
	//mAnimatedLogo = new AnimatedTexture("");

	mLogo->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.35f));
	//mLogo->Scale(Vector2(1.3f, 1.3f));
	mLogo->Parent(this);

	// Play mode Entities
	mPlayModes = new GameEntity(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.55f));
	mPlayMode = new Texture("Play", "fonts/starcraft.ttf", 50, { 230, 230, 230 });
	mExitMode = new Texture("Exit", "fonts/starcraft.ttf", 50, { 230, 230, 230 });
	mCursor = new Texture("cursor.jpeg");

	mPlayMode->Parent(mPlayModes);
	mExitMode->Parent(mPlayModes);
	mCursor->Parent(mPlayModes);


	mPlayMode->Pos(Vector2(0.0f, -40.0f));
	mExitMode->Pos(Vector2(0.0f, 40.0f));
	mCursor->Pos(Vector2(-195.0f, -50.0f));

	mPlayModes->Parent(this);

	mCursorStartPos = mCursor->Pos(local);
	mCursorOffset = Vector2(0.0f, 80.0f);
	mSelectedMode = 0;

	//Bottom Bar Entities
	mBotBar = new GameEntity(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.7f));
	mCompany = new Texture("RIOT", "fonts/LOL1.ttf", 25, { 200, 0, 0 });
	mDates = new Texture("2022 MADE BY TORIOP", "fonts/starcraft.ttf", 30, { 129, 129, 129 });
	mRights = new Texture("ALL RIGHTS RESERVED", "fonts/starcraft.ttf", 30, { 129, 129, 129 });

	mCompany->Parent(mBotBar);
	mDates->Parent(mBotBar);
	mRights->Parent(mBotBar);

	mCompany->Pos(Vector2(0.0f, 200.0f));
	mDates->Pos(Vector2(0.0f, 70.0f));
	mRights->Pos(Vector2(0.0f, 130.0f));

	mBotBar->Parent(this);

	ResetAnimation();
}

StartScreen::~StartScreen()
{
	// Freeing Top Bar Entities
	delete mTopBar;
	mTopBar = NULL;

	delete mVersion;
	mVersion = NULL;

	// Freeing logo Entities
	delete mLogo;
	mLogo = NULL;

	// Freeing Play Mode Entities
	delete mPlayModes;
	mPlayModes = NULL;

	delete mPlayMode;
	mPlayMode = NULL;

	delete mExitMode;
	mExitMode = NULL;

	delete mCursor;
	mCursor = NULL;

	// Freeing Bot Bar Entities
	delete mBotBar;
	mBotBar = NULL;

	delete mCompany;
	mCompany = NULL;

	delete mDates;
	mDates = NULL;

	delete mRights;
	mRights = NULL;
}

void StartScreen::ResetAnimation()
{
	// Screen Animation Variables
	// scrren has pos VEC2_ZERO, everything setup with (0, 0) position in the world
	mAnimationStartPos = Vector2(0.0f, Graphics::SCREEN_HEIGHT);
	mAnimationEndPos = VEC2_ZERO;
	mAnimationTimer = 0.0f;
	mAnimationTotalTime = 5.0f;
	mAnimationDone = false;

	Pos(mAnimationStartPos);
}

int StartScreen::SelectedMode()
{
	return mSelectedMode;
}

void StartScreen::ChangeSelectedMode(int change)
{
	mSelectedMode += change;
	
	if (mSelectedMode < 0)
		mSelectedMode = 1;
	else if (mSelectedMode > 1)
		mSelectedMode = 0;

	mCursor->Pos(mCursorStartPos + mCursorOffset * mSelectedMode);
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
		if (mInput->KeyPressed(SDL_SCANCODE_DOWN))
			ChangeSelectedMode(1);
		else if (mInput->KeyPressed(SDL_SCANCODE_UP))
			ChangeSelectedMode(-1);
	}
}

void StartScreen::Render()
{
	mVersion->Render();

	mLogo->Render();

	mPlayMode->Render();
	mExitMode->Render();
	mCursor->Render();

	mCompany->Render();
	mDates->Render();
	mRights->Render();
}