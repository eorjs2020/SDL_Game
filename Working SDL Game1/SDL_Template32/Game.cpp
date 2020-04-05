#include "Game.h"
#include <iostream>
#include <SDL_image.h>
#include "Enemy.h"

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

			if (Mix_Init(MIX_INIT_MP3) != 0)
			{
				std::cout << "Mix failed to initialize" << std::endl;
			}
			//44.1 kHz
			Mix_OpenAudio(22400, AUDIO_U16, 8, 2048);
			bgm = Mix_LoadWAV("sounds/bgm.wav");
			fireball = Mix_LoadWAV("sounds/laserBlast.wav");
			
		}
	}
}

Game::~Game()
{
}

void Game::run()
{
	//shipBullet = new Bullet(pRenderer, "Assets/fireball.png", 32, 32, 500);
	
	ship = new Ship(pRenderer, "Assets/Seagull_Wizard_1.png", 64, 64, 1);
	ship->tag = SpriteTag::PLAYER;
	background = new Sprite(pRenderer, "Assets/background.png", 800, 600);
	background2 = new Sprite(pRenderer, "Assets/background.png", 800, 600);


	spriteManager.add(background);
	spriteManager.add(background2);
	
	
	
	spriteManager.add(ship);

	background->setPosition(0,0);
	background2->setPosition(-800, 0);
	ship->setPosition(400, sin((float)SDL_GetTicks() / 1000.f) * 200 + 200);
	Mix_PlayChannel(0, bgm, -1);
	Mix_Volume(0, 64);

	

	

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
	
	static bool spacePressed = false;

	static bool musicPaused = false;

	

	while (SDL_PollEvent(&sdlEvent))
	{
		if (sdlEvent.type == SDL_KEYDOWN)
		{
		

			switch (sdlEvent.key.keysym.sym)
			{
			
			case(SDLK_SPACE):
			{
				if (!spacePressed)
				{
					spacePressed = true;
					Mix_PlayChannel(1, fireball, -1);
				}

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
			case(SDLK_m):
			{
				musicPaused = !musicPaused;
				
				
				if (musicPaused)
				{
					Mix_Resume(0);
				}
				else
				{
					Mix_Pause(0);
				}
				
				
				break;
			}
			}
		}
		if (sdlEvent.type == SDL_KEYUP)
		{
			switch (sdlEvent.key.keysym.sym)
			{
			case(SDLK_SPACE):
			{
				spacePressed = false;
				Mix_HaltChannel(1);
				break;
			}
			}
		}
		
	}
	if (spacePressed)
	{
		ship->tryShoot();
		
	}
}

void Game::update()
{
	int counter{};
	spriteManager.updateAll(deltaTime);

	counter = counter + 10;
	/*std::cout << counter;*/
	background->dst.x += counter;
	background2->dst.x += counter;
	if (background->dst.x > 800)
	{
		background->dst.x = -790;
	}
	if (background2->dst.x > 800)
	{
		background2->dst.x = -790;
	}

	enemyTimer -= deltaTime;
	if (enemyTimer <= 0)
	{
		std::cout << counter;
		Enemy* newenemy = new Enemy(pRenderer, "Assets/human.png", 40, 40, 50);
		newenemy->dst.x = rand() % 700;
		newenemy->dst.y = rand() % 300;
		
		spriteManager.add(newenemy);

		enemyTimer = enemySpawnDelay;
		newenemy->enemyTryShoot();
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
