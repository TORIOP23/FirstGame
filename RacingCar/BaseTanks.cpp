#include "BaseTanks.h"
#include "BoxCollider.h"
#include "PhysicManager.h"
#include <string>

BaseTanks::BaseTanks(bool player)
{
	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	//Map
	mMap = Map::Instance();

	mVisible = true; // false ??
	mAnimating = false;
	mWasHit = false;

	mColor = static_cast<PhysicEntity::Color>(rand() % PhysicEntity::MAX);

	if (player)
	{
		SetTankColor();
		SetBarrelColor();
	}
	else
	{
		SetTankColor(mColor);
		SetBarrelColor(mColor);
	}

	mDeathAnimation = new AnimatedTexture("PNG/Death/tankBeige.png", 0, 0, 100, 100, 4, 1.0f, AnimatedTexture::VERTICAL);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Pos(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::ONCE);

	// Health Bar
	mHealth = 20; // full = 20

	std::string filename = "PNG/Health_Bars/health_";
	for (unsigned int i = 0; i < MAX_HEALTH; i++)
	{
		std::string file = filename + std::to_string(i) + ".png";
		mHealthBar[i] = new Texture(file);
	}

	for (unsigned int i = 0; i < MAX_HEALTH; i++)
	{
		mHealthBar[i]->Parent(this);
		mHealthBar[i]->Pos(Vector2(0.0f, 50.0f));
		mHealthBar[i]->Scale(Vector2(0.25f, 0.3f));
	}

	// Bullet
	for (unsigned int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i] = new Bullet(player);
	}

	// Speed
	mRotationSpeed = 90.0f;
	mMoveSpeed = 300.0f;

	// Collider
	AddCollider(new BoxCollider(mTank->ScaleDimensions()));

	// Register Collision
	if (player)
		mId = PhysicManager::Instance()->RegisterEntity(this, PhysicManager::CollisionLayers::Friendly);
	else 
		mId = PhysicManager::Instance()->RegisterEntity(this, PhysicManager::CollisionLayers::Hostile);
}

BaseTanks::~BaseTanks()
{
	mTimer = nullptr;
	mAudio = nullptr;

	mMap = nullptr;

	// Free Player
	delete mHeadBarrel;
	mHeadBarrel = nullptr;

	delete mBarrel;
	mBarrel = nullptr;

	delete mTank;
	mTank = nullptr;

	delete mDeathAnimation;
	mDeathAnimation = nullptr;

	// Freeing HealthBar 
	for (unsigned int i = 0; i < MAX_HEALTH; i++)
	{
		delete mHealthBar[i];
		mHealthBar[i] = nullptr;
	}

	// Freeing Bullets
	for (unsigned int i = 0; i < MAX_BULLETS; i++)
	{
		delete mBullets[i];
		mBullets[i] = nullptr;
	}
}

void BaseTanks::SetTankColor(PhysicEntity::Color color)
{
	std::string path = "PNG/tanks/tank";
	switch (color)
	{
	case PhysicEntity::BEIGE:
		path += "Beige.png";
		break;
	case PhysicEntity::BLACK:
		path += "Black.png";
		break;
	case PhysicEntity::BLUE:
		path += "Blue.png";
		break;
	case PhysicEntity::GREEN:
		path += "Green.png";
		break;
	case PhysicEntity::RED:
		path += "Red.png";
		break;
	default:
		break;
	}

	delete mTank;
	mTank = new Texture(path);
	mTank->Parent(this);
	mTank->Pos(VEC2_ZERO);
}

void BaseTanks::SetBarrelColor(PhysicEntity::Color color)
{
	std::string path = "PNG/tanks/barrel";
	switch (color)
	{
	case PhysicEntity::BEIGE:
		path += "Beige.png";
		break;
	case PhysicEntity::BLACK:
		path += "Black.png";
		break;
	case PhysicEntity::BLUE:
		path += "Blue.png";
		break;
	case PhysicEntity::GREEN:
		path += "Green.png";
		break;
	case PhysicEntity::RED:
		path += "Red.png";
		break;
	}

	delete mBarrel;
	mBarrel = new Texture(path);
	mBarrel->Parent(this);
	mBarrel->Pos(Vector2(0.0f, 0.0f));

	delete mHeadBarrel;
	mHeadBarrel = new GameEntity();
	mHeadBarrel->Parent(mBarrel);
	mHeadBarrel->Pos(Vector2(0.0f, 50.0f));
}

void BaseTanks::Visible(bool visible)
{
	mVisible = visible;
}

bool BaseTanks::WasHit() const
{
	return mWasHit;
}

bool BaseTanks::IsAnimating() const
{
	return mAnimating;
}

int BaseTanks::Health() const
{
	return mHealth;
}

float BaseTanks::Speed() const
{
	return mMoveSpeed;
}