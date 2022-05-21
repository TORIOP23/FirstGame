#include "Enermy.h"

Player* Enermy::sPlayer = nullptr;

void Enermy::CurrentPlayer(Player* player)
{
	sPlayer = player;
}

Enermy::Enermy() : BaseTanks(false)
{

	mRotationSpeed = 60.0f;

	mMoveSpeed = 150.0f;

	// Delay Bullet
	mBulletsTimer = 0.0f;
	mBulletsDelay = 0.8f;

	mCurrentState = CHASE;
}

Enermy::~Enermy()
{

}


void Enermy::HandleStates()
{
	switch (mCurrentState)
	{
	case Enermy::AUTO:
		HandleAutoState();
		break;
	case Enermy::CHASE:
		HandleChaseState();
		break;
	case Enermy::DEAD:
		HandldeDeadState();
		break;
	default:
		break;
	}
}

void Enermy::HandleAutoState()
{

}

void Enermy::HandleChaseState()
{
	// Update barrel
	Vector2 direct = mPlayerPos - Pos();
	float barrelRotation = AngleBetweenVector(Vector2(0.0f, 1.0f), direct);
	if (mPlayerPos.x - Pos().x >= 0)
	{
		mBarrel->Rotation(-barrelRotation);
	}
	else {
		mBarrel->Rotation(barrelRotation);
	}

	// Move 
	float distance = (mHeadBarrel->Pos() - mPlayerPos).Magnitude();

	int tankRotation = static_cast<int>(mTank->Rotation());
	if (distance > mBullets[0]->FIRING_RANGE + 10.0f)
	{
		// Move horizontal
		if (mPlayerPos.x - Pos().x > 5.0f)
		{
			Translate(VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::world);
			if (tankRotation != 90 && tankRotation != 270)
				mTank->Rotate(mRotationSpeed * mTimer->DeltaTime());

		}
		else if (mPlayerPos.x - Pos().x < -5.0f) 
		{
			Translate(-VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::world);
			if (tankRotation != 90 && tankRotation != 270)
				mTank->Rotate(mRotationSpeed * mTimer->DeltaTime());
		}
		else {
			// Move vertical
			if (mPlayerPos.y - Pos().y >= 0)
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

void Enermy::HandldeDeadState()
{
	if (mDeathAnimation->IsAnimating())
	{
		mDeathAnimation->Update();
	}
}

void Enermy::HandleFiring()
{
	mBulletsTimer += mTimer->DeltaTime();
	if (mBulletsTimer >= mBulletsDelay)
	{
		mBulletsTimer = 0.0f;
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (!mBullets[i]->Active())
			{
				mBullets[i]->Fire(mHeadBarrel->Pos(), mPlayerPos);
				mAudio->PlaySFX("SFX/shoot_01.ogg");
				break;
			}
		}
	}
}

bool Enermy::IgnoreCollision()
{
	return !mVisible || mAnimating;
}

Enermy::STATES Enermy::CurrentState()
{
	return mCurrentState;
}

void Enermy::Hit(PhysicEntity* other)
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

void Enermy::Update(Vector2 playerPos)
{
	//printf("(X, Y) = (%f, %f)\n", mMap->MoveCamera().Approximate().x, mMap->MoveCamera().Approximate().y);
	Translate(-mMap->MoveCamera().Approximate());

	if (mAnimating)
	{
		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimating();
	}
	else
	{
		if (mWasHit)
			mWasHit = false;

		if (Active())
		{
			mPlayerPos = playerPos;
			HandleStates();
		}
	}

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i]->Update();
	}	
}

void Enermy::Render()
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