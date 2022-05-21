// AnimatedTexture.cpp
// Extends the Texture class' functionality to handle animations
// Uses the Texture class' spritesheet constructor

#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir)
	: Texture(filename, x, y, w, h) 
{
	mTimer = Timer::Instance();

	mStartX = x;
	mStartY = y;

	mFrameCount = frameCount;
	mAnimationSpeed = animationSpeed;
	mTimePerFrame = mAnimationSpeed / mFrameCount;
	mAnimationTimer = 0.0f;

	mAnimationDirection = animationDir;

	mAnimationDone = false;

	mWrapMode = ONCE;
}

AnimatedTexture::~AnimatedTexture() 
{
	mTimer = nullptr;
}

void AnimatedTexture::WrapMode(WRAP_MODE mode) 
{
	mWrapMode = mode;
}

void AnimatedTexture::ResetAnimation()
{
	mAnimationTimer = 0.0f;
	mAnimationDone = false;
}

bool AnimatedTexture::IsAnimating() const
{
	return !mAnimationDone;
}

void AnimatedTexture::Update() 
{
	if(!mAnimationDone)
	{
		mAnimationTimer += mTimer->DeltaTime();

		if(mAnimationTimer >= mAnimationSpeed) 
		{
			//Only loop if the wrap mode is loop
			if(mWrapMode == LOOP) 
			{
				mAnimationTimer -= mAnimationSpeed;

			} else 
			{
				mAnimationDone = true;
				// stop at last animation then say that the animation is done
				mAnimationTimer = mAnimationSpeed - mTimePerFrame;
			}
		}

		if(mAnimationDirection == HORIZONTAL) 
		{
			mClipRect.x = mStartX + static_cast<int>(mAnimationTimer / mTimePerFrame) * mWidth;

		} else 
		{
			mClipRect.y = mStartY + static_cast<int>(mAnimationTimer / mTimePerFrame) * mHeight;
		}
	}
}