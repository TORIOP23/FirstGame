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

	virtual void Render();

protected:

	void SetDebugTexture(Texture* texture);
};

