#include "Enemy.h"

Player* Enemy::sPlayer = nullptr;

void Enemy::CurrentPlayer(Player* player)
{
	sPlayer = player;
}

Enemy::Enemy() : BaseTanks(false)
{

	mRotationSpeed = 60.0f;

	mMoveSpeed = 150.0f;

	// Delay Bullet
	mBulletsTimer = 0.0f;
	mBulletsDelay = 0.6f;

	mCurrentState = CHASE;

	mMoveAuto = 0.0f;

	mPrePos = VEC2_ZERO;
}

Enemy::~Enemy()
{

}


void Enemy::HandleStates()
{
	Vector2 pos = Pos();
	if (pos.x < 0 || pos.y < 0 || pos.x > Graphics::SCREEN_WIDTH || pos.y > Graphics::SCREEN_HEIGHT)
	{
		mCurrentState = AUTO;
	}
	else
		mCurrentState = CHASE;

	switch (mCurrentState)
	{
	case Enemy::AUTO:
		HandleAutoState();
		break;
	case Enemy::CHASE:
		HandleChaseState();
		break;
	default:
		break;
	}
}

void Enemy::HandleAutoState()
{
	if (mId % 2 == 0)
	{
		if (mMoveAuto > mDistanceMoveAuto)
		{
			mSign = -1.0f;
		}
		else if (mMoveAuto < -mDistanceMoveAuto)
			mSign = 1.0f;

		mMoveAuto += mSign * (VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime()).Magnitude();
		Translate(mSign * VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::world);
	}
	else {
		if (mMoveAuto > mDistanceMoveAuto)
		{
			mSign = -1.0f;
		}
		else if (mMoveAuto < -mDistanceMoveAuto)
			mSign = 1.0f;

		mMoveAuto += (mSign * VEC2_UP * mMoveSpeed * mTimer->DeltaTime()).Magnitude();
		Translate(mSign * VEC2_UP * mMoveSpeed * mTimer->DeltaTime(), GameEntity::world);
	}
}

void Enemy::HandleChaseState()
{
	// Update barrel
	Vector2 direct = sPlayer->Pos() - Pos();
	float barrelRotation = AngleBetweenVector(Vector2(0.0f, 1.0f), direct);
	if (sPlayer->Pos().x - Pos().x >= 0)
	{
		mBarrel->Rotation(-barrelRotation);
	}
	else {
		mBarrel->Rotation(barrelRotation);
	}

	// Move 
	float distance = (mHeadBarrel->Pos() - sPlayer->Pos()).Magnitude();

	int tankRotation = static_cast<int>(mTank->Rotation());
	if (distance > mBullets[0]->FIRING_RANGE + 10.0f)
	{
		// Move horizontal
		if (sPlayer->Pos().x - Pos().x > 5.0f)
		{
			Translate(VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::world);
			if (tankRotation != 90 && tankRotation != 270)
				mTank->Rotate(mRotationSpeed * mTimer->DeltaTime());

		}
		else if (sPlayer->Pos().x - Pos().x < -5.0f)
		{
			Translate(-VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::world);
			if (tankRotation != 90 && tankRotation != 270)
				mTank->Rotate(mRotationSpeed * mTimer->DeltaTime());
		}
		else {
			// Move vertical
			if (sPlayer->Pos().y - Pos().y >= 0)
			{
				Translate(VEC2_DOWN * mMoveSpeed * mTimer->DeltaTime(), GameEntity::world);
				if (tankRotation != 0 && tankRotation != 180)
					mTank->Rotate(-mRotationSpeed * mTimer->DeltaTime());
			}
			else {
				Translate(VEC2_UP * mMoveSpeed * mTimer->DeltaTime(), GameEntity::world);
				if (tankRotation != 0 && tankRotation != 180)
					mTank->Rotate(-mRotationSpeed * mTimer->DeltaTime());
			}
		}
	}
	else {
		HandleFiring();
	}
}

void Enemy::HandleFiring()
{
	mBulletsTimer += mTimer->DeltaTime();
	if (mBulletsTimer >= mBulletsDelay)
	{
		mBulletsTimer = 0.0f;
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (!mBullets[i]->Active())
			{
				mBullets[i]->Fire(mHeadBarrel->Pos(), sPlayer->Pos());
				mAudio->PlaySFX("SFX/shoot_01.ogg");
				break;
			}
		}
	}
}

bool Enemy::IgnoreCollision()
{
	return !mVisible || mAnimating;
}

Enemy::STATES Enemy::CurrentState()
{
	return mCurrentState;
}

void Enemy::Hit(PhysicEntity* other)
{
	if (mHealth > 0)
		mHealth--;
	if (mHealth == 0)
	{
		mDeathAnimation->ResetAnimation();
		mAnimating = true;
		mAudio->PlaySFX("SFX/explosion.wav");

		sPlayer->AddScore(100);
	}
	else {
		mAudio->PlaySFX("SFX/tribe_d.wav");
	}

	mWasHit = true;

}

void Enemy::PlayerHitEnemy(PhysicEntity* other)
{
	Pos(mPrePos);
}

void Enemy::Update()
{
	Translate(-mMap->MoveCamera().Approximate());

	mPrePos = Pos(); // ?? 

	if (mAnimating)
	{
		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();
		if (!mAnimating)
		{
			Visible(false);
		}
	}
	else
	{
		if (mWasHit)
			mWasHit = false;

		if (Active())
		{
			HandleStates();
		}
	}

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i]->Update();
	}	
}

void Enemy::Render()
{
	PhysicEntity::Render();

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i]->Render();
	}

	if (mVisible)
	{
		if (mAnimating)
		{
			mDeathAnimation->Render();
		}
		else
		{
			mHealthBar[mHealth]->Render();
			mTank->Render();
			mBarrel->Render();
		}
	}
}