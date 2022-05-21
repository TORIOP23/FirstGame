// ScreenManager.h
// Singleton

#pragma once
#include "StartScreen.h"
#include "PlayScreen.h"

class ScreenManager
{
public:
	enum SCREENS { START, PLAY };

private:
	
	//Needed to make AssetManager a singleton class
	static ScreenManager* sInstance;

	InputManager* mInput;
	AudioManager* mAudio;
	StartScreen* mStartScreen;
	PlayScreen* mPlayScreen;

	SCREENS mCurrentScreen;

	bool mQuit;
public:
	//Returns a pointer to the class instance 
	static ScreenManager* Instance();

	//Releases the class instance and sets it back to NULL 
	static void Release();

	bool Exit() const;

	void Update();

	void Render();

private:
	//Contructor is private so that Instance() must be used to get an instance when needed
	ScreenManager();

	//Destructor is private so that the instance can only be destroyed using Release()  
	~ScreenManager();

};

