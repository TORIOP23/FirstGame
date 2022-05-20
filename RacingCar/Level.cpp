#include "Level.h"

Level::Level(int stage, PlayTopBar* topBar, Player* player)
{
	mTimer = Timer::Instance();

	mTopBar = topBar;
	mTopBar->SetLevel(stage);

	mStage = stage;
	mStageStarted = false;

	mLabelTimer = 0.0f;

	// Stage label
	mStageLabel = new Texture("STAGE", "fonts/lol2.ttf", 60, { 75, 75, 200 });
	mStageLabel->Parent(this);
	mStageLabel->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.45f, Graphics::SCREEN_HEIGHT * 0.5f));

	mStageNumber = new Scoreboard({ 75, 75, 200}, 60);
	mStageNumber->Score(mStage);
	mStageNumber->Parent(this);
	mStageNumber->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.55f, Graphics::SCREEN_HEIGHT * 0.5f));

	mStageLabelOnScreen = 0.0f;
	mStageLabelOffScreen = 1.5f;

	// Ready label
	mReadyLabel = new Texture("READY", "fonts/lol1.ttf", 50, { 150, 0, 0 });
	mReadyLabel->Parent(this);
	mReadyLabel->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));

	mReadyLabelOnScreen = mStageLabelOffScreen;
	mReadyLabelOffScreen = mReadyLabelOnScreen + 2.5f;

	// Player
	mPlayer = player;
	mPlayerHit = false;
	//mPlayerRespawnDelay = 3.0f;
	//mPlayerRespawnTimer = 0.0f;
	//mPlayerRespawnLabelOnScreen = 2.0f;

	// Enermy
	mEnermy = new Enermy();
	mEnermy->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.2f, Graphics::SCREEN_HEIGHT * 0.2f));
	mEnermyHit = false;

	mGameOverLabel = new Texture("GAME OVER!!", "fonts/lol1.ttf", 60, { 150, 0, 0 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));

	mGameOver = false;
	mGameOverDelay = 5.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	mCurrentState = RUNNING;
}

Level::~Level()
{
	mTimer = NULL;
	mTopBar = NULL;

	delete mStageLabel;
	mStageLabel = NULL;

	delete mStageNumber;
	mStageNumber = NULL;

	delete mReadyLabel;
	mReadyLabel = NULL;

	mPlayer = NULL;

	delete mEnermy;
	mEnermy = NULL;

	delete mGameOverLabel;
	mGameOverLabel = NULL;
}

void Level::StartStage()
{
	mStageStarted = true;
}

void Level::HandleStartLabels()
{
	mLabelTimer += mTimer->DeltaTime();
	if (mLabelTimer >= mStageLabelOffScreen)
	{
		if (mStage > 1)
		{
			StartStage();
			mPlayer->Active(true);
			mPlayer->Visible(true);
		}
		else {
			if (mLabelTimer >= mReadyLabelOffScreen)
			{
				StartStage();
				mPlayer->Active(true);
				mPlayer->Visible(true);
			}
		}
	}
}

void Level::HandleCollisions()
{
	if (!mPlayerHit)
	{
		if (mPlayer->WasHit())
		{
			mPlayerHit = true;
			//mPlayerRespawnTimer = 0.0f;
			if (mPlayer->Health() == 0)
				mPlayer->Active(false);

		}
	}

	if (!mEnermyHit)
	{
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_Z))
		{
			mEnermy->WasHit();
			mEnermyHit = true;
			//mPlayerRespawnTimer = 0.0f;
			if (mEnermy->Health() == 0)
				mEnermy->Active(false);

		}
	}

}

void Level::HandlePlayerDeath()
{
	if (!mPlayer->IsAnimating())
	{
		if (mPlayer->Health() > 0)
		{
			/*if (mPlayerRespawnTimer == 0.0f)
			{
				mPlayer->Visible(false);
			}

			mPlayerRespawnTimer += mTimer->DeltaTime();
			if (mPlayerRespawnTimer >= mPlayerRespawnDelay)
			{
				mPlayer->Active(true);
				mPlayer->Visible(true);*/
				mPlayerHit = false;
			//}
		}
		else {
			if (mGameOverTimer == 0.0f)
				mPlayer->Visible(false);

			mGameOverTimer += mTimer->DeltaTime();
			if (mGameOverTimer >= mGameOverDelay)
			{
				mCurrentState = GAMEOVER;
			}
		}
	}
}

Level::LEVEL_STATES Level::State()
{
	return mCurrentState;
}

void Level::Update()
{
	if (!mStageStarted)
	{
		HandleStartLabels();
	} 
	else {
		// Enermy 
		mEnermy->Update(mPlayer->Pos());

		HandleCollisions();

		if (mPlayerHit)
		{
			HandlePlayerDeath();
		}
		else {
			if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_N))
			{
				mCurrentState = FINISHED;
			}
		}
	}
}

void Level::Render()
{
	if (!mStageStarted)
	{
		if (mLabelTimer > mStageLabelOnScreen && mLabelTimer < mStageLabelOffScreen)
		{
			mStageLabel->Render();
			mStageNumber->Render();
		} 
		else if (mLabelTimer > mReadyLabelOnScreen && mLabelTimer < mReadyLabelOffScreen)
		{
			mReadyLabel->Render();
		}
	}
	else
	{
		mEnermy->Render();

		if (mPlayerHit)
		{
			/*if (mPlayerRespawnTimer >= mPlayerRespawnLabelOnScreen)
				mReadyLabel->Render();*/

			if (mGameOverTimer >= mGameOverLabelOnScreen)
				mGameOverLabel->Render();
		}
	}
}