#include "SDLManager.h"

SDLManager::SDLManager()
{
	if (SDL_Init(SDL_INIT_EVERYTHING))
		std::cout << "failed to init SDL" << std::endl << SDL_GetError() << std::endl;

	if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG))
		std::cout << "failed to init IMG" << std::endl << IMG_GetError() << std::endl;

	if (TTF_Init())
		std::cout << "failed to init TTF" << std::endl << TTF_GetError() << std::endl;
}

SDLManager::~SDLManager()
{
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

