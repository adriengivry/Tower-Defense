#include "EventManager.h"
#include "GameInfo.h"

EventManager::EventManager()
{
	m_exit.Init(false);
	m_leftClick.Init(false);
	m_pause.Init(false);
	m_skipPrep.Init(false);
}

EventManager::~EventManager()
{
}

Event & EventManager::GetEvent(const size_t p_event)
{
	switch (p_event)
	{
	default:
	case EXIT_EVENT:			return m_exit;
	case LEFT_CLICK_EVENT:		return m_leftClick;
	case RIGHT_CLICK_EVENT:		return m_rightClick;
	case PAUSE_EVENT:			return m_pause;
	case SKIP_PREP_EVENT:		return m_skipPrep;
	}
}

void EventManager::UpdateEvents()
{
	while (SDL_PollEvent(&m_event))
	{
		if (m_event.type == SDL_QUIT)
			m_exit.SetState(true);

		if (m_event.type == SDL_KEYDOWN)
		{
			switch (m_event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				m_exit.SetState(true);
				break;
			case SDLK_p:
				m_pause.Toggle();
				break;
			case SDLK_t:
				m_skipPrep.SetState(true);
				break;
			}
		}

		if (m_event.type == SDL_MOUSEBUTTONDOWN && m_event.button.button == SDL_BUTTON_LEFT)
			m_leftClick.SetState(true);
		else
			m_leftClick.SetState(false);

		if (m_event.type == SDL_MOUSEBUTTONDOWN && m_event.button.button == SDL_BUTTON_RIGHT)
			m_rightClick.SetState(true);
		else
			m_rightClick.SetState(false);
	}
}

void EventManager::PreventClicLoop()
{
	if (GetEvent(LEFT_CLICK_EVENT).IsOn())
		GetEvent(LEFT_CLICK_EVENT).Toggle();

	if (GetEvent(RIGHT_CLICK_EVENT).IsOn())
		GetEvent(RIGHT_CLICK_EVENT).Toggle();
}
