// singleton
// contain pointers to all physics entites

#pragma once

#include "PhysicEntity.h"
#include <bitset>


class PhysicManager
{
public:
	enum class CollisionLayers 
	{
		Friendly = 0,  // Player will be
		FriendlyProjectiles,
		Hostile,     // Enermy will be
		HostileProjectiles,
		//------------------
		MaxLayers
	};

	enum class CollisionFlags
	{
		None				= 0x00,
		Friendly			= 0x01,
		FriendlyProjectiles = 0x02,
		Hostile				= 0x04,
		HostileProjectiles	= 0x08
	};

private:
	static PhysicManager* sInstance;

	// each layer will have its own vector, have all entities that belong to that layer
	std::vector<PhysicEntity*> mCollisionLayers[static_cast<unsigned int>(CollisionLayers::MaxLayers)];
	
	// 
	std::bitset<static_cast<unsigned int>(CollisionLayers::MaxLayers)> mLayerMasks[static_cast<unsigned int>(CollisionLayers::MaxLayers)];

	// Assign a unique ID to each physics entity that we register with the manager
	unsigned long mLastId;

public:

	static PhysicManager* Instance();
	static void Release();

	// Take in these flag and then set them into mLayerMask
	void SetLayerCollisionMask(CollisionLayers layer, CollisionFlags flags);

	// Find the index of the layer we're passing in
	unsigned long RegisterEntity(PhysicEntity* entity, CollisionLayers layer);
	
	//
	void UnregisterEntity(unsigned long id);

	// handle all our detection
	void Update();

private:

	PhysicManager();
	~PhysicManager();
};

inline PhysicManager::CollisionFlags operator|(PhysicManager::CollisionFlags a, PhysicManager::CollisionFlags b)
{
	return static_cast<PhysicManager::CollisionFlags>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b));
}

inline PhysicManager::CollisionFlags operator&(PhysicManager::CollisionFlags a, PhysicManager::CollisionFlags b)
{
	return static_cast<PhysicManager::CollisionFlags>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b));
}


