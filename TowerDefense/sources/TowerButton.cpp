#include "TowerButton.h"

TowerButton::TowerButton(Window* p_window, GameInfo* p_gameInfo, const uint8_t p_type, const float p_x, const float p_y) : Actor(p_window, p_gameInfo, p_x, p_y)
{
	SetClickable(true);
	SetHoverable(true);

	SetBaseAlpha(BUTTON_BASE_ALPHA);
	SetHoverAlpha(BUTTON_HOVER_ALPHA);

	UnHighlight();

	SetSize(BUTTON_X_SIZE, BUTTON_Y_SIZE);

	SetType(p_type);

	switch (GetType())
	{
	default:
	case TowerType::CASTLE_TOWER:
		SetTexture(CASTLE_TOWER_PATH);
		SetPosition(CASTLE_TOWER_X_POS, CASTLE_TOWER_Y_POS);
		break;

	case TowerType::ARCHER_TOWER:
		SetTexture(ARCHER_TOWER_PATH);
		SetPosition(ARCHER_TOWER_X_POS, ARCHER_TOWER_Y_POS);
		break;
	}

	m_rotateIncrement = 0.2f;
}

void TowerButton::Tick()
{
	Actor::Tick();

	if (GetGameInfo()->GetSelectedTower() == GetType())
	{
		Highlight();
	}

	m_rotationAngle += m_rotateIncrement;

	if (m_rotationAngle >= 8 || m_rotationAngle <= -8)
	{
		m_rotateIncrement = -m_rotateIncrement;
	}
}

void TowerButton::OnMouseOver()
{
	Actor::OnMouseOver();

	std::string towerHeader = "";
	std::string towerDescription1 = "";
	std::string towerDescription2 = "";
	std::string towerDescription3 = "";
	std::string towerDescription4 = "";
	std::string towerDescription5 = "";
	std::string towerDescription6 = "";
	std::string towerDescription7 = "";
	std::string towerDescription8 = "";
	std::string towerPrice;

	towerDescription6 = "Range: ";
	towerDescription7 = "Damages: ";
	towerDescription8 = "Reload time: ";

	switch (GetType())
	{
	default:
	case TowerType::CASTLE_TOWER:
		towerHeader = "CASTLE TOWER";
		towerDescription1 = "A classic stone tower";
		towerDescription2 = "with a low speed but";
		towerDescription3 = "great damages.";
		towerDescription5 = "";
		towerDescription6 += std::to_string(CASTLE_TOWER_RANGE);
		towerDescription7 += std::to_string(CASTLE_TOWER_DAMAGES);
		towerDescription8 += to_string_with_precision(std::floor(CASTLE_TOWER_COOLDOWN / 60.f * 100 + 0.5) / 100, 2) + "s";
		towerPrice = "Price: " + std::to_string(CASTLE_TOWER_COST) + "$";
		break;

	case TowerType::ARCHER_TOWER:
		towerHeader = "ARCHER TOWER";
		towerDescription1 = "This tower is very fast";
		towerDescription2 = "and her range is great.";
		towerDescription3 = "She slows enemies";
		towerDescription4 = "when hitting them.";
		towerDescription5 = "";
		towerDescription6 += std::to_string(ARCHER_TOWER_RANGE);
		towerDescription7 += std::to_string(ARCHER_TOWER_DAMAGES);
		towerDescription8 += to_string_with_precision(std::floor(ARCHER_TOWER_COOLDOWN / 60.f * 100 + 0.5) / 100, 2) + "s";
		towerPrice = "Price: " + std::to_string(ARCHER_TOWER_COST) + "$";
		break;
	}

	GetUserInterface()->SetTowerInfo();
	GetUserInterface()->SetAlign(ALIGN_LEFT);
	GetUserInterface()->SetCurrentColor(255, 255, 0);
	GetUserInterface()->SetCurrentFont(FontType::HUD_FONT);
	GetUserInterface()->ShowText(towerHeader, 10, 190);
	GetUserInterface()->SetCurrentColor(255, 255, 255);
	GetUserInterface()->SetCurrentFont(FontType::SMALL_FONT);
	GetUserInterface()->SetCurrentColor(255, 255, 255);
	GetUserInterface()->ShowText(towerDescription1, 10, 230);
	GetUserInterface()->ShowText(towerDescription2, 10, 255);
	GetUserInterface()->ShowText(towerDescription3, 10, 280);
	GetUserInterface()->ShowText(towerDescription4, 10, 305);
	GetUserInterface()->ShowText(towerDescription5, 10, 330);
	GetUserInterface()->SetCurrentColor(51, 153, 255);
	GetUserInterface()->ShowText(towerDescription6, 10, 355);
	GetUserInterface()->ShowText(towerDescription7, 10, 380);
	GetUserInterface()->ShowText(towerDescription8, 10, 405);
	GetUserInterface()->SetCurrentColor(255, 255, 0);
	GetUserInterface()->ShowText(towerPrice, 10, 450);
}

void TowerButton::OnClick()
{
	Actor::OnClick();

	GetGameInfo()->SetSelectedTower(m_type);
	GetGameInfo()->GetAudioManager()->PlaySound(CLICK_SOUND_PATH);
}
