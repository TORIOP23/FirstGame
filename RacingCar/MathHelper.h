//-------------------------------------------------------------------------------------------------------------------//
// MathHelper.h                                                                                                      //
// Contains all the math functions that will be needed in the framework.                                             //
//-------------------------------------------------------------------------------------------------------------------//

#pragma once
#include <cmath>

#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f
//--------------------------------------------------------------------------------------------------
// Vector2 structs consist of x and y values discribing a 2D vector,                                
// along with vector magnitude calculations, normalization, and operator overloading of += and -=   
//--------------------------------------------------------------------------------------------------
struct Vector2 
{
	float x;
	float y;

	Vector2(float _x = 0.0f, float _y = 0.0f)
		: x(_x), y(_y) {}
	//--------------------------------------------------------------------------------------------
	//Calculates the square of the magnitude (preferably used instead of Magnitude if possible) 
	//We can test things much faster   
	//--------------------------------------------------------------------------------------------
	float MagnitudeSqr() const
	{
		return x * x + y * y;
	}

	//-------------------------------------------
	//Calculates the magnitude of the vector     
	//-------------------------------------------
	float Magnitude() const
	{
		return static_cast<float>(sqrt(x * x + y * y));
	}

	//----------------------------------------------------------------------------------------
	//Returns a directional Vector2 with the same direction as the Vector2 but of length 1    
	// (Does not change the x and y values of the original vector)                                       
	//----------------------------------------------------------------------------------------
	Vector2 Normalized()  const 
	{
		float mag = Magnitude();
		return Vector2(x / mag, y / mag);
	}

	//The return value of the function is a variable
	Vector2& operator +=(const Vector2& rhs) 
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	// rhs : right hand side 
	Vector2& operator -=(const Vector2& rhs) 
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}

	Vector2 operator -() const
	{
		return Vector2(-x, -y);
	}
};

inline Vector2 operator +(const Vector2& lhs, const Vector2& rhs) 
{
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline Vector2 operator -(const Vector2& lhs, const Vector2& rhs) 
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline Vector2 operator *(const Vector2& lhs, const float& rhs) 
{
	return Vector2(lhs.x * rhs, lhs.y * rhs);
}

//----------------------------------------------------------------
//Rotates the given vector by the given angle around the origin (clockwise)
//(Does not change the original vector)    
// https://matthew-brett.github.io/teaching/rotation_2d.html                         
//----------------------------------------------------------------
inline Vector2 RotateVector(Vector2& vec, float angle) 
{
	//converting the angle to radians to be used in sin and cos functions
	float radAngle = static_cast<float>(angle * DEG_TO_RAD);

	return Vector2(static_cast<float>(vec.x * cos(radAngle) - vec.y * sin(radAngle)), static_cast<float>(vec.x * sin(radAngle) + vec.y * cos(radAngle)));
}

inline Vector2 Lerp(Vector2& start, Vector2& end, float time)
{
	if (time <= 0.0f)
		return start;
	if (time >= 1.0f)
		return end;
	Vector2 dir = (end - start).Normalized();
	float mag = (end - start).Magnitude();

	return start + dir * mag * time;
}

inline float AngleBetweenVector(const Vector2& lhs, const Vector2& rhs)
{
	float cos = (lhs.x * rhs.x + lhs.y * rhs.y) / (lhs.Magnitude() * rhs.Magnitude());
	return static_cast<float>(acos(cos) / (DEG_TO_RAD));
}

const Vector2 VEC2_ZERO = { 0.0f, 0.0f };
const Vector2 VEC2_ONE = { 1.0f, 1.0f };
const Vector2 VEC2_UP = { 0.0f, - 1.0f };
const Vector2 VEC2_DOWN = { 0.0f, 1.0f };
const Vector2 VEC2_RIGHT = { 1.0f, 0.0f };