#include "PhysicEntity.h"

PhysicEntity::PhysicEntity()
{

}

PhysicEntity::~PhysicEntity()
{
	for (int i = 0; i < mColliders.size(); i++)
	{
		delete mColliders[i];
		mColliders[i] = nullptr;
	}
	mColliders.clear();
}

void PhysicEntity::AddCollider(Collider* collider, Vector2 localPos)
{
	collider->Parent(this);
	collider->Pos(localPos);
	mColliders.push_back(collider);
}

void PhysicEntity::Render()
{
	for (int i = 0; i < mColliders.size(); ++i)
	{
		mColliders[i]->Render();
	}
}