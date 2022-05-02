#pragma once

#include "GameObject.h"
#include "GameManager.h"
#include "Map.h"

class Player : public GameObject
{
public:
	//Player();
	Player(Colors color);
	~Player();

	void HandleInput();
	void Update(const Map* data);
	void Draw();

	/*void DoPlayer(Map& map_data);
	void CheckToMap(Map& map_data);*/

private:
	int speed;

	double velocX;
	double velocY;

	double angle;

	SDL_Rect desR;
	//Input input_type;    // luu trang thai di chuyen

	//int status;  // status hien tai
	//bool on_ground;


};
