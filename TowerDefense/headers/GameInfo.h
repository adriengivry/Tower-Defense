#ifndef _GAMEINFO_
#define _GAMEINFO_

#include <map>

#include "AudioManager.h"

#define STARTING_MONEY 600
#define MONEY_AFTER_WAVE_CLEAR 80
#define CASTLE_LIFE 100
#define STARTING_STAGE 1
#define STARTING_TICK 0

#define PREPARATION_TIME 20
#define WAVE_DURATION 60

enum GameState
{
	STATE_PLAY,
	STATE_PAUSE,
	STATE_DEFEAT
};

class GameInfo
{
public:
	explicit GameInfo(AudioManager* p_audioManager);
	~GameInfo() {}

	void SetRun(const bool p_value) { m_run = p_value; }
	void SetGameState(const uint8_t p_newGameState) { m_gameState = p_newGameState; }
	void SetMoney(const int p_value) { m_money = p_value; }
	void SetCastleLife(const size_t p_value);
	void SetCastleMaxLife(const size_t p_value) { m_castleMaxLife = p_value; }
	void SetCanSpawn(const bool p_value) { m_canSpawn = p_value; }
	void SetThisTime(const size_t p_value) { m_thisTime = p_value; }
	void SetLastTime(const size_t p_value) { m_lastTime = p_value; }
	void SetDeltaTime(const float p_value) { m_deltaTime = p_value; }
	void SetSelectedTower(const uint8_t p_value) { m_selectedTower = p_value; }
	void SetCurrentStageCompleted(const bool p_value) { m_currentStageCompleted = p_value; }
	void SetStage(const uint8_t p_value) { m_stage = p_value; }
	void SetTickCounter(const size_t p_value) { m_tickCounter = p_value; }
	void SetAudioManager(AudioManager* p_value) { m_audioManager = p_value; }
	void SetTimer(const size_t p_value) { m_timer = p_value + 1; }
	void SetSpawnedEnemies(const size_t p_value) { m_spawnedEnemies = p_value; }
	void SetKilledEnemies(const size_t p_value) { m_killedEnemies = p_value; }
	
	int GetTickCounter() const { return m_tickCounter; }
	float GetElapsedTime() const { return m_elapsedTime; }
	int GetMoney() const { return m_money; }
	size_t GetCastleLife() const { return m_castleLife; }
	size_t GetCastleMaxLife() const { return m_castleMaxLife; }
	uint8_t GetStage() const { return m_stage; }
	uint8_t GetGameState() const { return m_gameState; }
	size_t GetThisTime() const { return m_thisTime; }
	size_t GetLastTime() const { return m_lastTime; }
	float GetDeltaTime() const { return m_deltaTime; }
	uint8_t GetSelectedTower() const { return m_selectedTower; }
	AudioManager* GetAudioManager() const { return m_audioManager; }
	size_t GetTimer() const { return m_timer; }
	size_t GetSpawnedEnemies() const { return m_spawnedEnemies; }
	size_t GetKilledEnemies() const { return m_killedEnemies; }

	bool IsRunning() const { return m_run; }
	bool IsCurrentStageCompleted() const { return m_currentStageCompleted; }
	bool CanSpawn() const { return m_canSpawn; }

	void ToggleCanSpawn() { m_canSpawn = !m_canSpawn; }
	void AddMoney(const int p_value) { m_money += p_value; }
	void RemoveCastleLife(const int p_value);
	void ResetTickCounter() { m_elapsedTime = 0; m_tickCounter = 0;	}
	void AddToElapsed(const float p_value) { m_elapsedTime += p_value; }
	void IncrementTickCounter() { ++m_tickCounter; }
	void NextStage();
	void CheckCastleLife();
	void AddTimer(const size_t p_toAdd) { m_timer += p_toAdd; }
	void IncrementSpawnedEnemies() { ++m_spawnedEnemies; }
	void IncrementKilledEnemies() { ++m_killedEnemies; }

private:
	AudioManager* m_audioManager;

	float m_elapsedTime;

	bool m_run;
	bool m_canSpawn;
	bool m_currentStageCompleted;

	uint8_t m_gameState;
	uint8_t m_stage;
	uint8_t m_selectedTower;

	int m_money;
	size_t m_castleLife;
	size_t m_castleMaxLife;

	size_t m_spawnedEnemies;
	size_t m_killedEnemies;

	size_t m_tickCounter;
	size_t m_timer;
	size_t m_thisTime;
	size_t m_lastTime;
	float m_deltaTime;
};

#endif // !_GAMEINFO_