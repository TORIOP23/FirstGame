#pragma once

#include "Timer.h"
#include "Texture.h"

class Bullet : public GameEntity
{
private:
	// 10 pixel, disable the bullet
	const int OFFSCREEN_BUFFER = 10;

	Timer* mTimer;

	float mSpeed;

	Texture* mTexture;

	Vector2 mBulletDirection;

public:

	Bullet();

	~Bullet();

	void Fire(Vector2 pos, Vector2 mousePos);

	// get ready to be fired again
	void Reload();

	void Update();

	void Render();
};

