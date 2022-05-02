#include "Enermy.h"


Enermy::Enermy(Colors color) : GameObject(color)
{
	speed = rand() % 5 + 7;
	std::cout << speed << '\n';
	velocX = 0;
	velocY = 0;

	angle = 90.0;

	desR.w = desR.h = 64;
	desR.x = 385;
	desR.y = 512;

	status = Status::LEFT;
}

Enermy::~Enermy() {}

void Enermy::CheckMap(const Map* data) 
{
	if (status == Status::LEFT)
	{
		int row, col;
		row = (desR.x / 64) + 1;
		col = desR.y / 64;
		if (data->map[col][row] == 28) 
		{
			velocX = 1;
		}
		else if (data->map[col - 1][row - 1] == 23)
		{
			velocX = 0;
			velocY = -1;
		}

	}
}

void Enermy::Update(const Map* data) 
{
	desR.x += (velocX * speed);
	desR.y += (velocY * speed);
}

void Enermy::Draw()
{
	SDL_RenderCopyEx(GameManager::renderer, objTexture, NULL, &desR, angle, NULL, SDL_FLIP_NONE);
}