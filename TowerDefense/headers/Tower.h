#ifndef _TOWER_
#define _TOWER_

#include "Actor.h"
#include "Enemy.h"
#include "Projectile.h"

#define CASTLE_TOWER_TEXTURE "assets/actors/tower.png"
#define CASTLE_TOWER_WIDTH 256
#define CASTLE_TOWER_HEIGHT 256
#define CASTLE_TOWER_SCALE 1.5
#define CASTLE_TOWER_COST 150
#define CASTLE_TOWER_RANGE 275
#define CASTLE_TOWER_COOLDOWN 80
#define CASTLE_TOWER_DAMAGES 16
#define CASTLE_TOWER_CRITICAL_RATE 5
#define CASTLE_TOWER_RANGE_UPGRADE 12
#define CASTLE_TOWER_DAMAGES_UPGRADE 4
#define CASTLE_TOWER_UPGRADE_COST 85

#define ARCHER_TOWER_TEXTURE "assets/actors/archer_tower.png"
#define ARCHER_TOWER_WIDTH 256
#define ARCHER_TOWER_HEIGHT 256
#define ARCHER_TOWER_SCALE 1.5
#define ARCHER_TOWER_COST 275
#define ARCHER_TOWER_RANGE 325
#define ARCHER_TOWER_COOLDOWN 45
#define ARCHER_TOWER_DAMAGES 12
#define ARCHER_TOWER_CRITICAL_RATE 5
#define ARCHER_TOWER_RANGE_UPGRADE 25
#define ARCHER_TOWER_DAMAGES_UPGRADE 2
#define ARCHER_TOWER_UPGRADE_COST 150

#define TOWER_RANGE_TEXTURE "assets/items/range.png"
#define TOWER_LEVEL_BACKGROUND_TEXTURE "assets/items/level_background.png"
#define TOWER_LEVEL_BACKGROUND_Y_OFFSET -30
#define TOWER_LEVEL_BACKGROUND_WIDTH 420
#define TOWER_LEVEL_BACKGROUND_HEIGHT 142
#define TOWER_LEVEL_BACKGROUND_SCALE 3

enum TowerType
{
	CASTLE_TOWER,
	ARCHER_TOWER
};

class Tower : public Actor
{
public:
	explicit Tower(Window* p_window = nullptr, GameInfo* p_gameInfo = nullptr, const uint8_t p_towerType = TowerType::ARCHER_TOWER, const float p_x = 0, const float p_y = 0);
	virtual ~Tower() {}

	void SetMaxCooldown(const int p_value) { m_maxCooldown = p_value; }
	void SetCurrentCooldown(const int p_value) { m_currentCooldown = p_value; }
	void SetDamageToAdd(const int p_value) { m_damageToAdd = p_value; }
	void SetRangeToAdd(const int p_value) { m_rangeToAdd = p_value; }
	void SetUpgradeCost(const int p_value) { m_upgradeBaseCost = p_value; }
	void SetLevel(const size_t p_value) { m_level = p_value; }
	void SetType(const uint8_t p_value) { m_type = p_value; }
	void SetTowerInfoToConsole() const;
	void SetRange(const size_t p_newRange) { m_range = p_newRange; }
	void SetDamages(const size_t p_newDamages) { m_damages = p_newDamages; }
	void SetMustBeRemoved(const bool p_value) { m_mustBeRemoved = p_value; }
	void SetLevelBackgroundTexture(SDL_Texture* p_texture) { m_levelBackgroundTexture = p_texture; }
	void SetCriticalRate(const uint8_t p_value) { m_criticalRate = p_value; }

	int GetDamageToAdd() const { return m_damageToAdd; }
	int GetRangeToAdd() const { return m_rangeToAdd; }
	int GetUpgradeCost() const { return m_upgradeBaseCost * GetLevel(); }
	int GetCooldown() const { return m_maxCooldown; }
	int GetCurrentCooldown() const { return m_currentCooldown; }
	uint8_t GetType() const { return m_type; }
	size_t GetLevel() const { return m_level; }
	size_t GetRange() const { return m_range; }
	size_t GetDamages() const { return m_damages; }
	uint8_t GetCriticalRate() const { return m_criticalRate; }
	SDL_Rect& GetLevelBackgroundRect() { return m_levelBackgroundRect; }
	SDL_Texture* GetLevelBackgroundTexture() const { return m_levelBackgroundTexture; }

	bool CanShoot() const { return m_currentCooldown <= 0; }
	bool CanGetUpgraded() const;

	bool MustBeRemoved() const { return m_mustBeRemoved; }

	void AddDamages(const size_t p_toAdd) { m_damages += p_toAdd; }
	void AddRange(const size_t p_toAdd) { m_range += p_toAdd; }
	void AddLevel(const size_t p_toAdd) { m_level += p_toAdd; }

	void Shoot(Enemy* p_target);
	void Upgrade();
	void UpdateShootCooldown();

	void Update(EventManager& p_eventManager) override;
	void Display() override;
	
	void Tick() override;
	void OnMouseOver() override;
	void OnClick() override;
	void OnRightClick() override;

private:
	uint8_t m_type;
	size_t m_level;
	size_t m_range;
	size_t m_damages;
	uint8_t m_criticalRate;

	bool m_mustBeRemoved;

	int m_upgradeBaseCost;
	int m_rangeToAdd;
	int m_damageToAdd;

	int m_maxCooldown;
	int m_currentCooldown;

	SDL_Rect m_levelBackgroundRect;
	SDL_Texture* m_levelBackgroundTexture;
};

#endif // !_TOWER_

