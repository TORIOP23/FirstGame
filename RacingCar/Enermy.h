#pragma once

#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "Bullet.h"
#include "PhysicEntity.h"

class Enermy : public PhysicEntity
{
public: 

	enum STATES { AUTO = 0, CHASE = 1, DEAD };

private:

	Timer* mTimer;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;

	//unsigned int mScore;
	unsigned int mHealth;

	// Tanks
	Texture* mTank;
	Texture* mBarrel;
	GameEntity* mHeadBarrel;

	// Death
	AnimatedTexture* mDeathAnimation;

	// Healthbar 
	static const unsigned int MAX_HEALTH = 21; // full = 20
	Texture* mHealthBar[MAX_HEALTH];

	float mRotationSpeed;

	float mMoveSpeed;

	static const unsigned int MAX_BULLETS = 5;
	Bullet* mBullets[MAX_BULLETS];
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

public:

	Enermy();

	~Enermy();

	// Setter
	void Visible(bool visible);

	// Getter mAnimating
	bool IsAnimating();

	STATES CurrentState();

	void WasHit();

	int Health();

	void Update(Vector2 playerPos);

	void Render();

};