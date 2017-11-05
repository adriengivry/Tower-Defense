#ifndef _EVENT_
#define _EVENT_

class Event
{
public:
	explicit Event(const bool p_value = false) { Init(p_value); }
	~Event() {}

	void SetState(const bool p_newState) { m_state = p_newState; }
	void SetDefaultState(const bool p_newDefaultState) { m_defaultState = p_newDefaultState; }

	bool GetState() const { return m_state; }
	bool GetDefaultState() const { return m_defaultState; }

	bool IsOn() const { return m_state; }
	bool IsOff() const { return !m_state; }

	void Toggle() { m_state = !m_state; }

	void Init(bool p_value);

private:
	bool m_defaultState;
	bool m_state;
};

#endif // !_EVENT_