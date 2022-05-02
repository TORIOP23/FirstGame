//---------------------------------------------------------------------//
// GameManager.cpp                                                     //
// Used to intialize and release all other manager                     //
// Contains the game loop as well as the Update and Render functions   //
// Used to make sure all functions are called in the correct order     //
//---------------------------------------------------------------------//

#include "GameManager.h"

//Initializing to NULL
GameManager* GameManager::sInstance = NULL;

GameManager* GameManager::Instance()
{
	//Create a new instance if no instance was created before
	if (sInstance == NULL)
		sInstance = new GameManager();

	return sInstance;
}

void GameManager::Release()
{
	delete sInstance;
	sInstance = NULL;
}

GameManager::GameManager()
{
	mQuit = false;
	mGraphics = Graphics::Instance();

	if (!Graphics::Initialized())
		mQuit = true;

	//Initialize AssetManager
	mAssetMgr = AssetManager::Instance();

	//Initialize InputManager
	mInputMgr = InputManager::Instance();

	//Initialize AudioManager
	mAudioMgr = AudioManager::Instance();

	////Initialize Timer
	mTimer = Timer::Instance();

	mScreenMgr = ScreenManager::Instance();
}

GameManager::~GameManager()
{
	ScreenManager::Release();
	mScreenMgr = NULL;

	AudioManager::Release();
	mAudioMgr = NULL;

	AssetManager::Release();
	mAssetMgr = NULL;

	Graphics::Release();
	mGraphics = NULL;

	InputManager::Release();
	mInputMgr = NULL;

	Timer::Release();
	mTimer = NULL;
	
}

void GameManager::EarlyUpdate()
{
	//Updating the input state before any other updates are run to make sure the Input check is accrate
	mTimer->Reset();
	mInputMgr->Update();
	
}

void GameManager::Update()
{
	//GameEntity Update should happen here;
	mScreenMgr->Update();

	if (mInputMgr->KeyDown(SDL_SCANCODE_1))
	{
		mAudioMgr->PlayMusic("URF.wav");
	}
	else if (mInputMgr->KeyPressed(SDL_SCANCODE_W))
	{
		printf("W key pressed\n");
	} 
	else if (mInputMgr->KeyReleased(SDL_SCANCODE_W))
	{
		printf("W key released\n");
	}

	if (mInputMgr->MouseButtonPressed(InputManager::left))
	{
		printf("left mouse button pressed\n");
	}
	else if (mInputMgr->MouseButtonReleased(InputManager::left))
	{
		printf("left mouse button released\n");
	}
	
}

void GameManager::LateUpdate()
{
	//Any collision detection should happen here

	mInputMgr->UpdatePrevInput();
}

void GameManager::Render()
{
	//	SDL_SetRenderDrawColor(GameManager::renderer, 50, 160, 97, 255);

	//Clears the last frame's render from the back buffer
	mGraphics->ClearBackBuffer();

	//All other rendering is happen here
	mScreenMgr->Render();

	//Renders the current frame
	mGraphics->Render();
}

void GameManager::Run()
{
	while (!mQuit)
	{
		mTimer->Update();

		while (SDL_PollEvent(&mEvents) != 0)
		{
			if (mEvents.type == SDL_QUIT)
			{
				mQuit = true;
			}
		}

		if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE))
		{
			
			EarlyUpdate();
			Update();
			LateUpdate();
			Render();
		}

	}
}