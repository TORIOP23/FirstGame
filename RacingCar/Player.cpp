#include "Player.h"

Player::Player() : BaseTanks(true)
{
	mInput = InputManager::Instance();

	mScore = 0;

	// Arrow 
	mArrow = new Texture("PNG/arrowPlayer.png");
	mArrow->Parent(this);
	mArrow->Pos(Vector2(0.0f, -80.0f));

	mPrePos = VEC2_ZERO;
}

Player::~Player()
{
	mInput = nullptr;

	// Arrow 
	delete mArrow;
	mArrow = nullptr;

}

bool Player::IgnoreCollision()
{
	return !mVisible || mAnimating;
}

void Player::HandleMovement()
{
	// Move barrel
	Vector2 MousePosToPlayer = mInput->MousePos() - Pos();

	float barrelRotation = AngleBetweenVector(Vector2(0.0f, 1.0f), MousePosToPlayer);
	if (mInput->MousePos().x - Pos().x >= 0)
	{
		mBarrel->Rotation(-barrelRotation);
	}
	else {
		mBarrel->Rotation(barrelRotation);
	}

	// Move tank 
	int tankRotation = static_cast<int>(mTank->Rotation());
	if (mInput->KeyDown(SDL_SCANCODE_RIGHT))
	{
		if (Pos().x > Graphics::SCREEN_WIDTH * 0.5f && mMap->PosCamera().x < mMap->Dimension().x - Graphics::SCREEN_WIDTH)
			mMap->MoveCamera(VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime());
		else {
			Translate(VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::world);
		}
		if (tankRotation != 90 && tankRotation != 270)
			mTank->Rotate(mRotationSpeed * mTimer->DeltaTime());
	}
	if (mInput->KeyDown(SDL_SCANCODE_LEFT))
	{
		if (Pos().x < Graphics::SCREEN_WIDTH * 0.5f && mMap->PosCamera().x > 0)
			mMap->MoveCamera(-VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime());
		else {
			Translate(-VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime(), GameEntity::world);
		}
			if (tankRotation != 90 && tankRotation != 270)
			mTank->Rotate(mRotationSpeed * mTimer->DeltaTime());
	}

	if (mInput->KeyDown(SDL_SCANCODE_UP))
	{
		if (Pos().y < Graphics::SCREEN_HEIGHT * 0.5f && mMap->PosCamera().y > 0)
			mMap->MoveCamera(VEC2_UP * mMoveSpeed * mTimer->DeltaTime());
		else {
			Translate(VEC2_UP * mMoveSpeed * mTimer->DeltaTime(), GameEntity::world);
		}
		if (tankRotation != 0 && tankRotation != 180)
			mTank->Rotate(-mRotationSpeed * mTimer->DeltaTime());
	}
	if (mInput->KeyDown(SDL_SCANCODE_DOWN))
	{
		if (Pos().y > Graphics::SCREEN_HEIGHT * 0.5f && mMap->PosCamera().y < mMap->Dimension().y - Graphics::SCREEN_HEIGHT)
			mMap->MoveCamera(VEC2_DOWN * mMoveSpeed * mTimer->DeltaTime());
		else {
			Translate(VEC2_DOWN * mMoveSpeed * mTimer->DeltaTime(), GameEntity::world);
		}
		if (tankRotation != 0 && tankRotation != 180)
			mTank->Rotate(-mRotationSpeed * mTimer->DeltaTime());
	}

	// Check map
	Vector2 pos = Pos(local);
	if (pos.x < 0 + 50)
		pos.x = 0 + 50;
	else if (pos.x > Graphics::SCREEN_WIDTH - 50)
		pos.x =	Graphics::SCREEN_WIDTH - 50;

	if (pos.y < 0 + 50)
		pos.y = 0 + 50;
	else if (pos.y > Graphics::SCREEN_HEIGHT - 50)
		pos.y = Graphics::SCREEN_HEIGHT - 50;

	Pos(pos);
}

void Player::HandleFiring()
{
	if (mInput->MouseButtonPressed(InputManager::LEFT))
	{
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (!mBullets[i]->Active())
			{
				mBullets[i]->Fire(mHeadBarrel->Pos(), mInput->MousePos());
				mAudio->PlaySFX("SFX/shoot_01.ogg");
				break;
			}
		}
	}
}


void Player::Hit(PhysicEntity* other)
{
	if (mHealth > 0)
		mHealth--;
	if (mHealth == 0)
	{
		mDeathAnimation->ResetAnimation();
		mAnimating = true;
		mAudio->PlaySFX("SFX/explosion.wav");
	}
	else {
		mAudio->PlaySFX("SFX/tribe_d.wav");
	}

	mWasHit = true;
}

void Player::PlayerHitEnemy(PhysicEntity* other)
{
	printf("Pos = (%f, %f) ; PrePos = (%f, %f)\n", Pos().x, Pos().y, mPrePos.x, mPrePos.y);
	Pos(mPrePos);
}

int Player::Score()
{
	return mScore;
}


void Player::AddScore(int change)
{
	mScore += change;
}

void Player::Update()
{
	mPrePos = Pos();

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
			HandleMovement();
			HandleFiring();
		}
	}

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i]->Update();
	}
}

void Player::Render()
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
			mArrow->Render();
			mHealthBar[mHealth]->Render();
			mTank->Render();
			mBarrel->Render();
		}
	}
}