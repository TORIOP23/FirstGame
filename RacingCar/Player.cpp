#include "Player.h"
#include "TextureManager.h"
#include "Collision.h"

Player::Player(Colors color) : GameObject(color)
{
	desR.x = 385;
	desR.y = 389;
	desR.w = desR.h = 64;
	speed = 10;
	angle = 90.0;
	velocX = 0;
	velocY = 0;
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
			angle = 0;
			velocY = -1;
			break;
		case SDLK_a:
			angle = 270;
			velocX = -1;
			break;
		case SDLK_d:
			angle = 90;
			velocX = 1;
			break;
		case SDLK_s:
			angle = 180;
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

void Player::Update(const Map* data)
{
	SDL_Rect preR = desR;
	desR.x += (velocX * speed);
	desR.y += (velocY * speed);

	// check cham bien cua so
	if (desR.x >= (Game::SCREEN_WIDTH - 64)) desR.x = Game::SCREEN_WIDTH - 64 - 10;
	else if (desR.x <= 0) desR.x = 0 + 10;

	if (desR.y >= (Game::SCREEN_HEIGHT - 64)) desR.y = Game::SCREEN_HEIGHT - 64 - 10;
	else if (desR.y <= 0) desR.y = 0 + 10;

	// check di tren duong
	int startX = desR.x / 64;
	int endX = desR.x / 64 + 1;

	int startY = desR.y / 64;
	int endY = desR.y / 64 + 1;

	for (int row = startY; row <= endY; ++row) {
		for (int col = startX; col <= endX; ++col) {
			if (data->map[row][col] == 0) {
				SDL_Rect mapR = { col * 64, row * 64, 64, 64 };
				if (Collision::AABB(mapR, desR))
				{
					//std::cout << "k o duong" << " mapR: " << mapR.x << " " << mapR.y << " desR: " << desR.x << " " << desR.y << '\n';
					desR = preR;
				}
			}
		}
	}

}

void Player::Draw()
{
	SDL_RenderCopyEx(Game::renderer, objTexture, NULL, &desR, angle, NULL, SDL_FLIP_NONE);
}

