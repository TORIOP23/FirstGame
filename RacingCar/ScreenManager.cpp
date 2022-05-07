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
	mAudio = AudioManager::Instance();


	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();

	mCurrentScreen = START;
}

ScreenManager::~ScreenManager()
{
	mInput = NULL;
	mAudio = NULL;

	delete mStartScreen;
	mStartScreen = NULL;

	delete mPlayScreen;
	mPlayScreen = NULL;
}

void ScreenManager::Update()
{

	switch (mCurrentScreen)
	{
	case ScreenManager::START:
		mStartScreen->Update();
		if (mStartScreen->SelectedMode() == StartScreen::PLAY)
		{
			if (mInput->MouseButtonPressed(InputManager::LEFT))
			{
				mAudio->PlaySFX("SFX/click1.ogg");

				mCurrentScreen = PLAY;

				mStartScreen->ResetAnimation();

				mPlayScreen->StartNewGame();
			}
		}
		break;
	case ScreenManager::PLAY:

		mPlayScreen->Update();

		if (mPlayScreen->GameOver())
		{
			mCurrentScreen = START;
			mAudio->PlayMusic("Music/pickBan.wav");
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
	case ScreenManager::START:
		mStartScreen->Render();
		break;
	case ScreenManager::PLAY:
		mPlayScreen->Render();
		break;
	default:
		break;
	}
}
