#ifndef _EVENTMANAGER_
#define _EVENTMANAGER_

#include <SDL.h>

#include "Event.h"

enum Events
{
	EXIT_EVENT,
	PAUSE_EVENT,
	LEFT_CLICK_EVENT,
	RIGHT_CLICK_EVENT,
	SKIP_PREP_EVENT
};

class EventManager
{
public:
	EventManager();
	~EventManager();

	Event& GetEvent(const size_t p_event);

	void UpdateEvents();
	void PreventClicLoop();

private:
	SDL_Event m_event;
	Event m_exit;
	Event m_leftClick;
	Event m_rightClick;
	Event m_pause;
	Event m_skipPrep;
};

#endif // !_EVENTMANAGER_