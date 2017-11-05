#ifndef _ENEMY_
#define _ENEMY_

#include "Actor.h"

#define ENEMY_LIFETIME 5000
#define ENEMY_DEFAULT_X_DIRECTION 1
#define ENEMY_DEFAULT_Y_DIRECTION 0
#define ENEMY_INVINCIBLE_RATE 20
#define ENEMY_SLOW_MULTIPLICATOR 0.75
#define ENEMY_ROLLING false
#define ENEMY_ROLLING_SPEED 200
#define ENEMY_X_SPAWN 0
#define ENEMY_Y_SPAWN 812

#define ENEMY_SAY_COOLDOWN 400
#define ENEMY_GOLD_LOOT 25

#define ENEMY_LIFEBAR_TEXTURE "assets/UI/lifebar.png"
#define ENEMY_LIFEBAR_WIDTH 100
#define ENEMY_LIFEBAR_HEIGHT 10

#define ENEMY_SHIELD_TEXTURE "assets/items/shield.png"
#define ENEMY_SHIELD_WIDTH 120
#define ENEMY_SHIELD_HEIGHT 120
#define ENEMY_SHIELD_SCALE 1.5

#define NOOB_TEXTURE "assets/actors/noob/idle.png"
#define NOOB_DEATH_TEXTURE "assets/actors/noob/death.png"
#define NOOB_DEATH_TEXTURE_WIDTH 64
#define NOOB_DEATH_TEXTURE_HEIGHT 64
#define NOOB_DEATH_TEXTURE_SCALE 1
#define NOOB_LIFE 110
#define NOOB_SPEED 80
#define NOOB_ATTACK 15
#define NOOB_WIDTH 242
#define NOOB_HEIGHT 248
#define NOOB_SCALE 3

#define WARRIOR_TEXTURE "assets/actors/warrior/idle.png"
#define WARRIOR_DEATH_TEXTURE "assets/actors/warrior/death.png"
#define WARRIOR_DEATH_TEXTURE_WIDTH 64
#define WARRIOR_DEATH_TEXTURE_HEIGHT 64
#define WARRIOR_DEATH_TEXTURE_SCALE 1
#define WARRIOR_LIFE 150
#define WARRIOR_SPEED 55
#define WARRIOR_ATTACK 25
#define WARRIOR_WIDTH 267
#define WARRIOR_HEIGHT 290
#define WARRIOR_SCALE 3

#define DOC_TEXTURE "assets/actors/doc/idle.png"
#define DOC_DEATH_TEXTURE "assets/actors/doc/death.png"
#define DOC_DEATH_TEXTURE_WIDTH 64
#define DOC_DEATH_TEXTURE_HEIGHT 64
#define DOC_DEATH_TEXTURE_SCALE 1
#define DOC_LIFE 70
#define DOC_SPEED 110
#define DOC_ATTACK 8
#define DOC_HEALING_POWER 2
#define DOC_HEALING_RANGE 100
#define DOC_HEALING_COOLDOWN 15
#define DOC_WIDTH 167
#define DOC_HEIGHT 230
#define DOC_SCALE 3

enum EnemyType
{
	NOOB,
	WARRIOR,
	DOC
};

class Enemy : public Actor
{
public:
	explicit Enemy(Window* p_window = nullptr, GameInfo* p_gameInfo = nullptr, const uint8_t p_type = NOOB, const float p_x = 0, const float p_y = 0);
	~Enemy();

	void SetLife(const int p_life);
	void SetMaxLife(const size_t p_maxLife) { m_maxLife = p_maxLife; }
	void SetAttack(const size_t p_attackDamage) { m_attackDamage = p_attackDamage; }
	void SetHealPower(const size_t p_healPower) { m_healPower = p_healPower; }
	void SetHealingRange(const size_t p_range) { m_healingRange = p_range; }
	void SetTimeSinceLastHit(const int p_value) { m_timeSinceLastHit = p_value; }
	void SetSlowDuration(const size_t p_value) { m_slowDuration = p_value; }
	void SetSlow(const bool p_value) { m_isSlow = p_value; }
	void SetType(const uint8_t p_type) { m_type = p_type; }
	void SetLifeBarSize(const int p_width, const int p_height);
	void SetMaxSpeed(const float p_value) { m_maxSpeed = p_value; }
	void SetCurrentLifebarTexture(SDL_Texture* p_value) { m_currentLifebarTexture = p_value; }
	void SetInvincible(const bool p_value);
	void SetShieldTexture(SDL_Texture* p_value) { m_shieldTexture = p_value; }
	void SetTimeSinceDeath(const size_t p_value) { m_timeSinceDeath = p_value; }
	void SetRolling(const bool p_value, const size_t p_speed) { m_youSeeMeRolling = p_value; m_rollingInc = p_speed; }
	void SetSayCooldown(const size_t p_value) { m_sayCooldown = p_value; }

	size_t GetLife() const { return m_currentLife; }
	size_t GetMaxLife() const { return m_maxLife; }
	size_t GetAttack() const { return m_attackDamage; }
	size_t GetHealPower() const { return m_healPower; }
	size_t GetHealingRange() const { return m_healingRange; }
	int GetTimeSinceLastHit() const { return m_timeSinceLastHit; }
	size_t GetSlowDuration() const { return m_slowDuration; }
	uint8_t GetType() const { return m_type; }
	Vector2D<int>& GetLifeBarSize() { return m_lifeBarSize; }
	float GetMaxSpeed() const { return m_maxSpeed; }
	SDL_Rect& GetCurrentLifebarRect() { return m_currentLifebarRect; }
	SDL_Texture* GetCurrentLifebarTexture() const { return m_currentLifebarTexture; }
	SDL_Rect& GetShieldRect() { return m_shieldRect; }
	SDL_Rect& GetMaxLifeBar() { return m_maxLifeBar; }
	SDL_Texture* GetShieldTexture() const { return m_shieldTexture; }
	size_t GetTimeSinceDeath() const { return m_timeSinceDeath; }
	size_t GetRollingInc() const { return m_rollingInc; }
	size_t GetSayCooldown() const { return m_sayCooldown; }

	bool IsSlow() const { return m_isSlow; }
	bool IsAlive() const { return GetLife() > 0; }
	bool IsInvincible() const { return m_isInvincible; }
	bool YouSeeMeRolling() const { return m_youSeeMeRolling; }

	void DecrementSayCooldown() { if (GetSayCooldown() > 0) SetSayCooldown(GetSayCooldown() - 1); }
	void IncrementTimeSinceLastHit() { if (GetTimeSinceLastHit() != -1) SetTimeSinceLastHit(GetTimeSinceLastHit() + 1); }

	bool CanHeal() const { return GetTickCounter() % DOC_HEALING_COOLDOWN == 0; }
	bool CanTalk() const { return GetSayCooldown() == 0; }

	void AddLife(const int p_toAdd) { SetLife(GetLife() + p_toAdd); }
	void ReceiveDamages(const int p_value, const bool p_isCrit = false);
	void FollowPath();
	void Slow(const int p_duration);
	void Heal();
	void Say(const std::string p_toSay, const int p_messageLifetime = DEFAULT_MESSAGE_LIFETIME, const bool p_sayInRed = false) override;

	void Display() override;
	void Tick() override;

	void Move(const float p_x, const float p_y) override;

	void Destroy(const std::string p_message = "") override;
	
	void OnMouseOver() override;
	void OnClick() override;

private:
	uint8_t m_type;

	size_t m_maxLife;
	size_t m_currentLife;
	size_t m_attackDamage;

	size_t m_healPower;
	size_t m_healingRange;

	float m_maxSpeed;

	SDL_Rect m_currentLifebarRect;
	SDL_Texture* m_currentLifebarTexture;

	SDL_Rect m_shieldRect;
	SDL_Texture* m_shieldTexture;

	SDL_Rect m_maxLifeBar;
	
	bool m_isSlow;
	bool m_isInvincible;
	bool m_youSeeMeRolling;
	bool m_lastHitWasBlocked;
	bool m_lastHitWasCrit;
	int m_lastHitDamages;
	
	size_t m_slowDuration;
	size_t m_timeSinceLastHit;
	size_t m_sayCooldown;

	size_t m_rollingInc;

	size_t m_timeSinceDeath;

	Vector2D<int> m_lifeBarSize;

	Vector2D<float> m_backupPos;
};

#endif // !_ENEMY_