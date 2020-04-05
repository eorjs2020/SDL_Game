#include "Ship.h"
#include <iostream>
#include "SpriteManager.h"
#include "Bullet.h"


void Ship::tryShoot()
{
	if (shootTimer <= 0)
	{
		std::cout << "pew" << std::endl;
		Bullet * b = new Bullet(renderer, "Assets/fireball.png", 32 , 32, 500);
		b->dst.x = dst.x + dst.w/2;
		b->dst.y = dst.y;

  		spriteManager->add(b);
		shootTimer = shootInverval;
	}
}

void Ship::update(float deltaTime)
{
	shootTimer -= deltaTime;
	if (shootTimer < 0) shootTimer = 0;
}

Ship::Ship(SDL_Renderer* renderer, const char* filename, int sizeX, int sizeY, int num_frames) :Sprite(renderer, filename, sizeX, sizeY, num_frames)
{
}

Ship::~Ship()
{
}
