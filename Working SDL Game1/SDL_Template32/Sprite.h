#pragma once
#include<SDL_image.h>
#include "SpriteTags.h"

class SpriteManager;
int distanceSq(int x1, int y1, int x2, int y2);

class Sprite
{
protected:
	SDL_Renderer* renderer;
	SDL_Texture* pSpriteTex = nullptr;
	SDL_Rect src;

public:
	SpriteManager* spriteManager;
	SDL_Rect dst;
	

	SpriteTag tag = SpriteTag::NONE;
	

	float velX = 0;
	float velY = 0;

	bool markedForRemoval = false;
	int frameCount;
	int frameWidth;
	int currentFrame;
	bool loopAnimation = true;
	bool playAnimation = true;
	bool destroyOnAnimationComplete = false;

	Sprite();
	Sprite(SDL_Renderer* renderer, const char* filename, int sizeX, int sizeY, int num_frames = 1);
	
	~Sprite();

	void setPosition(int x, int y);
	void setSize(int x, int y);
	void draw();
	virtual void update(float deltaTime);
	void updateAnimation();
	bool isCollidingWith(const Sprite &other);
	bool isCollidingCircular(const Sprite& other);
	virtual void onCollisionWith(const Sprite& other);
	void cleanup();
};

