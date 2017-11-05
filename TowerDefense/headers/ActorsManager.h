#ifndef _ACTORMANAGER_
#define _ACTORMANAGER_

#include <list>

#include "Window.h"
#include "EventManager.h"
#include "UserInterface.h"
#include "Actor.h"
#include "Tower.h"
#include "Slot.h"
#include "Field.h"
#include "TowerButton.h"

class ActorsManager
{
public:
	ActorsManager(Window* p_window, EventManager* p_eventManager, GameInfo* p_gameInfo, UserInterface* p_userInterface);
	~ActorsManager();

	void SetEventManager(EventManager* p_newEventManager) { m_eventManager = p_newEventManager; }
	void SetWindow(Window* p_window) { m_window = p_window; }
	void SetGameInfo(GameInfo* p_gameInfo) { m_gameInfo = p_gameInfo; }
	void SetUserInterface(UserInterface* p_userInterface) { m_userInterface = p_userInterface; }
	void SetField(Field* p_field) { m_gameField = p_field; }
	void SetCastleTowerButton(TowerButton* p_value) { m_CastleTowerButton = p_value; }
	void SetArcherTowerButton(TowerButton* p_value) { m_ArcherTowerButton = p_value; }
	

	EventManager* GetEventManager() const { return m_eventManager; }
	Window* GetWindow() const { return m_window; }
	GameInfo* GetGameInfo() const { return m_gameInfo; }
	UserInterface* GetUserInterface() const { return m_userInterface; }
	Field* GetField() const { return m_gameField; }
	std::list<Enemy*>& GetEnemies() { return m_enemies; }
	std::list<Slot*>& GetSlots() { return m_slots; }
	std::list<Tower*>& GetTowers() { return m_towers; }
	std::list<Projectile*>& GetProjectiles() { return m_projectiles; }
	TowerButton* GetCastleTowerButton() const { return m_CastleTowerButton; }
	TowerButton* GetArcherTowerButton() const { return m_ArcherTowerButton; }

	size_t HowManyAliveEnemy();

	void ClearEnemies();
	void ClearProjectiles();

	void SpawnRandomEnemy();
	void UpdateActors();
	void DisplayActors();

private:
	Field* m_gameField;

	std::list<Enemy*> m_enemies;
	std::list<Slot*> m_slots;
	std::list<Tower*> m_towers;
	std::list<Projectile*> m_projectiles;

	TowerButton* m_CastleTowerButton;
	TowerButton* m_ArcherTowerButton;
	
	EventManager* m_eventManager;
	GameInfo* m_gameInfo;
	Window* m_window;
	UserInterface* m_userInterface;
};

#endif // !_ACTORMANAGER_

