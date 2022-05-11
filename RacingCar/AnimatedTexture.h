// AnimatedTexture.h                                               //
// Extends the Texture class' functionality to handle animations   //
// Use the Texture class' spritesheet constructor                  //
#pragma once

#include "Timer.h"
#include "Texture.h"


class AnimatedTexture : public Texture {

public:
	//WRAP_MODE enum - wrap mode used by the animation
	enum WRAP_MODE { ONCE = 0, LOOP = 1 };

	//ANIM_DIR enum - The way the animation sprites are arranged in the spritesheet
	enum ANIM_DIR { HORIZONTAL = 0, VERTICAL = 1 };

private:

	//Used to get the deltatime to update the animation
	Timer* mTimer;

	//the first frame's starting pixel's X values on the spritesheet
	int mStartX;
	//the first frame's starting pixel's Y values on the spritesheet
	int mStartY;

	//Used to keep track of how long current animation frame has been on screen
	float mAnimationTimer;
	//Used to determine the speed of the animation, is total amount of time for the entire animation
	float mAnimationSpeed;
	//Stores how long each animation frame should be on screen
	float mTimePerFrame;

	//Stores the number of animation frames in the animation
	int mFrameCount;

	//Stores the wrap mode
	WRAP_MODE mWrapMode;
	//Stores the animation direction
	ANIM_DIR mAnimationDirection;

	//Is set to true only if the wrap mode is once and the last frame of the animation is reached
	bool mAnimationDone;

public:

	//Loads a texture from from file (relative to the exe path)
	//Supports spritesheets
	//x : Start X
	//y : Start Y
	//w : The width of 1 frame
	//h : The height of 1 frame
	//frameCount : The number of frames in the animation
	//animationSpeed : How long it takes to run the animation in seconds
	//animationDirection : How the animation sprites are arranges in the spritesheet
	AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir);
	
	~AnimatedTexture();

	//Sets the wrap mode of the animation
	void WrapMode(WRAP_MODE mode);

	void ResetAnimation();

	bool IsAnimating();

	//Used to update the animation frames and loop the animation if needed
	void Update();
};