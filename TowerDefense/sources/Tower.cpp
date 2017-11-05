#include "Tower.h"
#include <algorithm>
#include "TowerButton.h"

Tower::Tower(Window* p_window, GameInfo* p_gameInfo, const uint8_t p_towerType, const float p_x, const float p_y): Actor(p_window, p_gameInfo, p_x, p_y)
{
	SetClickable(true);
	SetHoverable(true);

	SetLevel(1);
	SetCurrentCooldown(0);
	SetMessageOffset(-15);
	SetType(p_towerType);
	SetMustBeRemoved(false);

	SetLevelBackgroundTexture(IMG_LoadTexture(GetWindow()->GetRenderer(), TOWER_LEVEL_BACKGROUND_TEXTURE));

	switch (GetType())
	{
	default:
	case CASTLE_TOWER:
		SetTexture(CASTLE_TOWER_TEXTURE);
		SetSize(static_cast<int>(CASTLE_TOWER_WIDTH / CASTLE_TOWER_SCALE), static_cast<int>(CASTLE_TOWER_HEIGHT / CASTLE_TOWER_SCALE));
		SetRange(CASTLE_TOWER_RANGE);
		SetMaxCooldown(CASTLE_TOWER_COOLDOWN);
		SetDamages(CASTLE_TOWER_DAMAGES);
		SetCriticalRate(CASTLE_TOWER_CRITICAL_RATE);
		SetUpgradeCost(CASTLE_TOWER_UPGRADE_COST);
		SetRangeToAdd(CASTLE_TOWER_RANGE_UPGRADE);
		SetDamageToAdd(CASTLE_TOWER_DAMAGES_UPGRADE);
		break;
	case ARCHER_TOWER:
		SetTexture(ARCHER_TOWER_TEXTURE);
		SetSize(static_cast<int>(ARCHER_TOWER_WIDTH / ARCHER_TOWER_SCALE), static_cast<int>(ARCHER_TOWER_HEIGHT / ARCHER_TOWER_SCALE));
		SetRange(ARCHER_TOWER_RANGE);
		SetMaxCooldown(ARCHER_TOWER_COOLDOWN);
		SetDamages(ARCHER_TOWER_DAMAGES);
		SetCriticalRate(ARCHER_TOWER_CRITICAL_RATE);
		SetUpgradeCost(ARCHER_TOWER_UPGRADE_COST);
		SetRangeToAdd(ARCHER_TOWER_RANGE_UPGRADE);
		SetDamageToAdd(ARCHER_TOWER_DAMAGES_UPGRADE);
		break;
	}
}

void Tower::Update(EventManager& p_eventManager)
{
	Actor::Update(p_eventManager);
}

void Tower::Display()
{
	Actor::Display();

	GetLevelBackgroundRect().w = TOWER_LEVEL_BACKGROUND_WIDTH / TOWER_LEVEL_BACKGROUND_SCALE;
	GetLevelBackgroundRect().h = TOWER_LEVEL_BACKGROUND_HEIGHT / TOWER_LEVEL_BACKGROUND_SCALE;
	GetLevelBackgroundRect().x = GetHitbox().x + GetHitbox().w / 2 - GetLevelBackgroundRect().w / 2;
	GetLevelBackgroundRect().y = GetHitbox().y + GetHitbox().h + TOWER_LEVEL_BACKGROUND_Y_OFFSET;

	if (GetType() == TowerType::ARCHER_TOWER)
		SDL_SetTextureColorMod(GetLevelBackgroundTexture(), 102, 51, 0);
	SDL_RenderCopy(GetWindow()->GetRenderer(), GetLevelBackgroundTexture(), nullptr, &GetLevelBackgroundRect());

	Vector2D<int> shieldCenter;
	shieldCenter.X() = GetLevelBackgroundRect().x + GetLevelBackgroundRect().w / 2;
	shieldCenter.Y() = GetLevelBackgroundRect().y + GetLevelBackgroundRect().h / 2;

	GetUserInterface()->SetAlign(TextProperty::ALIGN_CENTER);
	GetUserInterface()->SetCurrentColor(255,255,255);
	GetUserInterface()->SetCurrentFont(FontType::FANCY_FONT);
	GetUserInterface()->ShowText(std::to_string(GetLevel()), shieldCenter.X(), shieldCenter.Y());
}

bool Tower::CanGetUpgraded() const
{
	return GetGameInfo()->GetMoney() >= GetUpgradeCost();
}

void Tower::Shoot(Enemy* p_target)
{
	SetCurrentCooldown(GetCooldown());

	Projectile* projectile = new Projectile(GetWindow(), static_cast<float>(GetMiddle().X() - 5), static_cast<float>(GetMiddle().Y() - 5), GetDamages(), GetCriticalRate(), GetType());
	projectile->SetTargetToFollow(p_target);
	projectile->SetGameInfo(GetGameInfo());

	GetProjectileList()->push_back(projectile);
}

void Tower::SetTowerInfoToConsole() const
{
	const std::string towerHeader = "TOWER LVL." + std::to_string(GetLevel());
	const std::string towerRange = "Range: " + std::to_string(GetRange());
	const std::string towerDamages = "Damages: " + std::to_string(GetDamages());
	const std::string towerCooldown = "Reload time: " + to_string_with_precision(std::floor(GetCooldown() / 60.f * 100 + 0.5) / 100, 2) + "s";
	const std::string lineBreak = "";
	const std::string towerUpgradeCost = "Upgrade for " + std::to_string(GetUpgradeCost()) + "$";
	const std::string towerUpgradeRange = "+" + std::to_string(GetRangeToAdd()) + " range";
	const std::string towerUpgradeDamages = "+" + std::to_string(GetDamageToAdd()) + " damages";

	GetUserInterface()->SetTowerInfo(
		towerHeader,
		towerRange,
		towerDamages,
		towerCooldown,
		lineBreak,
		towerUpgradeCost,
		towerUpgradeRange,
		towerUpgradeDamages);
}

void Tower::Upgrade()
{
	GetGameInfo()->AddMoney(-GetUpgradeCost());
	Say("Upgraded (-" + std::to_string(GetUpgradeCost()) + "$)", 100);

	switch (GetType())
	{
	default:
	case TowerType::CASTLE_TOWER:
		GetGameInfo()->GetAudioManager()->PlaySound(CASTLE_TOWER_UPGRADE_SOUND);
		break;

	case TowerType::ARCHER_TOWER:
		GetGameInfo()->GetAudioManager()->PlaySound(ARCHER_TOWER_UPGRADE_SOUND);
		break;
	}

	AddLevel(1);
	AddRange(GetRangeToAdd());
	AddDamages(GetDamageToAdd());
}

void Tower::UpdateShootCooldown()
{
	SetCurrentCooldown(static_cast<int>(GetCurrentCooldown() - GetGameInfo()->GetDeltaTime()));
}

void Tower::Tick()
{
	Actor::Tick();

	UpdateShootCooldown();

	std::map<float, Enemy*> m_targetableEnemies;

	for (auto iterator = GetEnemyList()->begin(); iterator != GetEnemyList()->end(); ++iterator)
	{
		Enemy* target = *iterator;
		if (target->IsUpdatable() && target->IsAlive() && target->IsAttackable())
			if (GetMiddle().DistanceTo(target->GetMiddle()) <= static_cast<int>(GetRange()) && CanShoot())
				m_targetableEnemies.insert(std::pair<float, Enemy*>(1000000 - target->GetDistanceTraveled(), target));
	}

	if (!m_targetableEnemies.empty())
	{
		Shoot(m_targetableEnemies.begin()->second);
		GetGameInfo()->GetAudioManager()->PlayRandomShot();
	}
}

void Tower::OnMouseOver()
{
	Actor::OnMouseOver();

	if (!CanGetUpgraded())
		GetUserInterface()->SetCursor(CursorType::CURSOR_ERROR);

	SetTowerInfoToConsole();

	GetUserInterface()->SetShowTowerRange(true);
	GetUserInterface()->GetTowerRangeRect().w = GetRange() * 2;
	GetUserInterface()->GetTowerRangeRect().h = GetRange() * 2;
	GetUserInterface()->GetTowerRangeRect().x = GetMiddle().X() - GetUserInterface()->GetTowerRangeRect().w / 2;
	GetUserInterface()->GetTowerRangeRect().y = GetMiddle().Y() - GetUserInterface()->GetTowerRangeRect().h / 2;
}

void Tower::OnClick()
{
	Actor::OnClick();

	if (CanGetUpgraded())
		Upgrade();
	else
	{
		Say(std::to_string(GetUpgradeCost()) + "$ needed", 100, true);
		GetGameInfo()->GetAudioManager()->PlaySound(ERROR_SOUND_PATH);
	}
}

void Tower::OnRightClick()
{
	Actor::OnRightClick();

	SetMustBeRemoved(true);
}
