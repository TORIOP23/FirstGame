#pragma once

#include "BaseTanks.h"
#include "Player.h"

class Enemy : public BaseTanks
{
public: 

	enum STATES { AUTO = 0, CHASE = 1 };

private:

	static Player* sPlayer;

	// Delay Bullet
	float mBulletsTimer;
	float mBulletsDelay;

	STATES mCurrentState;

	//AUTO
	const float mDistanceMoveAuto = 100.0f;
	float mMoveAuto;
	float mSign = 1.0f;

	Vector2 mPrePos;

private:

	void HandleAutoState();
	void HandleChaseState();

	void HandleStates();

	void HandleFiring();

	bool IgnoreCollision() override;

public:

	static void CurrentPlayer(Player* player);

	Enemy();

	~Enemy();

	STATES CurrentState();

	void Hit(PhysicEntity* other) override;

	void PlayerHitEnemy(PhysicEntity* other) override;

	void Update();

	void Render();

};