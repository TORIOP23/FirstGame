#include "Bullet.h"
#include "BoxCollider.h"
#include "PhysicManager.h"

Bullet::Bullet(bool friendly)
{
	mTimer = Timer::Instance();

	mMap = Map::Instance();

	mSpeed = 700.0f;

	mTexture = new Texture("PNG/Bullets/bulletBeige.png");
	mTexture->Parent(this);
	mTexture->Pos(VEC2_ZERO);

	Reload();

	AddCollider(new BoxCollider(mTexture->ScaleDimensions()));

	if (friendly)
		mId = PhysicManager::Instance()->RegisterEntity(this, PhysicManager::CollisionLayers::FriendlyProjectiles);
	else
		mId = PhysicManager::Instance()->RegisterEntity(this, PhysicManager::CollisionLayers::HostileProjectiles);

}

Bullet::~Bullet()
{
	mTimer = nullptr;

	mMap = nullptr;

	delete mTexture;
	mTexture = nullptr;
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

void Bullet::Hit(PhysicEntity* other)
{
	Reload();
}

bool Bullet::IgnoreCollision()
{
	return !Active();
}

void Bullet::Update()
{
	Translate(-mMap->MoveCamera().Approximate());

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
		PhysicEntity::Render();
		mTexture->Render();
	}
}


