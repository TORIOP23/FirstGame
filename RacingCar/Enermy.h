#pragma once

#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "Bullet.h"
#include "Player.h"

class Enermy : public PhysicEntity
{
public: 

	enum STATES { AUTO = 0, CHASE = 1, DEAD };

private:

	Timer* mTimer;
	AudioManager* mAudio;

	static Player* sPlayer;

	Map* mMap;

	bool mVisible;
	bool mAnimating;
	bool mWasHit;

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

	bool IgnoreCollision() override;

public:

	static void CurrentPlayer(Player* player);

	Enermy();

	~Enermy();

	// Setter
	void Visible(bool visible);

	// Getter mAnimating
	bool IsAnimating();

	STATES CurrentState();

	void Hit(PhysicEntity* other) override;

	bool WasHit();

	int Health();

	void Update(Vector2 playerPos);

	void Render();

};