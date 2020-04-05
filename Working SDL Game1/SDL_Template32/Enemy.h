#pragma once
#include "Sprite.h"
class Enemy :
	public Sprite
{
public:
	int hitPoints;

	Enemy(SDL_Renderer* renderer, const char* filename, int sizeX, int sizeY, int hitPoints);
	~Enemy();
	void update(float deltaTime) override;
	void onCollisionWith(const Sprite& other)override;
};

