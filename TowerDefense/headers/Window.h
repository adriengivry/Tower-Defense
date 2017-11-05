#ifndef _WINDOW_
#define _WINDOW_

#include <iostream>
#include <SDL.h>

#include "Infos.h"

#define WINDOW_FLAGS SDL_WINDOW_FULLSCREEN
#define RENDERER_FLAGS SDL_RENDERER_PRESENTVSYNC

class Window
{
public:
	Window();
	~Window();
	
	void SetWindow(SDL_Window* p_window) { m_windowComponent = p_window; }
	void SetRenderer(SDL_Renderer* p_renderer) { m_rendererComponent = p_renderer; }

	SDL_Renderer* GetRenderer() const { return m_rendererComponent; }
	SDL_Window* GetWindow() const { return m_windowComponent; }

	void UpdateRenderer() const;
	void ClearScreen() const;

private:
	SDL_Window* m_windowComponent;
	SDL_Renderer* m_rendererComponent;
};

#endif // !_WINDOW_
