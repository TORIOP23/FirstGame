#pragma once

#include <vector>
#include "Collider.h"


class PhysicEntity : public GameEntity 
{
protected:

	// because we can't have a single shape to describe our entire objects 
	std::vector<Collider*> mColliders;

public:
	PhysicEntity();
	virtual ~PhysicEntity();

	virtual void Render();

protected:
	void AddCollider(Collider* collider, Vector2 localPos = VEC2_ZERO);
};

