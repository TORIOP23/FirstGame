#include "Level.h"

Level::Level(int stage, PlayTopBar* topBar, Player* player) : ENEMIES(stage)
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
	mPlayerDeath = false;
	//mPlayerRespawnDelay = 3.0f;
	//mPlayerRespawnTimer = 0.0f;
	//mPlayerRespawnLabelOnScreen = 2.0f;

	// Enemy
	for (int i = 0; i < ENEMIES; i++)
	{
		int posX, posY;
		Vector2 posPlayer = mPlayer->Pos();
		do
		{
			posX = rand() % 31;
			posY = rand() % 16;
		} while (posX * 100 + 70.0f > posPlayer.x - 100 && posX * 100 + 70.0f < posPlayer.x + 100
				&& posY * 100 + 70.0f > posPlayer.y - 100 && posY * 100 + 70.0f < posPlayer.y + 100);
		
		mEnemy.push_back(new Enemy());
		mEnemy[i]->Pos(Vector2(posX * 100 + 70.0f, posY * 100 + 70.0f));

		printf("(%f, %f)\n", mEnemy[i]->Pos().x, mEnemy[i]->Pos().y);
	}
	
	mCntEnemy = ENEMIES;

	mEnemyLabel = new Texture("ENEMIES : ", "fonts/lol1.ttf", 40, { 150, 200, 150 });
	mEnemyLabel->Pos(Vector2(Graphics::SCREEN_WIDTH - 300.0f, 200.0f));

	mEnemyNumber = new Scoreboard({ 150, 200, 150 });
	mEnemyNumber->Parent(mEnemyLabel);
	mEnemyNumber->Pos(Vector2(200.0f, 0.0f));
	mEnemyNumber->Score(mCntEnemy);

	// game over
	mGameOverLabel = new Texture("GAME OVER!!", "fonts/lol1.ttf", 60, { 150, 0, 0 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, Graphics::SCREEN_HEIGHT * 0.5f));

	mGameOver = false;
	mGameOverDelay = 5.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	mCurrentState = RUNNING;

	Enemy::CurrentPlayer(mPlayer);
}

Level::~Level()
{
	mTimer = nullptr;
	mTopBar = nullptr;

	delete mStageLabel;
	mStageLabel = nullptr;

	delete mStageNumber;
	mStageNumber = nullptr;

	delete mReadyLabel;
	mReadyLabel = nullptr;

	mPlayer = nullptr;

	// Enemy
	for (int i = 0; i < mEnemy.size(); i++)
	{
		delete mEnemy[i];
		mEnemy[i] = nullptr;
	}
	mEnemy.clear();

	delete mEnemyLabel;
	mEnemyLabel = nullptr;

	delete mEnemyNumber;
	mEnemyNumber = nullptr;

	delete mGameOverLabel;
	mGameOverLabel = nullptr;
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
	if (!mPlayerDeath)
	{
		if (mPlayer->Health() == 0)
		{
			mPlayer->Active(false);
			mPlayerDeath = true;
		}
	}

	mCntEnemy = ENEMIES;
	for (int i = 0; i < mEnemy.size(); i++)
	{
		if (mEnemy[i]->Health() == 0)
		{
			mEnemy[i]->Active(false);
			mCntEnemy--;
		}
	}
}

void Level::HandlePlayerDeath()
{
	if (!mPlayer->IsAnimating())
	{
		if (mGameOverTimer == 0.0f)
			mPlayer->Visible(false);

		mGameOverTimer += mTimer->DeltaTime();
		if (mGameOverTimer >= mGameOverDelay)
		{
			mCurrentState = GAMEOVER;
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
		for (int i = 0; i < mEnemy.size(); i++)
			mEnemy[i]->Update();

		HandleCollisions();

		mEnemyNumber->Score(mCntEnemy);

		if (mCntEnemy == 0)
		{
			mCurrentState = FINISHED;
		}

		if (mPlayerDeath)
		{
			HandlePlayerDeath();
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
		for (int i = 0; i < mEnemy.size(); i++)
			mEnemy[i]->Render();

		mEnemyLabel->Render();
		mEnemyNumber->Render();

		if (mPlayerDeath)
		{
			/*if (mPlayerRespawnTimer >= mPlayerRespawnLabelOnScreen)
				mReadyLabel->Render();*/

			if (mGameOverTimer >= mGameOverLabelOnScreen)
				mGameOverLabel->Render();
		}
	}
}