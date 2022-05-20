#include "Timer.h"

//Initializing sInstance to NULL
Timer* Timer::sInstance = nullptr;

Timer* Timer::Instance() 
{
	//Create a new instance of Timer if no instance was created before
	if (sInstance == nullptr)
		sInstance = new Timer();
	return sInstance;
}

void Timer::Release() 
{
	delete sInstance;
	sInstance = nullptr;
}

Timer::Timer() 
{
	//Using Reset to initialize all the values beside mTimeScale
	Reset();
	mTimeScale = 1.0f;
	mElapsedTicks = 0;
	mDeltaTime = 0.0f;
}

Timer::~Timer()
{}

void Timer::Reset() 
{
	mStartTicks = SDL_GetTicks();
}

float Timer::DeltaTime() 
{
	return mDeltaTime;
}

void Timer::TimeScale(float t) 
{
	mTimeScale = t;
}

float Timer::TimeScale() 
{
	return mTimeScale;
}

void Timer::Update() 
{
	mElapsedTicks = SDL_GetTicks() - mStartTicks;
	//Converting milliseconds to seconds
	mDeltaTime = mElapsedTicks * 0.001f;
}