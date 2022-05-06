// StartScreen.h
// Menu Screen
// 

#pragma once

#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"

class StartScreen : public GameEntity
{
public:

	enum MODE { NONE, PLAY, EXIT };

private:

	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	// Background
	Texture* mBkg;

	// Top Bar Entities
	GameEntity* mTopBar;
	Texture* mDates; 
	Texture* mVersion;


	//Play Mode Entities
	GameEntity* mPlayModes;
	Texture* mPlayButton;
	Texture* mPlayMode;
	Texture* mExitButton;
	Texture* mExitMode;

	MODE mSeLectedMode;

	//Bottom Bar Entities
	GameEntity* mBotBar;
	Texture* mCompany;
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

	// set mode
	void Mode();

	// get mode
	MODE SelectedMode();

	void Update();

	void Render();

};
