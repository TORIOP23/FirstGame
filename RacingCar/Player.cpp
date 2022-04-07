#include "Player.h"
#include "TextureManager.h"

Player::Player(Colors color) : GameObject(color)
{
	x_pos = 450;
	y_pos = 600;
	speed = 10;
	angle = 0.0;
}

Player::~Player()
{
}

void Player::HandleInput()
{
	if (Game::event.type == SDL_KEYDOWN)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_w:
			if (angle != 0) {
				if (angle > 0 && angle <= 180)
					angle -= INCREASE_ANGLE;
				else angle += INCREASE_ANGLE;
			}
			velocY = -1;
			break;
		case SDLK_a:
			if (angle != 270) {
				if (angle >= 90 && angle < 270)
					angle += INCREASE_ANGLE;
				else angle -= INCREASE_ANGLE;
			}
			velocX = -1;
			break;
		case SDLK_d:
			if (angle != 90) {
				if (angle > 90 && angle <= 270)
					angle -= INCREASE_ANGLE;
				else angle += INCREASE_ANGLE;
			}
			velocX = 1;
			break;
		case SDLK_s:
			if (angle != 180) {
				if (angle >= 0 && angle < 180)
					angle += INCREASE_ANGLE;
				else angle -= INCREASE_ANGLE;
			}
			velocY = 1;
			break;
		default:
			break;
		}
	}
	if (Game::event.type == SDL_KEYUP)
	{
		switch (Game::event.key.keysym.sym)
		{
		case SDLK_w:
			velocY = 0;
			break;
		case SDLK_a:
			velocX = 0;
			break;
		case SDLK_d:
			velocX = 0;
			break;
		case SDLK_s:
			velocY = 0;
			break;
		case SDLK_ESCAPE:
			Game::isRunning = false;
			break;
		default:
			break;
		}
	}
}

void Player::Update()
{
	if (angle >= 360) angle = 0;
	else if (angle < 0) angle += 360;

	x_pos += (velocX * speed);
	y_pos += (velocY * speed);

	if (x_pos >= (1600 - 64)) x_pos = 1600 - 64;
	else if (x_pos <= 0) x_pos = 0;
	

	if (y_pos >= (960 - 64)) y_pos = 960 - 64;
	else if (y_pos <= 0) y_pos = 0;

}

void Player::Draw()
{
	SDL_Rect desR = { x_pos, y_pos, 64, 64 };
	SDL_RenderCopyEx(Game::renderer, objTexture, NULL, &desR, angle, NULL, SDL_FLIP_NONE);
}

