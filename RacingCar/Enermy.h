#pragma once
#include "GameObject.h"
#include "Map.h"


class Enermy : public GameObject
{
public:
	Enermy(Colors color);
	~Enermy();

	enum class Status { UP, DOWN, LEFT, RIGHT };

	void CheckMap(const Map* data);
	void Update(const Map* data);
	void Draw();
	
private:
	int speed;

	int velocX;
	int velocY;

	double angle;

	SDL_Rect desR;

	Status status;
};

