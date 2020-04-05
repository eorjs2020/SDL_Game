#pragma once
#include "Sprite.h"
class EnemyBullet :
	public Sprite
{
public:
	EnemyBullet();
	EnemyBullet(SDL_Renderer* renderer, const char* filename, int sizeX, int sizeY, float a_speed);

	float speed = -300;
	float lifeTime = 5;

	void update(float deltaTime) override;
};