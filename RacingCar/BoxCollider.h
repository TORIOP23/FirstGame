#pragma once

#include "Collider.h"

class BoxCollider : public Collider
{
private:
	// vertice
	static const int MAX_VERTS = 4;

	GameEntity* mVerts[MAX_VERTS];

public:

	BoxCollider(Vector2 size);
	~BoxCollider();

private:

	void AddVert(int index, Vector2 pos);
};

