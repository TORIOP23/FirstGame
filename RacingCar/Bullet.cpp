#include "Bullet.h"


Bullet::Bullet()
{
	mTimer = Timer::Instance();

	mSpeed = 500.0f;

	mTexture = new Texture("PNG/Bullets/bulletBeige.png");
	mTexture->Parent(this);
	mTexture->Pos(VEC2_ZERO);

	Reload();
}

Bullet::~Bullet()
{
	mTimer = NULL;

	delete mTexture;
	mTexture = NULL;
}

void Bullet::Fire(Vector2 pos, Vector2 mousePos)
{
	Pos(pos);
	mStartPos = pos;
	mBulletDirection = (mousePos - Pos()).Normalized();
	Active(true);
}

void Bullet::Reload()
{
	Active(false);
}

void Bullet::Update()
{
	float range = (Pos() - mStartPos).MagnitudeSqr();

	if (Active())
	{
		if (range < FIRING_RANGE * FIRING_RANGE)
		{
			Translate(mBulletDirection * mSpeed * mTimer->DeltaTime(), world);

			if (mBulletDirection.x >= 0)
				Rotation(-AngleBetweenVector(Vector2(0.0f, 1.0f), mBulletDirection));
			else Rotation(AngleBetweenVector(Vector2(0.0f, 1.0f), mBulletDirection));
		} 
		else
		{
			Reload();
		}
	}
}

void Bullet::Render()
{
	if (Active())
	{
		mTexture->Render();
	}
}
