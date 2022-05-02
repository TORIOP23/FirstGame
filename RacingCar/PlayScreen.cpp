#include "PlayScreen.h"

PlayScreen::PlayScreen()
{
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();


}

PlayScreen::~PlayScreen()
{
	mTimer = NULL;
	mInput = NULL;
}

void PlayScreen::Update()
{

}

void PlayScreen::Render()
{

}