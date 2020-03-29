#pragma once
#include "Sprite.h"

class Ship :
	public Sprite
{
public:
	Ship(SDL_Renderer* renderer, const char* filename, int sizeX, int sizeY, int num_frames = 1);

	~Ship();

	void update(float deltaTime)override;
	void tryShoot();
	float shootInverval = 0.1;
	float shootTimer = 0;

};

