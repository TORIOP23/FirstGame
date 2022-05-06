#pragma once
#include <vector>
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"

class Player : public GameEntity
{
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	//Set to true if the object is to be updated and not rendered  
	bool mVisible;
	bool mAnimating;

	int mScore;
	int mHealth;;

	// Tanks
	Texture* mTank;
	Texture* mBarrel;

	// Death
	AnimatedTexture* mDeathAnimation;

	// Healthbar 
	std::vector<Texture*> mHealthBar;

	float mRotationSpeed;

	float mMoveSpeed;

private:

	void HandleMovement();

public:
	
	Player();

	~Player();

	void Visible(bool visible);

	bool IsAnimating();

	int Score();

	int Health();

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
