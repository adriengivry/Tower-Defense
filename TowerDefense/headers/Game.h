#ifndef _GAME_
#define _GAME_

#include <ctime>
#include <random>

#include "SDLManager.h"
#include "GameInfo.h"
#include "Window.h"
#include "EventManager.h"
#include "UserInterface.h"
#include "ActorsManager.h"
#include "GameLoader.h"
#include "AudioManager.h"

#include "maths_operation.h"

class Game
{
public:
	Game();
	~Game();

	GameInfo* GetGameInfo() const { return m_gameInfo; }
	Window* GetWindow() const { return m_window; }
	SDLManager* GetSDLManager() const { return m_sdlManager; }
	EventManager* GetEventManager() const { return m_eventManager; }
	UserInterface* GetUserInterface() const { return m_userInterface; }
	ActorsManager* GetActorsManager() const { return m_actorManager; }
	GameLoader* GetGameLoad() const { return m_gameLoader; }
	AudioManager* GetAudioManager() const { return m_audioManager; }

	void CheckEvents() const;

	void Setup() const;	

	uint8_t Run() const;

	void Tick() const;
	void PauseTick() const;
	void DefeatTick() const;
	void PlayTick() const;

	bool ElapsedIsBetween(const float p_startTime, const float p_endTime) const { return GetGameInfo()->GetTickCounter() >= p_startTime * 60 && GetGameInfo()->GetTickCounter() <= p_endTime * 60; }
	bool ElapsedIs(const float p_time) const { return GetGameInfo()->GetTickCounter() == p_time * 60; }
	bool ElapsedIsSuperior(const float p_time) const { return GetGameInfo()->GetTickCounter() >= p_time * 60; }
	bool ElapsedIsInferior(const float p_time) const { return GetGameInfo()->GetTickCounter() <= p_time * 60; }
	bool ElapsedIsSuperior_s(const float p_time) const { return GetGameInfo()->GetTickCounter() > p_time * 60; }
	bool ElapsedIsInferior_s(const float p_time) const { return GetGameInfo()->GetTickCounter() < p_time * 60; }

	bool ToDoEveryXTicks(const size_t p_value) const { return GetGameInfo()->GetTickCounter() % p_value == 0; }

private:
	GameInfo* m_gameInfo;
	SDLManager* m_sdlManager;
	Window* m_window;
	EventManager* m_eventManager;
	UserInterface* m_userInterface;
	ActorsManager* m_actorManager;
	GameLoader* m_gameLoader;
	AudioManager* m_audioManager;
};

#endif // !_GAME_

