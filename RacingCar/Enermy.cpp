#include "Enermy.h"
#include "BoxCollider.h"
#include "PhysicManager.h"

Player* Enermy::sPlayer = nullptr;

void Enermy::CurrentPlayer(Player* player)
{
	sPlayer = player;
}

Enermy::Enermy()
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mMap = Map::Instance();

	mVisible = true;
	mAnimating = false;
	mWasHit = false;

	mHealth = 20; 
	
	// Tank
	mTank = new Texture("PNG/tanks/tankBlue.png");
	mTank->Parent(this);
	mTank->Pos(VEC2_ZERO);

	mBarrel = new Texture("PNG/tanks/barrelBeige.png");
	mBarrel->Parent(this);
	mBarrel->Pos(Vector2(0.0f, 0.0f));

	mHeadBarrel = new GameEntity();
	mHeadBarrel->Parent(mBarrel);
	mHeadBarrel->Pos(Vector2(0.0f, 50.0f));

	mDeathAnimation = new AnimatedTexture("PNG/Death/tankBeige.png", 0, 0, 100, 100, 4, 1.0f, AnimatedTexture::VERTICAL);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Pos(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::ONCE);


	// Health Bar
	std::string filename = "PNG/Health_Bars/health_";
	for (unsigned int i = 0; i < MAX_HEALTH; i++)
	{
		std::string file = filename + std::to_string(i) + ".png";
		mHealthBar[i] = new Texture(file);
	}

	for (unsigned int i = 0; i < MAX_HEALTH; i++)
	{
		mHealthBar[i]->Parent(this);
		mHealthBar[i]->Pos(Vector2(0.0f, 50.0f));
		mHealthBar[i]->Scale(Vector2(0.25f, 0.3f));
	}

	mRotationSpeed = 60.0f;

	mMoveSpeed = 100.0f;

	// Bullets
	for (unsigned int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i] = new Bullet(false);
	}
	mBulletsTimer = 0.0f;
	mBulletsDelay = 0.8f;

	mCurrentState = CHASE;

	// Collider 
	AddCollider(new BoxCollider(mTank->ScaleDimensions()));

	mId = PhysicManager::Instance()->RegisterEntity(this, PhysicManager::CollisionLayers::Hostile);
}

Enermy::~Enermy()
{
	mTimer = NULL;
	mAudio = NULL;

	mMap = NULL;

	// Free Player
	delete mHeadBarrel;
	mHeadBarrel = NULL;

	delete mBarrel;
	mBarrel = NULL;

	delete mTank;
	mTank = NULL;

	delete mDeathAnimation;
	mDeathAnimation = NULL;

	// Freeing HealthBar 
	for (unsigned int i = 0; i < MAX_HEALTH; i++)
	{
		delete mHealthBar[i];
		mHealthBar[i] = NULL;
	}

	// Freeing Bullets
	for (unsigned int i = 0; i < MAX_BULLETS; i++)
	{
		delete mBullets[i];
		mBullets[i] = NULL;
	}
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

void Enermy::Visible(bool visible)
{
	mVisible = visible;
}

bool Enermy::IsAnimating()
{
	return mAnimating;
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

bool Enermy::WasHit()
{
	return mWasHit;
}

int Enermy::Health()
{
	return mHealth;
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