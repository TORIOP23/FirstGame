#pragma once

#include "Timer.h"
#include "PhysicEntity.h"
#include "Map.h"

class Bullet : public PhysicEntity
{
public:

	const float FIRING_RANGE = 500.0f;

private:

	Timer* mTimer;

	Map* mMap;

	float mSpeed;

	Texture* mTexture;

	Vector2 mBulletDirection;

	Vector2 mStartPos;

public:

	Bullet(bool friendly);

	~Bullet();

	void Fire(Vector2 pos, Vector2 mousePos);

	// get ready to be fired again
	void Reload();

	void Hit(PhysicEntity* other) override;

	void Update();

	void Render();

private:

	bool IgnoreCollision() override;
};

