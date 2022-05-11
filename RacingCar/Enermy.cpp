#include "Enermy.h"

Enermy::Enermy()
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mVisible = true;
	mAnimating = false;

	mHealth = 20; 

	// Tank
	mTank = new Texture("PNG/tanks/tankBlue.png");
	mTank->Parent(this);
	mTank->Pos(VEC2_ZERO);

	mBarrel = new Texture("PNG/tanks/barrelBeige.png");
	mBarrel->Parent(this);
	mBarrel->Pos(Vector2(0.0f, 0.0f));

	mHeadBarrel = new GameEntity();
	mHeadBarrel->Parent(mBarrel);
	mHeadBarrel->Pos(Vector2(0.0f, 50.0f));

	mDeathAnimation = new AnimatedTexture("PNG/Death/tankBeige.png", 0, 0, 100, 100, 4, 1.0f, AnimatedTexture::VERTICAL);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Pos(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::ONCE);


	// Health Bar
	std::string filename = "PNG/Health_Bars/health_";
	for (unsigned int i = 0; i < MAX_HEALTH; i++)
	{
		std::string file = filename + std::to_string(i) + ".png";
		mHealthBar[i] = new Texture(file);
	}

	for (unsigned int i = 0; i < MAX_HEALTH; i++)
	{
		mHealthBar[i]->Parent(this);
		mHealthBar[i]->Pos(Vector2(0.0f, -50.0f));
		mHealthBar[i]->Scale(Vector2(0.25f, 0.3f));
	}

	mRotationSpeed = 70.0f;

	mMoveSpeed = 200.0f;

	for (unsigned int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i] = new Bullet();
	}

	mCurrentState = AUTO;
}

Enermy::~Enermy()
{
	mTimer = NULL;
	mAudio = NULL;

	// Free Player
	delete mHeadBarrel;
	mHeadBarrel = NULL;

	delete mBarrel;
	mBarrel = NULL;

	delete mTank;
	mTank = NULL;

	delete mDeathAnimation;
	mDeathAnimation = NULL;

	// Freeing HealthBar 
	for (unsigned int i = 0; i < MAX_HEALTH; i++)
	{
		delete mHealthBar[i];
		mHealthBar[i] = NULL;
	}

	// Freeing Bullets
	for (unsigned int i = 0; i < MAX_BULLETS; i++)
	{
		delete mBullets[i];
		mBullets[i] = NULL;
	}
}


void Enermy::HandleStates()
{
	switch (mCurrentState)
	{
	case Enermy::AUTO:
		HandleAutoState();
		break;
	case Enermy::CHASE:
		HandleChaseState();
		break;
	case Enermy::DEAD:
		HandldeDeadState();
		break;
	default:
		break;
	}
}

void Enermy::HandleAutoState()
{

}

void Enermy::HandleChaseState()
{

}

void Enermy::HandldeDeadState()
{

}

Enermy::STATES Enermy::CurrentState()
{
	return mCurrentState;
}

void Enermy::Update()
{
	if (Active())
		HandleStates();
}

void Enermy::Render()
{
	if (mVisible)
	{
		if (mAnimating)
		{
			mDeathAnimation->Render();
		}
		else
		{
			mHealthBar[mHealth]->Render();
			mTank->Render();
			mBarrel->Render();
		}
	}
}

//Enermy::Enermy(Colors color) : GameObject(color)
//{
//	speed = rand() % 5 + 7;
//	std::cout << speed << '\n';
//	velocX = 0;
//	velocY = 0;
//
//	angle = 90.0;
//
//	desR.w = desR.h = 64;
//	desR.x = 385;
//	desR.y = 512;
//
//	status = Status::LEFT;
//}
//
//Enermy::~Enermy() {}
//
//void Enermy::CheckMap(const Map* data) 
//{
//	if (status == Status::LEFT)
//	{
//		int row, col;
//		row = (desR.x / 64) + 1;
//		col = desR.y / 64;
//		if (data->map[col][row] == 28) 
//		{
//			velocX = 1;
//		}
//		else if (data->map[col - 1][row - 1] == 23)
//		{
//			velocX = 0;
//			velocY = -1;
//		}
//
//	}
//}
//
//void Enermy::Update(const Map* data) 
//{
//	desR.x += (velocX * speed);
//	desR.y += (velocY * speed);
//}
//
//void Enermy::Draw()
//{
//	SDL_RenderCopyEx(GameManager::renderer, objTexture, NULL, &desR, angle, NULL, SDL_FLIP_NONE);
//}