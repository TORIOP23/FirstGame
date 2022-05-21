#pragma once

#include "PhysicEntity.h"
#include "AnimatedTexture.h"
#include "Bullet.h"
#include "AudioManager.h"
#include "Map.h"


class BaseTanks : public PhysicEntity
{
protected:
	Timer* mTimer;
	AudioManager* mAudio;

	// Map
	Map* mMap;

	//Set to true if the object is to be updated and not rendered  
	bool mVisible;
	bool mAnimating;
	bool mWasHit;

	// Tanks
	Texture* mTank;
	Texture* mBarrel;
	GameEntity* mHeadBarrel;

	// Death
	AnimatedTexture* mDeathAnimation;


	// Healthbar 
	unsigned int mHealth;
	static const unsigned int MAX_HEALTH = 21; // full = 20
	Texture* mHealthBar[MAX_HEALTH];

	//Bullet
	static const unsigned int MAX_BULLETS = 5;
	Bullet* mBullets[MAX_BULLETS];

	//Speed
	float mMoveSpeed;
	float mRotationSpeed;

public:

	BaseTanks(bool player);

	~BaseTanks();

	// Setter
	void SetTankColor(PhysicEntity::Color color = PhysicEntity::BEIGE);
	void SetBarrelColor(PhysicEntity::Color color = PhysicEntity::BEIGE);
	void Visible(bool visible);


	// Getter 
	bool WasHit() const;

	bool IsAnimating() const;

	int Health() const;

	float Speed() const;

};

