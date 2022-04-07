#pragma once

#include "GameObject.h"
#include "Game.h"

static const double INCREASE_ANGLE = 45;

class Player : public GameObject
{
public:
	//Player();
	Player(Colors color);
	~Player();

	void HandleInput();
	void Update();
	void Draw();

	/*void DoPlayer(Map& map_data);
	void CheckToMap(Map& map_data);*/

private:
	int speed;

	int velocX;
	int velocY;

	double angle;

	int x_pos; // vi tri
	int y_pos; // vi tri

	//Input input_type;    // luu trang thai di chuyen
	int frame;  // frame hien tai
	int status;  // status hien tai
	bool on_ground;


};
