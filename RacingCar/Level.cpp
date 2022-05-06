#include "Level.h"

Level::Level(int stage, PlayTopBar* topBar)
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
	mStageNumber->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.6f, Graphics::SCREEN_HEIGHT * 0.5f));

	mStageLabelOnScreen = 0.0f;
	mStageLabelOffScreen = 1.5f;

	// Ready label
	mReadyLabel = new Texture("READY", "fonts/lol1.ttf", 50, { 150, 0, 0 });
	mReadyLabel->Parent(this);
	mReadyLabel->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));

	mReadyLabelOnScreen = mStageLabelOffScreen;
	mReadtLabelOffScreen = mReadyLabelOnScreen + 3.0f;

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
}

void Level::StartStage()
{
	mStageStarted = true;
}
void Level::Update()
{
	if (!mStageStarted)
	{
		mLabelTimer += mTimer->DeltaTime();
		if (mLabelTimer >= mStageLabelOffScreen)
		{
			if (mStage > 1)
			{
				StartStage();
			}
			else {
				if (mLabelTimer >= mReadtLabelOffScreen)
					StartStage();
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
		else if (mLabelTimer > mReadyLabelOnScreen && mLabelTimer < mReadtLabelOffScreen)
		{
			mReadyLabel->Render();
		}
	}
}