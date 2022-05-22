#pragma once

#include <vector>
#include "Collider.h"


class PhysicEntity : public GameEntity 
{
public:
	enum Color {
		BEIGE = 0, BLACK, BLUE, GREEN, RED, MAX
	};

protected:

	// Id = 0 <=> Unregister
	unsigned long mId;

	// because we can't have a single shape to describe our entire objects 
	std::vector<Collider*> mColliders;

	// Broad Phase Collider
	Collider* mBroadPhaseCollider;

	//Color
	Color mColor;

public:

	PhysicEntity();
	virtual ~PhysicEntity();

	unsigned long GetId();

	bool CheckCollision(PhysicEntity* other);

	virtual void Hit(PhysicEntity* other);

	virtual void PlayerHitEnemy(PhysicEntity* other);

	virtual void Render();

protected:
	
	virtual bool IgnoreCollision();

	void AddCollider(Collider* collider, Vector2 localPos = VEC2_ZERO);
};

