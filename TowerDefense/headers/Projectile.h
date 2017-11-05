#ifndef _PROJECTILE_
#define _PROJECTILE_

#include "Actor.h"
#include "Enemy.h"

#define PROJECTILE_LIFETIME 500
#define PROJECTILE_SLOW_DURATION 40
#define PROJECTILE_DEFAULT_CRITICAL_RATE 0
#define PROJECTILE_CRITICAL_RATE_MULTIPLICATOR 2
#define PROJECTILE_DEFAULT_ROTATION_SPEED 800

#define PROJECTILE_ARROW_TEXTURE "assets/actors/arrow.png"
#define PROJECTILE_ARROW_SPEED 700
#define PROJECTILE_ARROW_WIDTH 500
#define PROJECTILE_ARROW_HEIGHT 79
#define PROJECTILE_ARROW_SCALE 10

#define PROJECTILE_ROCK_TEXTURE "assets/actors/rock.png"
#define PROJECTILE_ROCK_SPEED 450
#define PROJECTILE_ROCK_WIDTH 374
#define PROJECTILE_ROCK_HEIGHT 294
#define PROJECTILE_ROCK_SCALE 12

enum RotationMode
{
	ROTATE_CONSTANT,
	ROTATE_FOLLOW
};

class Projectile : public Actor
{
public:
	explicit Projectile(Window* p_window = nullptr, const float p_x = 0, const float p_y = 0, const size_t p_damages = 0, const uint8_t p_criticalRate = PROJECTILE_DEFAULT_CRITICAL_RATE, const uint8_t p_towerType = 0);
	~Projectile() {}

	void SetDamages(const size_t p_damages) { m_damages = p_damages; }
	void SetCanSlow(const bool p_value) { m_canSlow = p_value; }
	void SetCriticalRate(const uint8_t p_value) { m_criticalRate = p_value; }
	void SetRotateMode(const uint8_t p_value) { m_rotateMode = p_value; }

	size_t GetDamages() const { return m_damages; }
	uint8_t GetCriticalRate() const { return m_criticalRate; }
	uint8_t GetRotateMode() const { return m_rotateMode; }

	bool CanSlow() const { return m_canSlow; }
	bool MustDie() const override;

	void Tick() override;

private:
	uint8_t m_rotateMode;
	uint8_t m_criticalRate;
	size_t m_damages;
	bool m_canSlow;
};

#endif // !_PROJECTILE_
