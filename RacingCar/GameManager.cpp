// GameManager.cpp
// Used to intialize and release all other manager
// Contains the game loop as well as the Update and Render functions
// Used to make sure all functions are called in the correct order

#include "GameManager.h"
#include <time.h>

//Initializing to NULL
GameManager* GameManager::sInstance = nullptr;

GameManager* GameManager::Instance()
{
	//Create a new instance if no instance was created before
	if (sInstance == nullptr)
		sInstance = new GameManager();

	return sInstance;
}

void GameManager::Release()
{
	delete sInstance;
	sInstance = nullptr;
}

GameManager::GameManager()
{
	srand(time(0));

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

	//Initialize Timer
	mTimer = Timer::Instance();

	// Physic Manager
	mPhysicMgr = PhysicManager::Instance();
	mPhysicMgr->SetLayerCollisionMask(PhysicManager::CollisionLayers::Friendly, PhysicManager::CollisionFlags::Hostile | PhysicManager::CollisionFlags::HostileProjectiles);
	mPhysicMgr->SetLayerCollisionMask(PhysicManager::CollisionLayers::FriendlyProjectiles, PhysicManager::CollisionFlags::Hostile);
	mPhysicMgr->SetLayerCollisionMask(PhysicManager::CollisionLayers::Hostile, PhysicManager::CollisionFlags::Friendly | PhysicManager::CollisionFlags::FriendlyProjectiles);
	mPhysicMgr->SetLayerCollisionMask(PhysicManager::CollisionLayers::HostileProjectiles, PhysicManager::CollisionFlags::Friendly);


	// Manager screen 
	mScreenMgr = ScreenManager::Instance();
}

GameManager::~GameManager()
{
	ScreenManager::Release();
	mScreenMgr = nullptr;

	PhysicManager::Release();
	mPhysicMgr = nullptr;

	AudioManager::Release();
	mAudioMgr = nullptr;

	AssetManager::Release();
	mAssetMgr = nullptr;

	Graphics::Release();
	mGraphics = nullptr;

	InputManager::Release();
	mInputMgr = nullptr;

	Timer::Release();
	mTimer = nullptr;
	
}

void GameManager::EarlyUpdate()
{
	//Updating the input state before any other updates are run to make sure the Input check is accrate
	mInputMgr->Update();
}

void GameManager::Update()
{
	//GameEntity Update should happen here;
	mScreenMgr->Update();
	mQuit = mScreenMgr->Exit();
}

void GameManager::LateUpdate()
{
	//Any collision detection should happen here
	mPhysicMgr->Update();

	mInputMgr->UpdatePrevInput();
	mTimer->Reset();
}

void GameManager::Render()
{
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