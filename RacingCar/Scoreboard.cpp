// Scoreboard.cpp 
// Keep track Score of player

#include "Scoreboard.h"

Scoreboard::Scoreboard(int size)
{
	mColor = { 230, 230, 230 };
	mSize = size;
	Score(0);
}

Scoreboard::Scoreboard(SDL_Color color, int size)
{
	mColor = color;
	mSize = size;
	Score(0);
}

Scoreboard::~Scoreboard()
{
	ClearScore();
}

void Scoreboard::ClearScore()
{
	mScore1 = 0;

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

	mScore1 = score;

	if (score == 0)
	{
		// show 00 
		for (int i = 0; i < 2; i++)
		{
			mScore.push_back(new Texture("0", "fonts/2.ttf", mSize, mColor));
			mScore[i]->Parent(this);
			mScore[i]->Pos(Vector2(-32.0f * i, 0.0f));
		}
	}
	else {
		std::string str = std::to_string(score);
		int lastIndex = static_cast<int>(str.length() - 1);

		for (int i = 0; i <= lastIndex; i++)
		{
			// cache 1 character one by one 
			mScore.push_back(new Texture(str.substr(i, 1), "fonts/2.ttf", mSize, mColor));
			mScore[i]->Parent(this);
			// 25 is space between two character
			mScore[i]->Pos(Vector2(-25.0f * (lastIndex - i), 0.0f));
		}
	}
}

int Scoreboard::Score()
{
	return mScore1;
}

void Scoreboard::Render()
{
	for (int i = 0; i < mScore.size(); i++)
	{
		mScore[i]->Render();
	}
}
