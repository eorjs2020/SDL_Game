#include "EnemyBullet.h"
#include "SpriteManager.h"
EnemyBullet::EnemyBullet()
{
}

EnemyBullet::EnemyBullet(SDL_Renderer* renderer, const char* filename, int sizeX, int sizeY, float a_speed) : Sprite(renderer, filename, sizeX, sizeY)
{
	speed = a_speed;
	tag = SpriteTag::ENEMY;
}

void EnemyBullet::update(float deltaTime)
{
	dst.y -= deltaTime * speed;
	lifeTime -= deltaTime;

	
}