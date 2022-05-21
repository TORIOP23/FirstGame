#include "PhysicEntity.h"
#include "CircleCollider.h"
#include "PhysicsHelper.h"
#include "PhysicManager.h"

PhysicEntity::PhysicEntity()
{
	mBroadPhaseCollider = nullptr;

	mId = 0;

	mColor = BEIGE;
}

PhysicEntity::~PhysicEntity()
{
	for (int i = 0; i < mColliders.size(); i++)
	{
		delete mColliders[i];
		mColliders[i] = nullptr;
	}
	mColliders.clear();

	if (mBroadPhaseCollider)
	{
		delete mBroadPhaseCollider;
		mBroadPhaseCollider = nullptr;
	}

	if (mId != 0)
	{
		PhysicManager::Instance()->UnregisterEntity(mId);
	}
}

unsigned long PhysicEntity::GetId()
{
	return mId;
}

bool PhysicEntity::CheckCollision(PhysicEntity* other)
{
	if (IgnoreCollision() || other->IgnoreCollision())
		return false;

	return ColliderColliderCheck(mBroadPhaseCollider, other->mBroadPhaseCollider);
}

void PhysicEntity::Hit(PhysicEntity* other)
{

}

bool PhysicEntity::IgnoreCollision()
{
	return false;
}

void PhysicEntity::AddCollider(Collider* collider, Vector2 localPos)
{
	collider->Parent(this);
	collider->Pos(localPos);
	mColliders.push_back(collider);

	if (mColliders.size() > 1 || mColliders[0]->GetType() != Collider::ColliderType::CIRCLE)
	{
		float furthestDist = mColliders[0]->GetFurthestPoint().Magnitude();
		float dist = 0.0f;
		for (int i = 1; i < mColliders.size(); i++)
		{
			dist = mColliders[i]->GetFurthestPoint().Magnitude();
			if (dist > furthestDist)
			{
				furthestDist = dist;
			}
		}

		delete mBroadPhaseCollider;
		mBroadPhaseCollider = new CircleCollider(furthestDist, true);
		mBroadPhaseCollider->Parent(this);
		mBroadPhaseCollider->Pos(VEC2_ZERO);
	}
}

void PhysicEntity::Render()
{
	if (mBroadPhaseCollider)
		mBroadPhaseCollider->Render();

	for (int i = 0; i < mColliders.size(); ++i)
	{
		mColliders[i]->Render();
	}
}