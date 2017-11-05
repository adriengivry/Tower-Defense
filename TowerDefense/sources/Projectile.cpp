#include "Projectile.h"

Projectile::Projectile(Window* p_window, const float p_x, const float p_y, const size_t p_damages, const uint8_t p_criticalRate, const uint8_t p_projectileType) : Actor(p_window, nullptr, p_x, p_y)
{
	SetLifeTime(PROJECTILE_LIFETIME);

	SetAbleToDie(true);
	SetDisplayable(true);

	switch (p_projectileType)
	{
	default:
	case 0:
		SetTexture(PROJECTILE_ROCK_TEXTURE);
		SetSpeed(PROJECTILE_ROCK_SPEED);
		SetSize(static_cast<int>(PROJECTILE_ROCK_HEIGHT / PROJECTILE_ROCK_SCALE), static_cast<int>(PROJECTILE_ROCK_HEIGHT / PROJECTILE_ROCK_SCALE));
		SetRotateMode(RotationMode::ROTATE_CONSTANT);
		break;

	case 1:
		SetTexture(PROJECTILE_ARROW_TEXTURE);
		SetSpeed(PROJECTILE_ARROW_SPEED);
		SetSize(static_cast<int>(PROJECTILE_ARROW_WIDTH / PROJECTILE_ARROW_SCALE), static_cast<int>(PROJECTILE_ARROW_HEIGHT / PROJECTILE_ARROW_SCALE));
		SetRotateMode(RotationMode::ROTATE_FOLLOW);
		SetCanSlow(true);
		break;
	}

	SetDamages(p_damages);
	SetCriticalRate(p_criticalRate);
}

bool Projectile::MustDie() const
{
	return	Actor::MustDie() ||
			!GetTargetToFollow() ||
			!GetTargetToFollow()->IsUpdatable() ||
			!GetTargetToFollow()->IsAttackable();
}

void Projectile::Tick()
{
	if (GetRotateMode() == RotationMode::ROTATE_FOLLOW)
		SetRotationAngle((atan2(1.f, 0.f) - atan2(GetDirection().X(), GetDirection().Y())) * 180.f / 3.14f);
	else if (GetRotateMode() == RotationMode::ROTATE_CONSTANT)
		SetRotationAngle(GetRotationAngle() + PROJECTILE_DEFAULT_ROTATION_SPEED * GetGameInfo()->GetDeltaTime());

	if (CanSlow())
		SDL_SetTextureColorMod(m_texture, 100, 100, 255);
	else
		SDL_SetTextureColorMod(m_texture, 255, 255, 255);

	if (Intersect(*GetTargetToFollow()) && GetTargetToFollow()->IsUpdatable())
	{
		int damages = GetDamages();
		const bool isCrit = rand() % 100 + 1 <= GetCriticalRate();
		if (isCrit)
			damages *= PROJECTILE_CRITICAL_RATE_MULTIPLICATOR;

		static_cast<Enemy*>(GetTargetToFollow())->ReceiveDamages(damages, isCrit);

		if (CanSlow())
			static_cast<Enemy*>(GetTargetToFollow())->Slow(PROJECTILE_SLOW_DURATION);

		Destroy();
	}
}
