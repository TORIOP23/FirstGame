// Scoreboard.cpp 
// Keep track Score of player

#include "Scoreboard.h"

Scoreboard::Scoreboard() : Scoreboard({ 230, 230, 230 })
{

}

Scoreboard::Scoreboard(SDL_Color color)
{
	mColor = color;
	Score(0);
}

Scoreboard::~Scoreboard()
{
	ClearScore();
}

void Scoreboard::ClearScore()
{
	for (int i = 0; i < mScore.size(); i++)
	{
		delete mScore[i];
		mScore[i] = NULL;
	}

	mScore.clear();
}

void Scoreboard::Score(int score)
{
	ClearScore();

	if (score == 0)
	{
		// show 00 
		for (int i = 0; i < 2; i++)
		{
			mScore.push_back(new Texture("0", "fonts/lol1.ttf", 32, mColor));
			mScore[i]->Parent(this);
			mScore[i]->Pos(Vector2(-32.0f * i, 0.0f));
		}
	}
	else {
		std::string str = std::to_string(score);
		int lastIndex = str.length() - 1;

		for (int i = 0; i <= lastIndex; i++)
		{
			// cache 1 character one by one 
			mScore.push_back(new Texture(str.substr(i, 1), "fonts/lol1.ttf", 32, { 230, 230, 230 }));
			mScore[i]->Parent(this);
			mScore[i]->Pos(Vector2(-32.0f * (lastIndex - i), 0.0f));
		}
	}
}

void Scoreboard::Render()
{
	for (int i = 0; i < mScore.size(); i++)
	{
		mScore[i]->Render();
	}
}
