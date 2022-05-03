#pragma once
#include "AnimatedTexture.h"
#include "InputManager.h"

class Player : public GameEntity
{
private:
	Timer* mTimer;
	InputManager* mInput;

	bool mVisible;
	bool mAnimating;

	int mScore;
	int mLives;

	Texture* mTank;
	Texture* mBarrel;

	float mRotation;

	float mMoveSpeed;
	Vector2 mMoveBounds;

private:

	void HandleMovement();

public:
	
	Player();
	~Player();

	void Visible(bool visible);
	bool IsAnimating();

	int Score();
	int Lives();

	void AddScore(int change);

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
