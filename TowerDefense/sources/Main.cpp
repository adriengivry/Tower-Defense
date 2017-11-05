#include <iostream>

#include <SDL.h>

#include "Game.h"

int main(int argc, char *argv[])
{
	Game gameInstance;
	gameInstance.Run();

	return EXIT_SUCCESS;
}