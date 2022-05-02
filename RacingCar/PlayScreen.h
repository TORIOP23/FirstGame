#pragma once

#include "InputManager.h"
#include "GameEntity.h"
#include "Timer.h"

class PlayScreen : public GameEntity
{
private:
	Timer* mTimer;
	InputManager* mInput;



public:
	PlayScreen();
	~PlayScreen();

	void Update();
	void Render();

};
