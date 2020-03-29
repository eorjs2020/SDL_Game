#include "SpriteManager.h"
#include<algorithm>

SpriteManager::SpriteManager()
{
}

SpriteManager::~SpriteManager()
{
}

void SpriteManager::cleanup()
{
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->cleanup();
		delete sprites[i];
	}
}

void SpriteManager::updateAll(float deltaTime)
{
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->update(deltaTime);
		sprites[i]->updateAnimation();
		if (sprites[i]->markedForRemoval)
		{
			sprites[i]->cleanup();
			delete sprites[i];
			sprites[i] = nullptr;
		}
	}

	

	auto endPos = std::remove(sprites.begin(), sprites.end(), nullptr);
	if (endPos != sprites.end())
	{
		sprites.erase(endPos);
	}
	
}

void SpriteManager::drawAll()
{
	for (int i = 0; i < sprites.size(); i++)
	{
		sprites[i]->draw();
	}
}

void SpriteManager::add(Sprite* spriteToAdd)
{
	sprites.push_back(spriteToAdd);
	spriteToAdd->spriteManager = this;
}

