#include "Player.h"
#include "TextureManager.h"
#include "Collision.h"
#include <cmath>

Player::Player(Colors color) : GameObject(color)
{
	desR.x = 385;
	desR.y = 389;
	desR.w = desR.h = 64;
	speed = 5;
	angle = 90.0;
	velocX = 0;
	velocY = 0;
}

Player::~Player()
{
}

void Player::HandleInput()
{
	if (GameManager::event.type == SDL_KEYDOWN)
	{
		switch (GameManager::event.key.keysym.sym)
		{
		case SDLK_w:
			std::cout << "W\n";
			velocX = sin(angle * M_PI / 180);
			velocY = -cos(angle * M_PI / 180);
			break;
		case SDLK_a:
			std::cout << "A\n";
			angle -= 30;
			break;
		case SDLK_d:
			std::cout << "D\n";
			angle += 30;
			break;
		case SDLK_s:
			std::cout << "S\n";
			velocX = -sin(angle * M_PI / 180);
			velocY = +cos(angle * M_PI / 180);
			break;
		default:
			break;
		}
	}
	if (GameManager::event.type == SDL_KEYUP)
	{
		switch (GameManager::event.key.keysym.sym)
		{
		case SDLK_w:
			velocY = 0;
			velocX = 0;
			break;
		case SDLK_a:
			break;
		case SDLK_d:
			break;
		case SDLK_s:
			velocX = 0;
			velocY = 0;
			break;
		case SDLK_ESCAPE:
			GameManager::isRunning = false;
			break;
		default:
			break;
		}
	}
}

void Player::Update(const Map* data)
{
	if (angle > 360) angle -= 360;
	else if (angle < 0) angle += 360;

	SDL_Rect preR = desR;
	desR.x += static_cast<int>(velocX * speed);
	desR.y += static_cast<int>(velocY * speed);

	// check cham bien cua so
	if (desR.x >= (GameManager::SCREEN_WIDTH - 64)) desR.x = GameManager::SCREEN_WIDTH - 64 - 10;
	else if (desR.x <= 0) desR.x = 0 + 10;

	if (desR.y >= (GameManager::SCREEN_HEIGHT - 64)) desR.y = GameManager::SCREEN_HEIGHT - 64 - 10;
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
	SDL_RenderCopyEx(GameManager::renderer, objTexture, NULL, &desR, angle, NULL, SDL_FLIP_NONE);
}

