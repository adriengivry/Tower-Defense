#include "Window.h"
#include "GameLoader.h"

Window::Window()
{
	SetWindow(SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS));

	if (!GetWindow())
	{
		std::cout << "failed to create SDL_Window" << std::endl << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}

	SetRenderer(SDL_CreateRenderer(GetWindow(), -1, RENDERER_FLAGS));

	if (!GetRenderer())
	{
		std::cout << "failed to create SDL_Renderer" << std::endl << SDL_GetError() << std::endl;
		exit(EXIT_FAILURE);
	}
}

Window::~Window()
{
	SDL_DestroyRenderer(GetRenderer());
	SDL_DestroyWindow(GetWindow());
}

void Window::UpdateRenderer() const
{
	SDL_RenderPresent(GetRenderer());
}

void Window::ClearScreen() const
{
	SDL_SetRenderDrawColor(GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(GetRenderer());
}
