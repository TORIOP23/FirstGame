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

public:

	Scoreboard();

	Scoreboard(SDL_Color color);

	~Scoreboard();

	// setter
	void Score(int score);

	void Render();

private:
	void ClearScore();
};

