#pragma once

#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "Bullet.h"

class Enermy : public GameEntity
{
public: 

	enum STATES { AUTO = 0, CHASE = 1, DEAD };

private:

	Timer* mTimer;
	AudioManager* mAudio;

	bool mVisible;
	bool mAnimating;

	//unsigned int mScore;
	unsigned int mHealth;;

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

	STATES mCurrentState;

	Vector2 mTargetPosition;

private:

	void HandleAutoState();
	void HandleChaseState();
	void HandldeDeadState();

	void HandleStates();

public:

	Enermy();

	~Enermy();

	STATES CurrentState();

	void Update();

	void Render();

};








//#include "GameObject.h"
//#include "Map.h"
//
//
//class Enermy : public GameObject
//{
//public:
//	Enermy(Colors color);
//	~Enermy();
//
//	enum class Status { UP, DOWN, LEFT, RIGHT };
//
//	void CheckMap(const Map* data);
//	void Update(const Map* data);
//	void Draw();
//	
//private:
//	int speed;
//
//	int velocX;
//	int velocY;
//
//	double angle;
//
//	SDL_Rect desR;
//
//	Status status;
//};
//
//class Enermy
//{
//};

