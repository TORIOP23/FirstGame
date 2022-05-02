#include "StartScreen.h"

StartScreen::StartScreen()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	//Top Bar Entities
	mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 80.0f));
	mHiScore = new Texture("xem quang cao de nhan them vat pham", "Starcraft.ttf", 22, { 200, 0, 0 });

	mHiScore->Parent(mTopBar);

	mHiScore->Pos(VEC2_ZERO);

	//this is a pointer to our startScreen
	mTopBar->Parent(this);

	// Logo Entities
	mLogo = new Texture("logo.jpg");
	//mAnimatedLogo = new AnimatedTexture("");

	mLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.35f));
	mLogo->Scale(Vector2(1.3f, 1.3f));
	mLogo->Parent(this);

	// Play mode Entities
	mPlayModes = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.55f));
	mOnePlayerMode = new Texture("Play", "starcraft.ttf", 40, { 230, 230, 230 });
	mTwoPlayerMode = new Texture("Don't play", "starcraft.ttf", 40, { 230, 230, 230 });
	mCursor = new Texture("cursor.jpeg");

	mOnePlayerMode->Parent(mPlayModes);
	mTwoPlayerMode->Parent(mPlayModes);
	mCursor->Parent(mPlayModes);


	mOnePlayerMode->Pos(Vector2(-18.0f, -35.0f));
	mTwoPlayerMode->Pos(Vector2(0.0f, 35.0f));
	mCursor->Pos(Vector2(-195.0f, -50.0f));

	mPlayModes->Parent(this);

	mCursorStartPos = mCursor->Pos(local);
	mCursorOffset = Vector2(0.0f, 70.0f);
	mSelectedMode = 0;

	//Bottom Bar Entities
	mBotBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.7f));
	mNamco = new Texture("RIOT", "LOL1.ttf", 50, { 200, 0, 0 });
	mDates = new Texture("2022 MADE BY TORIOP", "starcraft.ttf", 32, { 230, 230,230 });
	mRights = new Texture("ALL RIGHTS RESERVED", "starcraft.ttf", 32, { 230,230,230 });

	mNamco->Parent(mBotBar);
	mDates->Parent(mBotBar);
	mRights->Parent(mBotBar);

	mNamco->Pos(VEC2_ZERO);
	mDates->Pos(Vector2(0.0f, 90.0f));
	mRights->Pos(Vector2(0.0f, 170.0f));

	mBotBar->Parent(this);

	ResetAnimation();
}

StartScreen::~StartScreen()
{
	// Freeing Top Bar Entities
	delete mTopBar;
	mTopBar = NULL;

	delete mHiScore;
	mHiScore = NULL;

	// Freeing logo Entities
	delete mLogo;
	mLogo = NULL;

	// Freeing Play Mode Entities
	delete mPlayModes;
	mPlayModes = NULL;

	delete mOnePlayerMode;
	mOnePlayerMode = NULL;

	delete mTwoPlayerMode;
	mTwoPlayerMode = NULL;

	delete mCursor;
	mCursor = NULL;

	// Freeing Bot Bar Entities
	delete mBotBar;
	mBotBar = NULL;

	delete mNamco;
	mNamco = NULL;

	delete mDates;
	mDates = NULL;

	delete mRights;
	mRights = NULL;
}

void StartScreen::ResetAnimation()
{
	// Screen Animation Variables
	// scrren has pos VEC2_ZERO, everything setup with (0, 0) position in the world
	mAnimationStartPos = Vector2(0.0f, Graphics::Instance()->SCREEN_HEIGHT);
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
	mHiScore->Render();

	mLogo->Render();

	mOnePlayerMode->Render();
	mTwoPlayerMode->Render();
	mCursor->Render();

	mNamco->Render();
	mDates->Render();
	mRights->Render();
}