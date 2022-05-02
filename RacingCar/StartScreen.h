// StartScreen.h
// Menu
// 

#pragma once

#include "AnimatedTexture.h"
#include "InputManager.h"

class StartScreen : public GameEntity
{
private:
	Timer* mTimer;
	InputManager* mInput;

	// Top Bar Entities
	GameEntity* mTopBar;
	Texture* mHiScore;

	//logo Entities
	Texture* mLogo;
	//AnimatedTexture* mAnimatedLogo;

	//Play Mode Entities
	GameEntity* mPlayModes;
	Texture* mOnePlayerMode;
	Texture* mTwoPlayerMode;
	Texture* mCursor;

	Vector2 mCursorStartPos;
	Vector2 mCursorOffset;
	int mSelectedMode;

	//Bottom Bar Entities
	GameEntity* mBotBar;
	Texture* mDates;
	Texture* mNamco;
	Texture* mRights;

	//Screen Animation Variables
	Vector2 mAnimationStartPos;
	Vector2 mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;

public:

	StartScreen();
	~StartScreen();

	void ResetAnimation();

	int SelectedMode();

	void ChangeSelectedMode(int change);

	void Update();

	void Render();

};
