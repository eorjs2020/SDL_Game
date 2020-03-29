#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(SDL_Renderer* renderer, const char* filename, int sizeX, int sizeY, float a_speed) : Sprite(renderer, filename, sizeX, sizeY)
{
	speed = a_speed;
}

void Bullet::update(float deltaTime)
{
	dst.y -= deltaTime * speed;
	lifeTime -= deltaTime;
	if (lifeTime <= 0)
	{
		markedForRemoval = true;
	}
}
