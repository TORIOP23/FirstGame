// ScreenManager.cpp
// Singleton
//

#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = NULL;

ScreenManager* ScreenManager::Instance()
{
	if (sInstance == NULL)
		sInstance = new ScreenManager();
	return sInstance;
}

void ScreenManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

ScreenManager::ScreenManager()
{
	mInput = InputManager::Instance();
	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();

	mCurrentScreen = start;
}

ScreenManager::~ScreenManager()
{
	mInput = NULL;

	delete mStartScreen;
	mStartScreen = NULL;

	delete mPlayScreen;
	mPlayScreen = NULL;
}

void ScreenManager::Update()
{

	switch (mCurrentScreen)
	{
	case ScreenManager::start:
		mStartScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_RETURN))
		{
			mCurrentScreen = play;
			mStartScreen->ResetAnimation();
		}
		break;
	case ScreenManager::play:

		mPlayScreen->Update();
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE))
		{
			mCurrentScreen = start;
		}
		break;
	default:
		break;
	}
}

void ScreenManager::Render()
{
	switch (mCurrentScreen)
	{
	case ScreenManager::start:
		mStartScreen->Render();
		break;
	case ScreenManager::play:
		mPlayScreen->Render();
		break;
	default:
		break;
	}
}
