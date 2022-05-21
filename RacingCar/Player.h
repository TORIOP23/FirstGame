#pragma once

#include "BaseTanks.h"
#include "InputManager.h"

class Player : public BaseTanks
{
private:
	InputManager* mInput;

	unsigned int mScore;

	// Arrow
	Texture* mArrow;

private:

	bool IgnoreCollision() override;

	void HandleMovement();
	
	void HandleFiring();

public:
	
	Player();

	~Player();

	void Hit(PhysicEntity* other) override;

	int Score();

	void AddScore(int change);

	void Update();

	void Render();

};
