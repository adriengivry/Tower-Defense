#include "Slot.h"

Slot::Slot(Window* p_window, GameInfo* p_gameInfo) : Actor(p_window, p_gameInfo)
{
	SetTexture(SLOT_TEXTURE);
	SetSize(SLOT_WIDTH / SLOT_SCALE, SLOT_HEIGHT / SLOT_SCALE);
	SetTower(nullptr);
	SetClickable(true);
	SetHoverable(true);
	SetMessageOffset(0);
}

bool Slot::CanCreateTower() const
{
	return GetGameInfo()->GetMoney() >= GetTowerCost() && !GetTower();
}

void Slot::AddTower()
{
	if (!GetTower())
	{
		Tower* toAdd = new Tower(GetWindow(), nullptr, GetGameInfo()->GetSelectedTower(), static_cast<float>(GetHitbox().x - 20), static_cast<float>(GetHitbox().y - 75));
		toAdd->SetEnemyList(GetEnemyList());
		toAdd->SetUserInterface(GetUserInterface());
		toAdd->SetGameInfo(GetGameInfo());
		toAdd->SetProjectileList(GetProjectileList());
		toAdd->SetDisplayable(true);
		toAdd->Say("Created (-" + std::to_string(GetTowerCost()) + "$)", 100);
		GetTowerList()->push_back(toAdd);
		SetTower(toAdd);

		if (GetGameInfo()->GetSelectedTower() == 0)
			GetGameInfo()->GetAudioManager()->PlaySound(CASTLE_TOWER_CREATE_SOUND_PATH);
		if (GetGameInfo()->GetSelectedTower() == 1)
			GetGameInfo()->GetAudioManager()->PlaySound(ARCHER_TOWER_CREATE_SOUND_PATH);
	}
}

void Slot::RemoveTower()
{
	if (GetTower())
	{
		int moneyToAdd = 0;

		switch(GetTower()->GetType())
		{
		default:
		case TowerType::CASTLE_TOWER:
			moneyToAdd = CASTLE_TOWER_COST;
			break;

		case TowerType::ARCHER_TOWER:
			moneyToAdd = ARCHER_TOWER_COST;
			break;
		}

		moneyToAdd /= 2;

		GetTower()->Destroy();
		SetTower(nullptr);
		SetHoverable(true);
		SetClickable(true);
		GetGameInfo()->GetAudioManager()->PlaySound(DESTROY_TOWER_SOUND_PATH);
		GetGameInfo()->AddMoney(moneyToAdd);
		Say("Deleted (+" + std::to_string(moneyToAdd) + "$)", 100);
	}
}

void Slot::Display()
{
	Actor::Display();
}

int Slot::GetTowerCost() const
{
	int towerCost = 0;

	if (GetGameInfo()->GetSelectedTower() == 0)
		towerCost = CASTLE_TOWER_COST;
	if (GetGameInfo()->GetSelectedTower() == 1)
		towerCost = ARCHER_TOWER_COST;

	return towerCost;
}

void Slot::OnMouseOver()
{
	Actor::OnMouseOver();

	if (!CanCreateTower())
		GetUserInterface()->SetCursor(CursorType::CURSOR_ERROR);

	GetUserInterface()->SetTowerInfo();
	GetUserInterface()->SetAlign(ALIGN_LEFT);
	GetUserInterface()->SetCurrentColor(255, 255, 0);
	GetUserInterface()->SetCurrentFont(FontType::HUD_FONT);
	GetUserInterface()->ShowText("EMPTY SLOT", 10, 190);
	GetUserInterface()->SetCurrentColor(255, 255, 255);
	GetUserInterface()->SetCurrentFont(FontType::SMALL_FONT);
	GetUserInterface()->SetCurrentColor(255, 255, 255);
	GetUserInterface()->ShowText("This is a cool place to", 10, 230);
	GetUserInterface()->ShowText("put a tower !", 10, 255);
	GetUserInterface()->SetCurrentColor(255, 255, 0);
	GetUserInterface()->ShowText("Place your selected", 10, 425);
	GetUserInterface()->ShowText("tower for only " + std::to_string(GetTowerCost()) + "$", 10, 450);

	int rangeToShow = 0;

	if (GetGameInfo()->GetSelectedTower() == TowerType::CASTLE_TOWER)
	{
		rangeToShow = CASTLE_TOWER_RANGE;
	}
	else if (GetGameInfo()->GetSelectedTower() == TowerType::ARCHER_TOWER)
	{
		rangeToShow = ARCHER_TOWER_RANGE;
	}

	GetUserInterface()->SetShowTowerRange(true);
	GetUserInterface()->GetTowerRangeRect().w = rangeToShow * 2;
	GetUserInterface()->GetTowerRangeRect().h = rangeToShow * 2;
	GetUserInterface()->GetTowerRangeRect().x = GetMiddle().X() - GetUserInterface()->GetTowerRangeRect().w / 2;
	GetUserInterface()->GetTowerRangeRect().y = GetMiddle().Y() - GetUserInterface()->GetTowerRangeRect().h / 2 - 54;
}

void Slot::OnClick()
{
	Actor::OnClick();

	if (CanCreateTower())
	{
		GetGameInfo()->AddMoney(-GetTowerCost());
		SetClickable(false);
		SetHoverable(false);
		AddTower();
	}
	else
	{
		Say(std::to_string(GetTowerCost()) + "$ needed", 100, true);
		GetGameInfo()->GetAudioManager()->PlaySound(ERROR_SOUND_PATH);
	}

}

void Slot::Tick()
{
	Actor::Tick();

	if (GetTower() && GetTower()->MustBeRemoved())
	{
		RemoveTower();
	}
}
