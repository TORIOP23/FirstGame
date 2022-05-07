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
	mBulletDirection = (mousePos - Pos()).Normalized();
	Active(true);
}

void Bullet::Reload()
{
	Active(false);
}

void Bullet::Update()
{
	if (Active())
	{
		Translate(mBulletDirection * mSpeed * mTimer->DeltaTime(), world);

		if (mBulletDirection.x >= 0)
			Rotation(-AngleBetweenVector(Vector2(0.0f, 1.0f), mBulletDirection));
		else Rotation(AngleBetweenVector(Vector2(0.0f, 1.0f), mBulletDirection));

		Vector2 pos = Pos();

		if (pos.y < -OFFSCREEN_BUFFER || pos.y > Graphics::SCREEN_HEIGHT + OFFSCREEN_BUFFER)
		{
			Reload();
		}

		if (pos.x < -OFFSCREEN_BUFFER || pos.x > Graphics::SCREEN_WIDTH + OFFSCREEN_BUFFER)
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
