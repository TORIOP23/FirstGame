#include "BoxCollider.h"

BoxCollider::BoxCollider(Vector2 size)
	: Collider(ColliderType::BOX)
{
	AddVert(0, Vector2(-0.5f * size.x, -0.5f * size.y));
	AddVert(1, Vector2( 0.5f * size.x, -0.5f * size.y));
	AddVert(2, Vector2(-0.5f * size.x,  0.5f * size.y));
	AddVert(3, Vector2( 0.5f * size.x,  0.5f * size.y));

	if (DEBUG_COLLIDERS)
	{
		SetDebugTexture(new Texture("PNG/boxCollider.png"));
		mDebugTexture->Scale(size / 100.0f);
	}
}

BoxCollider::~BoxCollider()
{
	for (int i = 0; i < MAX_VERTS; i++)
	{
		delete mVerts[i];
		mVerts[i] = nullptr;
	}
}

void BoxCollider::AddVert(int index, Vector2 pos)
{
	mVerts[index] = new GameEntity(pos);
	mVerts[index]->Parent(this);
}
