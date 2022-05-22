#pragma once

#include "CircleCollider.h"
#include "BoxCollider.h"
#include "MathHelper.h"

inline bool PointInPolygon(Vector2* verts, int vertCount, const Vector2& point)
{
	bool retVal = false;

	for (int i = 0, j = vertCount - 1; i < vertCount; j = i++) // j = i; i++
	{
		// same side
		if ((verts[i].y >= point.y) != (verts[j].y >= point.y))
		{
			Vector2 vec1 = (verts[i] - verts[j]).Normalized();
			Vector2 proj = verts[j] + vec1 * Dot(point - verts[j], vec1);

			// because we draw line to the right of x 
			if (proj.x > point.x)
			{
				retVal = !retVal;
			}
		}
	}

	return retVal;
}

inline float PointToLineDistance(const Vector2& lineStart, const Vector2& lineEnd, const Vector2& point)
{
	Vector2 slope = lineEnd - lineStart;

	// Get projection, have clamp because if projected vector lies after the start
	float param = Clamp(Dot(point - lineStart, slope) / slope.MagnitudeSqr(), 0.0f, 1.0f);

	Vector2 nearestPoint = lineStart + slope * param;

	return (point - nearestPoint).Magnitude();
}

inline bool CircleCircleCollision(CircleCollider* c1, CircleCollider* c2)
{
	return (c1->Pos() - c2->Pos()).Magnitude() < (c1->GetRadius() + c2->GetRadius());
}

inline bool BoxCircleCollision(BoxCollider* box, CircleCollider* circle)
{
	Vector2 quad[4];
	quad[0] = box->GetVertexPos(0);
	quad[1] = box->GetVertexPos(1);
	quad[2] = box->GetVertexPos(3); // flip 3 <-> 2
	quad[3] = box->GetVertexPos(2);

	float radius = circle->GetRadius();
	Vector2 circlePos = circle->Pos();
	
	// Box inside circle
	for (int i = 0; i < 4; i++)
	{
		if ((quad[i] - circlePos).Magnitude() < radius)
		{
			return true;
		}
	}


	// notice order vertex
	if (PointToLineDistance(box->GetVertexPos(0), box->GetVertexPos(1), circlePos) < radius ||
		PointToLineDistance(box->GetVertexPos(0), box->GetVertexPos(2), circlePos) < radius || 
		PointToLineDistance(box->GetVertexPos(2), box->GetVertexPos(3), circlePos) < radius || 
		PointToLineDistance(box->GetVertexPos(3), box->GetVertexPos(1), circlePos) < radius )
	{
		return true;
	}

	// Check circle inside box, like circle with radius = 0.0f

	if (PointInPolygon(quad, 4, circlePos))
	{
		return true;
	}

	return false;
}


// SAT, must convex polygon
inline bool BoxBoxCollision(BoxCollider* b1, BoxCollider* b2)
{
	Vector2 projAxis[4];

	projAxis[0] = (b1->GetVertexPos(0) - b1->GetVertexPos(1)).Normalized();
	projAxis[1] = (b1->GetVertexPos(0) - b1->GetVertexPos(2)).Normalized();

	projAxis[2] = (b2->GetVertexPos(0) - b2->GetVertexPos(1)).Normalized();
	projAxis[3] = (b2->GetVertexPos(0) - b2->GetVertexPos(2)).Normalized();

	float b1Min = 0.0f, b1Max = 0.0f;
	float b2Min = 0.0f, b2Max = 0.0f;
	float proj1 = 0.0f, proj2 = 0.0f; // point

	for (int i = 0; i < 4; i++) // axis
	{	
		for (int j = 0; j < 4; j++) // verts
		{	
			proj1 = Dot(b1->GetVertexPos(j), projAxis[i]); // projected 4 verts to 4 axis
			proj2 = Dot(b2->GetVertexPos(j), projAxis[i]);

			if (j == 0)
			{
				b1Min = b1Max = proj1;
				b2Min = b2Max = proj2;
			} 
			else
			{
				if (proj1 < b1Min)
					b1Min = proj1;
				if (proj1 > b1Max)
					b1Max = proj1;

				if (proj2 < b2Min)
					b2Min = proj2;
				if (proj2 > b2Max)
					b2Max = proj2;
			}
		}

		float halfDis1 = (b1Max - b1Min) * 0.5f;
		float midPoint1 = b1Min + halfDis1;

		float halfDis2 = (b2Max - b2Min) * 0.5f;
		float midPoint2 = b2Min + halfDis2;

		// like a circle collision
		if (abs(midPoint1 - midPoint2) > (halfDis1 + halfDis2))
		{
			return false;
		}
	}

	return true;
}

inline bool ColliderColliderCheck(Collider* c1, Collider* c2)
{
	if (c1->GetType() == Collider::ColliderType::CIRCLE && c2->GetType() == Collider::ColliderType::CIRCLE)
	{
		return CircleCircleCollision(static_cast<CircleCollider*>(c1), static_cast<CircleCollider*>(c2));
	}
	else if (c1->GetType() == Collider::ColliderType::BOX && c2->GetType() == Collider::ColliderType::CIRCLE)
	{
		return BoxCircleCollision(static_cast<BoxCollider*>(c1), static_cast<CircleCollider*>(c2));
	}
	else if (c2->GetType() == Collider::ColliderType::BOX && c1->GetType() == Collider::ColliderType::CIRCLE)
	{
		return BoxCircleCollision(static_cast<BoxCollider*>(c2), static_cast<CircleCollider*>(c1));
	}
	else if (c1->GetType() == Collider::ColliderType::BOX && c2->GetType() == Collider::ColliderType::BOX)
	{
		return BoxBoxCollision(static_cast<BoxCollider*>(c1), static_cast<BoxCollider*>(c2));
	}
	else
		return false;
}