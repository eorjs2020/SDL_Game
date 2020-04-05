#include "Enemy.h"
#include "SpriteManager.h"
#include "EnemyBullet.h"
#include <iostream>
#include "Game.h"

Enemy::Enemy(SDL_Renderer* renderer, const char* filename, int sizeX, int sizeY, int hp) : Sprite(renderer, filename, sizeX, sizeY)
{
	hitPoints = hp;
	tag = SpriteTag::OBSTACLE;
}
 
Enemy::~Enemy()
{
}

void Enemy::update(float deltaTime)
{
	
}

void Enemy::onCollisionWith(const Sprite& other)
{
	
	if (other.tag == SpriteTag::PROJECTILE)
	{
		hitPoints -= 10;
	}
	if (hitPoints <= 0 && !markedForRemoval)
	{
		Sprite* explosion = new Sprite(renderer, "Assets/explosion_01.png", dst.w, dst.h, 6);
		explosion->dst.x = dst.x;
		explosion->dst.y = dst.y;
		explosion->destroyOnAnimationComplete = true;
		spriteManager->add(explosion);
		markedForRemoval = true;
	}
}

void Enemy::enemyTryShoot()
{
	EnemyBullet* b = new EnemyBullet(renderer, "Assets/Can_1.png", 32, 32, -500);
	b->dst.x = dst.x + dst.w / 2;
	b->dst.y = dst.y;

	spriteManager->add(b);
	shootTimer = shootInverval;
}
