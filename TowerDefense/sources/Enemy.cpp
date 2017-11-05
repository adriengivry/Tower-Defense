#include "Enemy.h"

Enemy::Enemy(Window* p_window, GameInfo* p_gameInfo, const uint8_t p_type, const float p_x, const float p_y) : Actor(p_window, p_gameInfo, p_x, p_y)
{
	SetAttackable(true);
	SetHealable(true);
	SetAbleToDie(true);
	SetMessageAnimated(false);


	SetLifeTime(ENEMY_LIFETIME);
	SetDirection(ENEMY_DEFAULT_X_DIRECTION, ENEMY_DEFAULT_Y_DIRECTION);
	SetType(p_type);
	SetTimeSinceLastHit(-1);
	SetRolling(ENEMY_ROLLING, ENEMY_ROLLING_SPEED);

	GetSpeakRect().x = 0;
	GetSpeakRect().x = 0;
	GetSpeakRect().w = static_cast<int>(ACTOR_SPEAK_WIDTH / ACTOR_SPEAK_SCALE);
	GetSpeakRect().h = static_cast<int>(ACTOR_SPEAK_HEIGHT / ACTOR_SPEAK_SCALE);

	SetSpeakTexture(IMG_LoadTexture(GetWindow()->GetRenderer(), ACTOR_SPEAK_TEXTURE_PATH));
	SetCurrentLifebarTexture(IMG_LoadTexture(GetWindow()->GetRenderer(), ENEMY_LIFEBAR_TEXTURE));
	SetShieldTexture(IMG_LoadTexture(GetWindow()->GetRenderer(), ENEMY_SHIELD_TEXTURE));

	GetShieldRect().x = 0;
	GetShieldRect().y = 0;
	GetShieldRect().w = static_cast<int>(ENEMY_SHIELD_WIDTH / ENEMY_SHIELD_SCALE);
	GetShieldRect().h = static_cast<int>(ENEMY_SHIELD_HEIGHT / ENEMY_SHIELD_SCALE);

	switch (p_type)
	{
	default:
	case NOOB:
		SetTexture(NOOB_TEXTURE);
		SetMaxLife(static_cast<size_t>(NOOB_LIFE * (1 + GetGameInfo()->GetStage() * 0.8)));
		SetLife(static_cast<int>(NOOB_LIFE * (1 + GetGameInfo()->GetStage() * 0.8)));
		SetSpeed(static_cast<float>(NOOB_SPEED + GetGameInfo()->GetStage() * 2));
		SetAttack(NOOB_ATTACK);
		SetSize(NOOB_WIDTH / NOOB_SCALE, NOOB_HEIGHT / NOOB_SCALE);
		SetLifeBarSize(NOOB_WIDTH / NOOB_SCALE, NOOB_WIDTH / NOOB_SCALE / 12);
		break;

	case WARRIOR:
		SetTexture(WARRIOR_TEXTURE);
		SetMaxLife(static_cast<size_t>(WARRIOR_LIFE * (1 + GetGameInfo()->GetStage() * 0.5)));
		SetLife(static_cast<int>(WARRIOR_LIFE * (1 + GetGameInfo()->GetStage() * 0.5)));
		SetSpeed(static_cast<float>(WARRIOR_SPEED + GetGameInfo()->GetStage() * 2));
		SetAttack(WARRIOR_ATTACK);
		SetSize(WARRIOR_WIDTH / WARRIOR_SCALE, WARRIOR_HEIGHT / WARRIOR_SCALE);
		SetLifeBarSize(WARRIOR_WIDTH / WARRIOR_SCALE, WARRIOR_WIDTH / WARRIOR_SCALE / 12);
		break;

	case DOC:
		SetTexture(DOC_TEXTURE);
		SetMaxLife(static_cast<size_t>(DOC_LIFE * ( 1 + GetGameInfo()->GetStage() * 0.8)));
		SetLife(static_cast<int>(DOC_LIFE * (1 + GetGameInfo()->GetStage() * 0.8)));
		SetSpeed(static_cast<float>(DOC_SPEED + GetGameInfo()->GetStage() * 2));
		SetAttack(DOC_ATTACK);
		SetHealPower(DOC_HEALING_POWER);
		SetHealingRange(DOC_HEALING_RANGE + GetGameInfo()->GetStage() * 15);
		SetSize(DOC_WIDTH / DOC_SCALE, DOC_HEIGHT / DOC_SCALE);
		SetLifeBarSize(DOC_WIDTH / DOC_SCALE, DOC_WIDTH / DOC_SCALE / 12);
		break;
	}

	SetMaxSpeed(GetSpeed());

	if (rand() % 10 + 1 == 10)
	{
		switch (rand() % 5)
		{
		default:
		case 0: Enemy::Say("HELLO THERE", 50); break;
		case 1: Enemy::Say("I'M ALIVE!", 50); break;
		case 2: Enemy::Say("HI BOYS", 50); break;
		case 3: Enemy::Say("HERE I AM", 50); break;
		case 4: Enemy::Say("READY TO FIGHT!", 50); break;
		case 5: Enemy::Say("I'M SO UGLY", 50); break;
		}
	}
}

Enemy::~Enemy()
{
	if (GetSpeakTexture())
		SDL_DestroyTexture(GetSpeakTexture());

	if (GetCurrentLifebarTexture())
		SDL_DestroyTexture(GetCurrentLifebarTexture());

	if (GetSpeakTexture())
		SDL_DestroyTexture(GetSpeakTexture());
}

void Enemy::SetLife(const int p_life)
{
	if (p_life <= 0)
	{
		switch (rand() % 5)
		{
		default:
		case 0: Destroy("Report you"); break;
		case 1: Destroy("RIP me"); break;
		case 2: Destroy("So weak"); break;
		case 3: Destroy("AAAARGH..."); break;
		case 4: Destroy("See you in hell"); break;
		case 5: Destroy("Nerf please!"); break;
		}
	}
	else if (p_life > static_cast<int>(GetMaxLife()))
		m_currentLife = GetMaxLife();
	else
		m_currentLife = p_life;
}

void Enemy::SetLifeBarSize(const int p_width, const int p_height)
{
	GetLifeBarSize().X() = p_width;
	GetLifeBarSize().Y() = p_height;
}

void Enemy::SetInvincible(const bool p_value)
{
	m_isInvincible = p_value;

	SetHoverable(p_value);
	SetClickable(p_value);
}

void Enemy::ReceiveDamages(const int p_value, const bool p_isCrit)
{
	m_lastHitWasCrit = p_isCrit;

	SetTimeSinceLastHit(0);

	if (IsInvincible())
	{
		m_lastHitWasBlocked = true;

		GetGameInfo()->GetAudioManager()->PlaySound(SHIELD_BLOCK_SOUND_PATH);
		if (CanTalk() && rand() % 10 + 1 == 1)
		{
			switch (rand() % 5)
			{
			default:
			case 0:
			case 1:
			case 2: Say("Don't click it!", 50); break;
			case 3: Say("Learn to play noob!", 50); break;
			case 4: Say("OP Shield!", 50); break;
			case 5: Say("So easy!", 50); break;
			}
		}
	}
	else
	{
		m_lastHitWasBlocked = false;

		if (p_value >= static_cast<int>(GetLife()))
			SetLife(0);
		else
			SetLife(GetLife() - p_value);

		m_lastHitDamages = p_value;

		if (p_isCrit)
		{
			Say("OP critical strike", 50);
		}
		else
		{

			if (IsSlow())
			{
				if (CanTalk() && rand() % 10 + 1 == 1)
				{
					switch (rand() % 5)
					{
					default:
					case 0: Say("That slow -_-", 50); break;
					case 1: Say("So fuckin' OP!", 50); break;
					case 2: Say("GTFO noob!", 50); break;
					case 3: Say("I'm a turtle", 50); break;
					case 4: Say("WTF, I'm blue ?!", 50); break;
					case 5: Say("So boring slow...", 50); break;
					}
				}
			}
			else
			{
				if (CanTalk() && rand() % 10 + 1 == 1)
				{
					switch (rand() % 5)
					{
					default:
					case 0: Say("Stop shooting me!", 50); break;
					case 1: Say("Fuck, it hurts!", 50); break;
					case 2: Say("Please stop!", 50); break;
					case 3: Say("This game sucks.", 50); break;
					case 4: Say("Ouch!", 50); break;
					case 5: Say("Daaaamn!", 50); break;
					}
				}
			}
		}
	}
}

void Enemy::FollowPath()
{
	if (GetMiddle().X() >= 632 && GetMiddle().X() <= 700 && GetDirection().X() == 1)
		SetDirection(0, -1);

	if (GetMiddle().Y() <= 310 && GetMiddle().Y() >= 150 && GetDirection().Y() == -1)
		SetDirection(1, 0);

	if (GetMiddle().X() >= 1130 && GetMiddle().X() <= 1230 && GetDirection().X() == 1)
		SetDirection(0, 1);

	if (GetMiddle().Y() >= 900 && GetMiddle().Y() <= 950 && GetDirection().Y() == 1)
		SetDirection(1, 0);

	if (GetMiddle().X() >= 1625 && GetMiddle().X() <= 1700 && GetDirection().X() == 1)
		SetDirection(0, -1);

	if (GetMiddle().Y() <= 610 && GetMiddle().X() > 1500 && GetDirection().Y() == -1)
	{
		GetGameInfo()->RemoveCastleLife(static_cast<int>(static_cast<float>(GetAttack()) * static_cast<float>(GetLife()) / static_cast<float>(GetMaxLife())));
		GetGameInfo()->GetAudioManager()->PlaySound(INTO_CASTLE_SOUND_PATH);
		SetUpdatable(false);
		SetLifeTime(0);
	}
}

void Enemy::Slow(const int p_duration)
{
	SetSlow(true);
	SetSlowDuration(p_duration);
}

void Enemy::Heal()
{
	size_t enemyHealed = 0;

	for (auto it = GetEnemyList()->begin(); it != GetEnemyList()->end(); ++it)
		if ((*it)->IsHealable() && (*it)->IsAlive() && (*it)->IsUpdatable())
			if (*it != this)
				if (GetMiddle().DistanceTo((*it)->GetMiddle()) <= static_cast<int>(GetHealingRange()) && (*it)->GetLife() < (*it)->GetMaxLife())
				{
					(*it)->AddLife(DOC_HEALING_POWER);
					++enemyHealed;
				}

	if (enemyHealed > 0)
		Say("Healing " + std::to_string(enemyHealed) + " buds!", 50);
	else
	{
		if (GetLife() < GetMaxLife())
		{
			Say("Healing myself", 50);
			AddLife(DOC_HEALING_POWER);
		}
	}
}

void Enemy::Say(const std::string p_toSay, const int p_messageLifetime, const bool p_sayInRed)
{
	Actor::Say(p_toSay, p_messageLifetime, p_sayInRed);

	SetSayCooldown(ENEMY_SAY_COOLDOWN);
}

void Enemy::Display()
{
	Actor::Display();

	if (IsAlive())
	{
		GetMaxLifeBar().x = GetHitbox().x - (ENEMY_LIFEBAR_WIDTH / 2 - GetHitbox().w / 2);
		GetMaxLifeBar().y = GetHitbox().y - 20;
		GetMaxLifeBar().w = ENEMY_LIFEBAR_WIDTH;
		GetMaxLifeBar().h = ENEMY_LIFEBAR_HEIGHT;

		GetCurrentLifebarRect().x = GetHitbox().x - (ENEMY_LIFEBAR_WIDTH / 2 - GetHitbox().w / 2);
		GetCurrentLifebarRect().y = GetHitbox().y - 20;
		GetCurrentLifebarRect().w = static_cast<int>(static_cast<float>(GetLife()) / static_cast<float>(GetMaxLife()) * ENEMY_LIFEBAR_WIDTH);
		GetCurrentLifebarRect().h = ENEMY_LIFEBAR_HEIGHT;

		SDL_SetRenderDrawColor(GetWindow()->GetRenderer(), 255, 255, 255, 100);
		SDL_RenderFillRect(GetWindow()->GetRenderer(), &GetMaxLifeBar());
		SDL_RenderCopy(GetWindow()->GetRenderer(), GetCurrentLifebarTexture(), nullptr, &GetCurrentLifebarRect());

		if (IsInvincible())
		{
			GetShieldRect().x = GetHitbox().x - 20;
			GetShieldRect().y = GetHitbox().y + 20;
			SDL_RenderCopy(GetWindow()->GetRenderer(), GetShieldTexture(), nullptr, &GetShieldRect());
		}
	}

	if (GetTimeSinceLastHit() >= 0 && GetTimeSinceLastHit() <= 30)
	{
		if (m_lastHitWasBlocked)
			GetUserInterface()->SetCurrentColor(255, 255, 255);
		else if (m_lastHitWasCrit)
			GetUserInterface()->SetCurrentColor(255, 255, 0);
		else
			GetUserInterface()->SetCurrentColor(255, 0, 0);

		GetUserInterface()->SetCurrentFont(FANCY_FONT);
		GetUserInterface()->SetAlign(ALIGN_CENTER);

		const int x = GetMaxLifeBar().x + GetMaxLifeBar().w / 2;
		const int y = GetMaxLifeBar().y - 10 - GetTimeSinceLastHit() * 2;

		if (m_lastHitWasBlocked)
			GetUserInterface()->ShowText("BLOCKED", x, y);
		else
			GetUserInterface()->ShowText("-" + std::to_string(m_lastHitDamages) + " HP", x, y);
	}
}

void Enemy::Tick()
{
	UnHighlight(GetShieldTexture());
	DecrementSayCooldown();
	IncrementTimeSinceLastHit();

	if (rand() % 1000 + 1 == 1)
		GetGameInfo()->GetAudioManager()->PlayRandomMonsterVoice();

	if (IsAlive())
	{
		if (YouSeeMeRolling())
			SetRotationAngle(GetRotationAngle() + GetRollingInc() * GetGameInfo()->GetDeltaTime());

		if (IsSlow())
			SDL_SetTextureColorMod(m_texture, 51, 153, 255);
		else
			SDL_SetTextureColorMod(m_texture, 255, 255, 255);

		SDL_SetTextureColorMod(GetShieldTexture(), 255, 255, 255);
		
		if (GetTimeSinceLastHit() >= 0 && GetTimeSinceLastHit() < 10)
		{
			if (!m_lastHitWasBlocked)
			{
				if (m_lastHitWasCrit)
					SDL_SetTextureColorMod(m_texture, 255, 255, 0);
				else
					SDL_SetTextureColorMod(m_texture, 255, 0, 0);
			}
			else
			{
				SDL_SetTextureColorMod(GetShieldTexture(), 0, 255, 0);
			}
		}

		if (GetSlowDuration() > 0)
			SetSlowDuration(GetSlowDuration() - 1);

		if (!GetSlowDuration() && IsSlow())
		{
			SetSlow(false);
		}

		FollowPath();

		if (GetType() == DOC && CanHeal())
			Heal();
	}
	else
	{
		SetTimeSinceDeath(GetTimeSinceDeath() + 1);

		if (GetTimeSinceDeath() == 1)
		{
			m_backupPos.X() = static_cast<float>(GetHitbox().x);
			m_backupPos.Y() = static_cast<float>(GetHitbox().y);
		}

		if (GetTimeSinceDeath() > 1 && GetTimeSinceDeath() < 50)
		{
			SDL_SetTextureAlphaMod(m_texture, static_cast<Uint8>(255 - GetTimeSinceDeath() * 5));
			SetRotationAngle(GetRotationAngle() + 100 * GetGameInfo()->GetDeltaTime());
		}

		if (GetTimeSinceDeath() == 50)
		{
			GetHitbox().x = static_cast<int>(m_backupPos.X());
			GetHitbox().y = static_cast<int>(m_backupPos.Y());

			switch (GetType())
			{
			default:
			case EnemyType::NOOB:
				SetTexture(NOOB_DEATH_TEXTURE);
				SetSize(static_cast<int>(NOOB_DEATH_TEXTURE_WIDTH / NOOB_DEATH_TEXTURE_SCALE), static_cast<int>(NOOB_DEATH_TEXTURE_HEIGHT / NOOB_DEATH_TEXTURE_SCALE));
				SetPosition(static_cast<float>(GetMiddle().X() - NOOB_DEATH_TEXTURE_WIDTH / NOOB_DEATH_TEXTURE_SCALE / 2), static_cast<float>(GetMiddle().Y() - NOOB_DEATH_TEXTURE_HEIGHT / NOOB_DEATH_TEXTURE_SCALE / 2));
				break;

			case EnemyType::WARRIOR:
				SetTexture(WARRIOR_DEATH_TEXTURE);
				SetSize(static_cast<int>(WARRIOR_DEATH_TEXTURE_WIDTH / WARRIOR_DEATH_TEXTURE_SCALE), static_cast<int>(WARRIOR_DEATH_TEXTURE_HEIGHT / WARRIOR_DEATH_TEXTURE_SCALE));
				SetPosition(static_cast<float>(GetMiddle().X() - WARRIOR_DEATH_TEXTURE_WIDTH / WARRIOR_DEATH_TEXTURE_SCALE / 2), static_cast<float>(GetMiddle().Y() - WARRIOR_DEATH_TEXTURE_HEIGHT / WARRIOR_DEATH_TEXTURE_SCALE / 2));
				break;

			case EnemyType::DOC:
				SetTexture(DOC_DEATH_TEXTURE);
				SetSize(static_cast<int>(DOC_DEATH_TEXTURE_WIDTH / DOC_DEATH_TEXTURE_SCALE), static_cast<int>(DOC_DEATH_TEXTURE_HEIGHT / DOC_DEATH_TEXTURE_SCALE));
				SetPosition(static_cast<float>(GetMiddle().X() - DOC_DEATH_TEXTURE_WIDTH / DOC_DEATH_TEXTURE_SCALE / 2), static_cast<float>(GetMiddle().Y() - DOC_DEATH_TEXTURE_HEIGHT / DOC_DEATH_TEXTURE_SCALE / 2));
				break;
			}

			SetRotationAngle(0);
		}

		if (GetTimeSinceDeath() >= 50 && GetTimeSinceDeath() <= 100)
			SDL_SetTextureAlphaMod(m_texture, static_cast<Uint8>((GetTimeSinceDeath() - 50) * 5));
	}
}

void Enemy::Move(const float p_x, const float p_y)
{
	if (IsSlow())
		SetSpeed(static_cast<float>(GetMaxSpeed() * ENEMY_SLOW_MULTIPLICATOR));
	else
		SetSpeed(GetMaxSpeed());

	if (GetType() == EnemyType::DOC && !IsSlow())
	{
		for (auto it = GetEnemyList()->begin(); it != GetEnemyList()->end(); ++it)
		{
			if ((*it)->IsUpdatable() && (*it)->IsAlive() && GetMiddle().DistanceTo((*it)->GetMiddle()) < 65)
			{
				if ((*it)->GetDistanceTraveled() > GetDistanceTraveled())
				{
					SetSpeed((*it)->GetSpeed());
				}
			}
		}
	}

	Actor::Move(p_x, p_y);
}

void Enemy::Destroy(const std::string p_message)
{
	if (IsAlive())
	{
		m_currentLife = 0;

		if (p_message != "")
			Say(p_message);

		std::cout << "An enemy died" << std::endl;
		GetGameInfo()->IncrementKilledEnemies();

		SetLifeTime(0);
		SetMovable(false);
		GetGameInfo()->AddMoney(ENEMY_GOLD_LOOT);
		GetGameInfo()->GetAudioManager()->PlayRandomDeath();
	}
}

void Enemy::OnMouseOver()
{
	Highlight(GetShieldTexture());
	GetUserInterface()->SetCursor(CursorType::CURSOR_HOVER);
}

void Enemy::OnClick()
{
	GetGameInfo()->GetAudioManager()->PlaySound(BREAK_SHIELD_SOUND_PATH);
	SetInvincible(false);
}
