#include "Game.h"
#include <iostream>
#include <SDL_image.h>

Game::Game()
{
}

Game::Game(const char* windowName, int windowSizeX, int windowSizeY)
{
	int flags = SDL_INIT_EVERYTHING;

	if (SDL_Init(flags) == 0) // if initialized SDL correctly...
	{
		// Create the window
		pWindow = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowSizeX, windowSizeY, SDL_WINDOW_SHOWN);

		if (pWindow != nullptr)
		{
			// Create the renderer
			pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_PRESENTVSYNC);

			if (pRenderer != nullptr)
			{
				IMG_Init(IMG_INIT_PNG);
			}
		}
	}
}

Game::~Game()
{
}

void Game::run()
{
	shipBullet = new Bullet(pRenderer, "Assets/fireball.png", 32, 32, 500);
	asteroid = new Sprite(pRenderer, "Assets/Can_1.png", 100, 100);
	ship = new Ship(pRenderer, "Assets/Seagull_Wizard_1.png", 64, 64, 1);
	background = new Sprite(pRenderer, "Assets/background.png", 800, 600);

	spriteManager.add(background);
	spriteManager.add(new Sprite(pRenderer, "Assets/SonicTheHedgehog.png", 128, 128, 8));
	spriteManager.add(shipBullet);
	spriteManager.add(asteroid);
	spriteManager.add(ship);

	background->setPosition(0,0);
	ship->setPosition(400, sin((float)SDL_GetTicks() / 1000.f) * 200 + 200);
	asteroid->setPosition(500, 200);



	isRunning = true;
	
	// set initial delta time
	deltaTime = 1.0f / targetFramerate;
	lastFrameStartTimeMs = SDL_GetTicks();

	while (isRunning)
	{
		input();
		update();
		draw();
		waitForNextFrame();
	}

	cleanup();
}

void Game::input()
{
	SDL_Event sdlEvent;

	float movementSpeed = 200;

	while (SDL_PollEvent(&sdlEvent))
	{
		if (sdlEvent.type == SDL_KEYDOWN)
		{
		

			switch (sdlEvent.key.keysym.sym)
			{
			
			case(SDLK_SPACE):
			{
				ship->tryShoot();
				break;
			}
			case(SDLK_a):
			{
				ship->dst.x -= movementSpeed * deltaTime;
				break;
			}
			case(SDLK_d):
			{
				
				ship->dst.x += movementSpeed * deltaTime;
				break;
			}
			case(SDLK_w):
			{
				ship->dst.y -= movementSpeed * deltaTime;
				break;
			}
			case(SDLK_s):
			{
				ship->dst.y += movementSpeed * deltaTime;
				break;
			}

			case(SDLK_ESCAPE):
			{
				quit();
				break;
			}
			}
		}
		
	}
}

void Game::update()
{
	spriteManager.updateAll(deltaTime);

	if (ship->isCollidingWith(*asteroid))
	{
		std::cout << "colliding" << std::endl;
	}

	
}

void Game::draw()
{
	SDL_SetRenderDrawColor(pRenderer, 255, 205, 90, 255);
	SDL_RenderClear(pRenderer);
	
	spriteManager.drawAll();
	
	SDL_RenderPresent(pRenderer);
}

void Game::waitForNextFrame()
{
	Uint32 gameTimeMs = SDL_GetTicks();
	timeSinceLastFrame = gameTimeMs - lastFrameStartTimeMs;

	if (timeSinceLastFrame < frameDelayMs)
	{
		SDL_Delay(frameDelayMs - timeSinceLastFrame);
	}

	frameEndTimeMs = SDL_GetTicks();
	deltaTime = (frameEndTimeMs - lastFrameStartTimeMs)/1000.f;
	gameTime = frameEndTimeMs / 1000.f;
	lastFrameStartTimeMs = frameEndTimeMs;
	
}

void Game::quit()
{
	isRunning = false;
}

void Game::cleanup()
{
	spriteManager.cleanup();
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	std::cout << "Goodbye World" << std::endl;
}
