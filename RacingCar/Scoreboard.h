// Scoreboard.h 
// Keep track score of player

#pragma once
#include <vector>
#include "Texture.h"


class Scoreboard : public GameEntity
{
private:

	std::vector<Texture*> mScore;

	SDL_Color mColor;
	int mSize;
	int mScore1;

public:

	Scoreboard(int size = 32);

	Scoreboard(SDL_Color color, int size = 32);

	~Scoreboard();

	// setter
	void Score(int score);

	//getter
	int Score();

	void Render();

private:
	void ClearScore();
};

