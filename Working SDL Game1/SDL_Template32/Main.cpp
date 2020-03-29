// Create and run the Game class
// Joss Moo-Young
#include <iostream>
#include"Game.h"

Game myGame;

// Main function.
int main(int argc, char* args[]) // Main MUST have these parameters for SDL.
{
	myGame = Game("Hello Game Class", 800, 600);
	myGame.run();
	return 0;
}