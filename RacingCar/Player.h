#pragma once

#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Bullet.h"
#include "PhysicEntity.h"

class Player : public PhysicEntity
{
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	//Set to true if the object is to be updated and not rendered  
	bool mVisible;
	bool mAnimating;

	unsigned int mScore;
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

	// Arrow
	Texture* mArrow;

	float mRotationSpeed;

	float mMoveSpeed;

	static const unsigned int MAX_BULLETS = 5;
	Bullet* mBullets[MAX_BULLETS];

private:

	void HandleMovement();
	
	void HandleFiring();

public:
	
	Player();

	~Player();

	// Setter
	void Visible(bool visible);

	// Getter mAnimating
	bool IsAnimating();

	int Score();

	int Health();

	float Speed();

	void AddScore(int change);

	void WasHit();

	void Update();

	void Render();

};

//#include "GameObject.h"
//#include "GameManager.h"
//#include "Map.h"
//
//class Player : public GameObject
//{
//public:
//	//Player();
//	Player(Colors color);
//	~Player();
//
//	void HandleInput();
//	void Update(const Map* data);
//	void Draw();
//
//	/*void DoPlayer(Map& map_data);
//	void CheckToMap(Map& map_data);*/
//
//private:
//	int speed;
//
//	double velocX;
//	double velocY;
//
//	double angle;
//
//	SDL_Rect desR;
//	//Input input_type;    // luu trang thai di chuyen
//
//	//int status;  // status hien tai
//	//bool on_ground;
//
//
//};
