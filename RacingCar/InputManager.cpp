// InputManager.cpp
// Handles all Input related functionality for keyboard and mouse.
#include <string.h>
#include <cstdio>

#include "InputManager.h"

//Initializing to NULL
InputManager* InputManager::sInstance = nullptr;

InputManager* InputManager::Instance() 
{
	//Create a new instance if no instance was created before
	if (sInstance == nullptr)
		sInstance = new InputManager();

	return sInstance;
}

void InputManager::Release() 
{
	delete sInstance;
	sInstance = nullptr;
}

InputManager::InputManager() 
{
	mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
	//Setting mPrevKeyboardState to be the same length as mKeyboardState
	mPrevKeyboardState = new Uint8[mKeyLength];
	//Copying the contents of mKeyboardState into mPrevKeyboardState so that it contains data on the first frame
	memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
}

InputManager::~InputManager() 
{
	//Clearing the previous keyboard state array
	delete[] mPrevKeyboardState;
	mPrevKeyboardState = nullptr;
}

bool InputManager::KeyDown(SDL_Scancode scanCode) 
{
	return (mKeyboardState[scanCode] != 0);
}

bool InputManager::KeyPressed(SDL_Scancode scanCode) 
{
	//returning true of the key was not pressed in the previous keyboard state but is pressed in the current one
	return (mPrevKeyboardState[scanCode]) == 0 && (mKeyboardState[scanCode] != 0);
}

bool InputManager::KeyReleased(SDL_Scancode scanCode) 
{
	//returning true of the key was pressed in the previous keyboard state but is not pressed in the current one
	return (mPrevKeyboardState[scanCode] != 0) && (mKeyboardState[scanCode] == 0);
}

Vector2 InputManager::MousePos() const
{
	//Converting the mouse position into a Vector2 for ease of use since all entities use Vector2
	return Vector2(static_cast<float>(mMouseXPos), static_cast<float>(mMouseYPos));
}

bool InputManager::MouseButtonDown(MOUSE_BUTTON button) 
{
	//mask to be using for bit wise operations
	Uint32 mask = 0;

	switch (button) 
	{
	case LEFT:
		mask = SDL_BUTTON_LMASK;
		break;

	case RIGHT:
		mask = SDL_BUTTON_RMASK;
		break;

	case MIDDLE:
		mask = SDL_BUTTON_MMASK;
		break;

	case BACK:
		mask = SDL_BUTTON_X1MASK;
		break;

	case FORWARD:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	//return true if the mask exists in the current mouse statem, bitwise & 
	return ((mMouseState & mask) != 0);
}

bool InputManager::MouseButtonPressed(MOUSE_BUTTON button) 
{
	//mask to be using for bit wise operations
	Uint32 mask = 0;

	switch (button) 
	{
	case LEFT:
		mask = SDL_BUTTON_LMASK;
		break;

	case RIGHT:
		mask = SDL_BUTTON_RMASK;
		break;

	case MIDDLE:
		mask = SDL_BUTTON_MMASK;
		break;

	case BACK:
		mask = SDL_BUTTON_X1MASK;
		break;

	case FORWARD:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	//return true if the mask does not exist in the previous mouse state, but exists in the current one
	return ((mPrevMouseState & mask) == 0) && ((mMouseState & mask) != 0);
}

bool InputManager::MouseButtonReleased(MOUSE_BUTTON button) 
{
	Uint32 mask = 0;

	switch (button) 
	{
	case LEFT:
		mask = SDL_BUTTON_LMASK;
		break;

	case RIGHT:
		mask = SDL_BUTTON_RMASK;
		break;

	case MIDDLE:
		mask = SDL_BUTTON_MMASK;
		break;

	case BACK:
		mask = SDL_BUTTON_X1MASK;
		break;

	case FORWARD:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	//return true if the mask exists in the previous mouse state, but does not exist in the current one
	return ((mPrevMouseState & mask) != 0) && ((mMouseState & mask) == 0);
}

void InputManager::Update() 
{
	//Updating the mouse state to get the key states of the current frame
	mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);
}

void InputManager::UpdatePrevInput() 
{
	//Copying the keyboard state into the previous keyboard state array at the end of the frame
	memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
	//Setting the previous mouse state as the current mouse state at the end of the frame
	mPrevMouseState = mMouseState;
}
