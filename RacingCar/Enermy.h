#pragma once

#include "BaseTanks.h"
#include "Player.h"

class Enermy : public BaseTanks
{
public: 

	enum STATES { AUTO = 0, CHASE = 1, DEAD };

private:

	static Player* sPlayer;

	// Delay Bullet
	float mBulletsTimer;
	float mBulletsDelay;

	STATES mCurrentState;

	Vector2 mPlayerPos;

private:

	void HandleAutoState();
	void HandleChaseState();
	void HandldeDeadState();

	void HandleStates();

	void HandleFiring();

	bool IgnoreCollision() override;

public:

	static void CurrentPlayer(Player* player);

	Enermy();

	~Enermy();

	STATES CurrentState();

	void Hit(PhysicEntity* other) override;

	void Update(Vector2 playerPos);

	void Render();

};