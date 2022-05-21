#pragma once

#include "Texture.h"

class Collider : public GameEntity
{
public:

	enum class ColliderType { BOX, CIRCLE };

protected:

	ColliderType mType;

	static const bool DEBUG_COLLIDERS = true;

	Texture* mDebugTexture;

public:

	Collider(ColliderType type);
	virtual ~Collider();

	// because the base collider class doesn't know what a furthest point is 
	virtual Vector2 GetFurthestPoint() = 0;

	virtual void Render();

	ColliderType GetType() const;

protected:
	// Derive class will use
	void SetDebugTexture(Texture* texture);
};

