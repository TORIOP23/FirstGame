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
	unsigned int mSize;
	unsigned int mScore1;

public:

	Scoreboard(unsigned int size = 32);

	Scoreboard(SDL_Color color, unsigned int size = 32);

	~Scoreboard();

	// setter
	void Score(unsigned int score);

	//getter
	int Score();

	void Render();

private:
	void ClearScore();
};

