#include "Sprite.h"

Sprite::Sprite()
{
}

Sprite::Sprite(SDL_Renderer* a_renderer, const char* filename, int sizeX, int sizeY, int num_frames)
{
	renderer = a_renderer;
	pSpriteTex = IMG_LoadTexture(renderer, filename);

	SDL_QueryTexture(pSpriteTex, NULL, NULL, &src.w, &src.h);
	


	src.x = 0;
	src.y = 0;
	src.w /= num_frames;
	
	

	dst.x = 0;
	dst.y = 0;
	dst.w = sizeX;
	dst.h = sizeY;

	frameCount = num_frames;
	currentFrame = 0;
}

Sprite::~Sprite()
{
}

void Sprite::cleanup()
{
	SDL_DestroyTexture(pSpriteTex);
}

void Sprite::setPosition(int x, int y)
{
	dst.x = x;
	dst.y = y;
}

void Sprite::setSize(int x, int y)
{
	dst.w = x;
	dst.h = y;
}

void Sprite::draw()
{
	SDL_RenderCopy(renderer, pSpriteTex, &src, &dst);
}


void Sprite::update(float deltaTime)
{
}

void Sprite::updateAnimation()
{
	if (playAnimation)
	{
		int xPos = currentFrame * src.w;
		src.x = xPos;

		currentFrame++;

		if (currentFrame >= frameCount && loopAnimation)
		{
			currentFrame = 0;
		}
	}
}

bool Sprite::isCollidingWith(const Sprite &other)
{
	// check if our xMin is less than other's xMax and our xMax is greater than other's xMin
	int otherXMin = other.dst.x;
	int ourXMin = dst.x;

	int otherXMax = other.dst.x + other.dst.w;
	int ourXMax = dst.x + dst.w;

	bool overlapX = ourXMin < otherXMax && ourXMax > otherXMin;

	int otherYMin = other.dst.y;
	int ourYMin = dst.y;

	int otherYMax = other.dst.y + other.dst.h;
	int ourYMax = dst.y + dst.h;
	
	bool overlapY = ourYMin < otherYMax && ourYMax > otherYMin;

	return overlapX && overlapY;
}

bool Sprite::isCollidingCircular(const Sprite& other)
{
	int radiusSumSq = (dst.w / 2) + (other.dst.w / 2);
	radiusSumSq *= radiusSumSq;

	int distSq = distanceSq(other.dst.x + other.dst.w / 2, other.dst.y + other.dst.h / 2, dst.x + dst.w / 2, dst.y + dst.h / 2);
	
	bool isColliding = distSq < radiusSumSq;
	return isColliding;
}

int distanceSq(int x1, int y1, int x2, int y2)
{
	int deltaX = x1 - x2;
	int deltaY = y1 - y2;
	return (deltaX * deltaX) + (deltaY * deltaY);
}
