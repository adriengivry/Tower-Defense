#include "UserInterface.h"
#include "SDLManager.h"
#include "Tower.h"
#include "TowerButton.h"

UserInterface::UserInterface(Window* p_window, GameInfo* p_gameInfo)
{
	m_gameInfo = p_gameInfo;
	m_window = p_window;

	m_fancyFont = TTF_OpenFont(FANCY_FONT_PATH, 22);
	m_smallFont = TTF_OpenFont(BOLD_FONT_PATH, 18);
	m_tooltipFont = TTF_OpenFont(BOLD_FONT_PATH, 24);
	m_hudFont = TTF_OpenFont(BOLD_FONT_PATH, 24);
	m_normalFont = TTF_OpenFont(FANCY_FONT_PATH, 30);
	m_bigFont = TTF_OpenFont(FANCY_FONT_PATH, 50);
	m_bubbleFont = TTF_OpenFont(BUBBLE_FONT_PATH, 22);

	SetCurrentColor(255, 255, 255);
	SetCurrentFont(NORMAL_FONT);

	GetImportantMessageBackground().w = IMPORTANT_MESSAGE_WIDTH / IMPORTANT_MESSAGE_SCALE;
	GetImportantMessageBackground().h = IMPORTANT_MESSAGE_HEIGHT / IMPORTANT_MESSAGE_SCALE;
	GetImportantMessageBackground().x = IMPORTANT_MESSAGE_X_POS;
	GetImportantMessageBackground().y = IMPORTANT_MESSAGE_Y_POS - (GetImportantMessageBackground().h / 2 - 25);

	for (int i = 0; i < 10; ++i)
	{
		m_consoleLine[i] = "";
	}

	GetCastleLifebarRect().x = LIFEBAR_X_POS;
	GetCastleLifebarRect().y = LIFEBAR_Y_POS;
	GetCastleLifebarRect().w = LIFEBAR_WIDTH / LIFEBAR_SCALE;
	GetCastleLifebarRect().h = LIFEBAR_HEIGHT / LIFEBAR_SCALE;

	GetTowerSelectorRect().x = SELECTOR_X_POS;
	GetTowerSelectorRect().y = SELECTOR_Y_POS;
	GetTowerSelectorRect().w = SELECTOR_WIDTH / SELECTOR_SCALE;
	GetTowerSelectorRect().h = SELECTOR_HEIGHT / SELECTOR_SCALE;

	GetTimerRect().x = TIMER_X_POS;
	GetTimerRect().y = TIMER_Y_POS;
	GetTimerRect().w = TIMER_WIDTH / TIMER_SCALE;
	GetTimerRect().h = TIMER_HEIGHT / TIMER_SCALE;

	m_castleLifebarTexture = IMG_LoadTexture(GetWindow()->GetRenderer(), LIFEBAR_TEXTURE_PATH);
	m_importantMessageBackgroundTexture = IMG_LoadTexture(GetWindow()->GetRenderer(), IMPORTANT_MESSAGE_TEXTURE_PATH);
	m_towerSelectorTexture = IMG_LoadTexture(GetWindow()->GetRenderer(), SELECTOR_TEXTURE_PATH);
	m_timerTexture = IMG_LoadTexture(GetWindow()->GetRenderer(), TIMER_TEXTURE_PATH);
	m_towerRangeTexture = IMG_LoadTexture(GetWindow()->GetRenderer(), TOWER_RANGE_TEXTURE);

	m_normalCursorTexture = IMG_LoadTexture(GetWindow()->GetRenderer(), CURSOR_NORMAL_TEXTURE_PATH);
	m_hoverCursorTexture = IMG_LoadTexture(GetWindow()->GetRenderer(), CURSOR_HOVER_TEXTURE_PATH);
	m_errorCursorTexture = IMG_LoadTexture(GetWindow()->GetRenderer(), CURSOR_ERROR_TEXTURE_PATH);

	m_waveScoreTexture1 = IMG_LoadTexture(GetWindow()->GetRenderer(), WAVE_SCORE_TEXTURE_1_PATH);
	m_waveScoreTexture2 = IMG_LoadTexture(GetWindow()->GetRenderer(), WAVE_SCORE_TEXTURE_2_PATH);
	m_waveScoreTexture3 = IMG_LoadTexture(GetWindow()->GetRenderer(), WAVE_SCORE_TEXTURE_3_PATH);
	
	m_waveScoreRect.x = WAVE_SCORE_X_POS;
	m_waveScoreRect.y = WAVE_SCORE_Y_POS;
	m_waveScoreRect.w = WAVE_SCORE_WIDTH / WAVE_SCORE_SCALE;
	m_waveScoreRect.h = WAVE_SCORE_HEIGHT / WAVE_SCORE_SCALE;

	SetCursor(CursorType::CURSOR_NORMAL);

	SDL_ShowCursor(false);
}

UserInterface::~UserInterface()
{
	SDL_DestroyTexture(m_castleLifebarTexture);
	SDL_DestroyTexture(m_importantMessageBackgroundTexture);
	SDL_DestroyTexture(m_towerSelectorTexture);
	SDL_DestroyTexture(m_timerTexture);
	SDL_DestroyTexture(m_towerRangeTexture);

	SDL_DestroyTexture(m_normalCursorTexture);
	SDL_DestroyTexture(m_errorCursorTexture);
	SDL_DestroyTexture(m_hoverCursorTexture);

	SDL_DestroyTexture(m_waveScoreTexture1);
	SDL_DestroyTexture(m_waveScoreTexture2);
	SDL_DestroyTexture(m_waveScoreTexture3);

	TTF_CloseFont(m_fancyFont);
	TTF_CloseFont(m_smallFont);
	TTF_CloseFont(m_tooltipFont);
	TTF_CloseFont(m_hudFont);
	TTF_CloseFont(m_normalFont);
	TTF_CloseFont(m_bigFont);
	TTF_CloseFont(m_bubbleFont);
}

void UserInterface::SetCurrentColor(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a)
{
	GetCurrentColor().r = r;
	GetCurrentColor().g = g;
	GetCurrentColor().b = b;
	GetCurrentColor().a = a;
}

void UserInterface::SetCurrentFont(const uint8_t p_font)
{
	switch(p_font)
	{
	default:
	case NORMAL_FONT:
		m_currentFont = m_normalFont;
		break;

	case FANCY_FONT:
		m_currentFont = m_fancyFont;
		break;

	case BIG_FONT:
		m_currentFont = m_bigFont;
		break;

	case SMALL_FONT:
		m_currentFont = m_smallFont;
		break;

	case TOOLTIP_FONT:
		m_currentFont = m_tooltipFont;
		break;

	case HUD_FONT:
		m_currentFont = m_hudFont;
		break;
	case BUBBLE_FONT:
		m_currentFont = m_bubbleFont;
	}
}

void UserInterface::Display()
{

	// DISPLAY TOWER RANGE
	if (MustShowTowerRange())
	{
		SDL_SetTextureAlphaMod(m_towerRangeTexture, RANGE_TO_SHOW_ALPHA);
		SDL_RenderCopy(GetWindow()->GetRenderer(), m_towerRangeTexture, nullptr, &m_towerRangeRect);
	}

	// DISPLAY MONEY
	SetCurrentColor(255, 255, 0);
	SetAlign(ALIGN_CENTER);
	SetCurrentFont(HUD_FONT);
	ShowText(std::to_string(GetGameInfo()->GetMoney()), TEXT_MONEY_X_POS, TEXT_MONEY_Y_POS);

	// DISPLAY STAGE
	SetAlign(ALIGN_CENTER);
	ShowText("Stage: " + std::to_string(GetGameInfo()->GetStage()), TEXT_STAGE_X_POS, TEXT_STAGE_Y_POS);
	
	// DISPLAY CASTLE LIFE
	GetCastleLifebarRect().w = static_cast<int>(static_cast<float>(GetGameInfo()->GetCastleLife()) / GetGameInfo()->GetCastleMaxLife() * LIFEBAR_WANTED_HEIGHT);
	SDL_RenderCopy(GetWindow()->GetRenderer(), m_castleLifebarTexture, nullptr, &GetCastleLifebarRect());

	// DISPLAY TOWER SELECTOR
	if (GetGameInfo()->GetSelectedTower() == TowerType::CASTLE_TOWER)
		if (GetTowerSelectorRect().y > SELECTOR_POSY_1)
			GetTowerSelectorRect().y -= SELECTOR_MOVEMENT_SPEED;
	if (GetGameInfo()->GetSelectedTower() == TowerType::ARCHER_TOWER)
		if (GetTowerSelectorRect().y < SELECTOR_POSY_2)
			GetTowerSelectorRect().y += SELECTOR_MOVEMENT_SPEED;
	SDL_RenderCopy(GetWindow()->GetRenderer(), GetTowerSelectorTexture(), nullptr, &GetTowerSelectorRect());

	// DISPLAY TOWER INFO ON THE LEFT
	ShowTowerInfo();

	// DISPLAY CURSOR
	ShowCursor();
}

void UserInterface::SetCursor(const uint8_t p_type)
{
	switch (p_type)
	{
	default:
	case CursorType::CURSOR_NORMAL:
		SetCursorTexture(m_normalCursorTexture);
		break;

	case CursorType::CURSOR_ERROR:
		SetCursorTexture(m_errorCursorTexture);
		break;

	case CursorType::CURSOR_HOVER:
		SetCursorTexture(m_hoverCursorTexture);
		break;
	}
}

void UserInterface::ShowText(const std::string p_text, const int p_x, const int p_y, const uint8_t p_alpha) const
{
	if (p_text == "")
		return;

	SDL_Surface* surface = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect rect;

	surface = TTF_RenderText_Blended(GetCurrentFont(), p_text.c_str(), GetCurrentColor());

	texture = nullptr;

	rect.x = p_x;
	rect.y = p_y;
	rect.w = surface->w;
	rect.h = surface->h;

	if (GetCurrentAlign() == ALIGN_CENTER)
	{
		rect.x -= rect.w / 2;
		rect.y -= rect.h / 2;
	}

	if (GetCurrentAlign() == ALIGN_RIGHT)
		rect.x -= rect.w;

	texture = SDL_CreateTextureFromSurface(m_window->GetRenderer(), surface);
	SDL_SetTextureAlphaMod(texture, p_alpha);
	SDL_RenderCopy(m_window->GetRenderer(), texture, nullptr, &rect);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

void UserInterface::SetTowerInfo(cstr l1, cstr l2, cstr l3, cstr l4, cstr l5, cstr l6, cstr l7, cstr l8, cstr l9, cstr l10)
{
	m_consoleLine[0] = l1;
	m_consoleLine[1] = l2;
	m_consoleLine[2] = l3;
	m_consoleLine[3] = l4;
	m_consoleLine[4] = l5;
	m_consoleLine[5] = l6;
	m_consoleLine[6] = l7;
	m_consoleLine[7] = l8;
	m_consoleLine[8] = l9;
	m_consoleLine[9] = l10;
}

void UserInterface::ShowTowerInfo()
{
	SetAlign(ALIGN_LEFT);
	SetCurrentColor(255, 255, 0);
	SetCurrentFont(FontType::HUD_FONT);
	ShowText(m_consoleLine[0], 10, 190);

	SetCurrentColor(51, 153, 255);
	SetCurrentFont(FontType::SMALL_FONT);
	for (int i = 1; i < 10; ++i)
	{
		if (i > 4)
			SetCurrentColor(0, 255, 0);
		ShowText(m_consoleLine[i], 10, 230 + 25 * (i - 1));
	}
}

void UserInterface::ShowImportantText(const std::string p_text)
{
	SDL_RenderCopy(m_window->GetRenderer(), m_importantMessageBackgroundTexture, nullptr, &GetImportantMessageBackground());

	SetCurrentColor(255, 255, 255);
	SetCurrentFont(BIG_FONT);
	SetAlign(ALIGN_CENTER);
	ShowText(p_text, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}

void UserInterface::ShowWaveClearScore() const
{
	int waveScore = 100;
	if (GetGameInfo()->GetSpawnedEnemies() != 0)
		waveScore = static_cast<int>(GetGameInfo()->GetKilledEnemies() / GetGameInfo()->GetSpawnedEnemies() * 100.f);
		
	SDL_Texture* toRender = nullptr;

	if (waveScore >= 0 && waveScore < 25)
	{
		toRender = m_waveScoreTexture1;
	} else if (waveScore >= 25 && waveScore < 75)
	{
		toRender = m_waveScoreTexture2;
	} else if (waveScore >= 75)
	{
		toRender = m_waveScoreTexture3;
	}

	SDL_RenderCopy(GetWindow()->GetRenderer(), toRender, nullptr, &m_waveScoreRect);
}

void UserInterface::ShowTimer(const std::string p_text)
{
	SDL_RenderCopy(m_window->GetRenderer(), m_timerTexture, nullptr, &GetTimerRect());
	
	SetCurrentColor(255, 255, 255);
	SetCurrentFont(HUD_FONT);
	SetAlign(ALIGN_CENTER);
	ShowText(p_text, TEXT_TIMER_X_POS, TEXT_TIMER_Y_POS);
}

void UserInterface::ShowCursor()
{
	SDL_GetMouseState(&GetCursorRect().x, &GetCursorRect().y);
	GetCursorRect().w = CURSOR_WIDTH / CURSOR_SCALE;
	GetCursorRect().h = CURSOR_HEIGHT / CURSOR_SCALE;

	SDL_RenderCopy(GetWindow()->GetRenderer(), m_cursorTexture, nullptr, &GetCursorRect());
}

void UserInterface::Update()
{
	Display();
}
