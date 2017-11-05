#include "ActorsManager.h"

ActorsManager::ActorsManager(Window * p_window, EventManager * p_eventManager, GameInfo* p_gameInfo, UserInterface* p_userInterface)
{
	SetWindow(p_window);
	SetEventManager(p_eventManager);
	SetGameInfo(p_gameInfo);
	SetUserInterface(p_userInterface);

	SetField(new Field(GetWindow(), GetGameInfo()));
	GetField()->SetUserInterface(GetUserInterface());

	SetCastleTowerButton(new TowerButton(GetWindow(), GetGameInfo(), 0));
	GetCastleTowerButton()->SetUserInterface(GetUserInterface());

	SetArcherTowerButton(new TowerButton(GetWindow(), GetGameInfo(), 1));
	GetArcherTowerButton()->SetUserInterface(GetUserInterface());
}

ActorsManager::~ActorsManager()
{
	delete GetField();

	delete GetCastleTowerButton();
	delete GetArcherTowerButton();

	for (auto it = GetSlots().begin(); it != GetSlots().end(); ++it)
		if (*it)
			delete *it;

	for (auto it = GetEnemies().begin(); it != GetEnemies().end(); ++it)
		if (*it)
			delete *it;

	for (auto it = GetTowers().begin(); it != GetTowers().end(); ++it)
		if (*it)
			delete *it;

	for (auto it = GetProjectiles().begin(); it != GetProjectiles().end(); ++it)
		if (*it)
			delete *it;	
}

void ActorsManager::UpdateActors()
{
	Slot* currentSlot = nullptr;
	Tower* currentTower = nullptr;
	Enemy* currentEnemy = nullptr;
	Projectile* currentProjectile = nullptr;
	Field* gameField = GetField();
	TowerButton* CastleTowerButton = GetCastleTowerButton();
	TowerButton* ArcherTowerButton = GetArcherTowerButton();

	gameField->Update(*GetEventManager()); 
	CastleTowerButton->Update(*GetEventManager());
	ArcherTowerButton->Update(*GetEventManager());

	for (auto it = GetSlots().begin(); it != GetSlots().end(); ++it)
	{
		currentSlot = *it;
		if (*it && currentSlot->IsUpdatable())
			currentSlot->Update(*GetEventManager());

		if (*it && currentSlot->MustDie())
		{
			delete *it;
			*it = nullptr;
		}
	}

	for (auto it = GetTowers().begin(); it != GetTowers().end(); ++it)
	{
		currentTower = *it;
		if (*it && currentTower->IsUpdatable())
			currentTower->Update(*GetEventManager());

		if (*it && currentSlot->MustDie())
		{
			delete *it;
			*it = nullptr;
		}
	}

	for (auto it = GetEnemies().begin(); it != GetEnemies().end(); ++it)
	{
		currentEnemy = *it;
		if (*it && currentEnemy->IsUpdatable())
			currentEnemy->Update(*GetEventManager());

		if (*it && currentSlot->MustDie())
		{
			delete *it;
			*it = nullptr;
		}
	}

	for (auto it = GetProjectiles().begin(); it != GetProjectiles().end(); ++it)
	{
		currentProjectile = *it;

		if (currentProjectile && currentProjectile->IsUpdatable())
			currentProjectile->Update(*GetEventManager());

		
		if (currentProjectile && currentProjectile->MustDie())
		{
			delete *it;
			*it = nullptr;
		}
		
	}
}

void ActorsManager::DisplayActors()
{
	Slot* currentSlot = nullptr;
	Tower* currentTower = nullptr;
	Enemy* currentEnemy = nullptr;
	Projectile* currentProjectile = nullptr;
	Field* gameField = GetField();
	TowerButton* CastleTowerButton = GetCastleTowerButton();
	TowerButton* ArcherTowerButton = GetArcherTowerButton();

	gameField->Display();
	CastleTowerButton->Display();
	ArcherTowerButton->Display();

	for (auto it = GetSlots().begin(); it != GetSlots().end(); ++it)
	{
		currentSlot = *it;
		if (*it && currentSlot->IsUpdatable())
			currentSlot->Display();
	}

	for (auto it = GetTowers().begin(); it != GetTowers().end(); ++it)
	{
		currentTower = *it;
		if (*it && currentTower->IsUpdatable())
			currentTower->Display();
	}

	for (auto it = GetEnemies().begin(); it != GetEnemies().end(); ++it)
	{
		currentEnemy = *it;
		if (*it && currentEnemy->IsUpdatable())
			currentEnemy->Display();
	}

	for (auto it = GetProjectiles().begin(); it != GetProjectiles().end(); ++it)
	{
		currentProjectile = *it;

		if (currentProjectile && currentProjectile->IsUpdatable())
			currentProjectile->Display();
	}
}

size_t ActorsManager::HowManyAliveEnemy()
{
	size_t counter = 0;
	
	for (auto it = GetEnemies().begin(); it != GetEnemies().end(); ++it)
		if (*it && (*it)->IsAlive() && (*it)->IsUpdatable())
			++counter;

	return counter;
}

void ActorsManager::ClearEnemies()
{
	for (auto it = GetEnemies().begin(); it != GetEnemies().end(); ++it)
		if (*it)
			delete *it;

	GetEnemies().clear();
}

void ActorsManager::ClearProjectiles()
{
	for (auto it = GetProjectiles().begin(); it != GetProjectiles().end(); ++it)
		if (*it)
			delete *it;

	GetProjectiles().clear();
}

void ActorsManager::SpawnRandomEnemy()
{
	const uint8_t enemyRandom = rand() % 100 + 1;
	uint8_t enemyType = 0;

	if (enemyRandom <= 60)
		enemyType = 0;
	else if (enemyRandom <= 80)
		enemyType = 1;
	else if (enemyRandom <= 100)
		enemyType = 2;

	Enemy* enemy = new Enemy(GetWindow(), GetGameInfo(), enemyType);

	enemy->SetEnemyList(&GetEnemies());
	enemy->SetPosition(static_cast<float>(ENEMY_X_SPAWN), static_cast<float>(ENEMY_Y_SPAWN - enemy->GetHitbox().h / 2));
	enemy->SetUserInterface(GetUserInterface());

	if (rand() % 100 + 1 <= ENEMY_INVINCIBLE_RATE + GetGameInfo()->GetStage() * 1.2)
		enemy->SetInvincible(true);

	GetEnemies().push_back(enemy);
	GetGameInfo()->IncrementSpawnedEnemies();
}

