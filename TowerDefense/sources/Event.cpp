#include "Event.h"

void Event::Init(const bool p_value)
{
	m_defaultState = p_value;
	m_state = p_value;
}
