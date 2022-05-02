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

	mTex = new Texture("Leagua of legend", "LOL1.ttf", 60, {0, 255, 0});
	mTex->Pos(Vector2(300, 300));
	mTex->Scale(Vector2(1.0f, 0.5f));

	mTex2 = new Texture("Welcome to summoner's rift", "LOL2.ttf", 60, { 255, 0, 0 });
	mTex2->Pos(Vector2(450, 600));


	mTex2->Parent(mTex);
}

GameManager::~GameManager()
{
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

	delete mTex;
	mTex = NULL;

	delete mTex2;
	mTex2 = NULL;
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

	mTex->Rotate(30.0f * mTimer->DeltaTime());
	mTex2->Rotate(-30.0f * mTimer->DeltaTime());
	printf("mTex rotation: %f\n", mTex->Rotation(GameEntity::world));
	//mTex->Update();
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
	mTex->Render();
	mTex2->Render();

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