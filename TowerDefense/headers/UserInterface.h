#ifndef _USERINTERFACE_
#define _USERINTERFACE_

#include <string>
#include <exception>

#include <SDL.h>
#include <SDL_ttf.h>

#include "GameInfo.h"
#include "Window.h"

#define FONT_PATH "assets/fonts/arial.ttf"
#define BOLD_FONT_PATH "assets/fonts/arial_round.ttf"
#define FANCY_FONT_PATH "assets/fonts/GILLUBCD.TTF"
#define BUBBLE_FONT_PATH "assets/fonts/bubble.ttf"

#define IMPORTANT_MESSAGE_TEXTURE_PATH "assets/UI/message_background.png"
#define IMPORTANT_MESSAGE_WIDTH 1000
#define IMPORTANT_MESSAGE_HEIGHT 120
#define IMPORTANT_MESSAGE_X_POS 450
#define IMPORTANT_MESSAGE_Y_POS WINDOW_HEIGHT / 2 - 25
#define IMPORTANT_MESSAGE_SCALE 1

#define LIFEBAR_TEXTURE_PATH "assets/UI/lifebar.png"
#define LIFEBAR_WIDTH 0
#define LIFEBAR_HEIGHT 31
#define LIFEBAR_X_POS 1620
#define LIFEBAR_Y_POS 40
#define LIFEBAR_SCALE 1
#define LIFEBAR_WANTED_HEIGHT 279

#define SELECTOR_TEXTURE_PATH "assets/UI/selector.png"
#define SELECTOR_WIDTH 512
#define SELECTOR_HEIGHT 512
#define SELECTOR_X_POS 1730
#define SELECTOR_Y_POS 130
#define SELECTOR_SCALE 6
#define SELECTOR_MOVEMENT_SPEED 10
#define SELECTOR_POSY_1 130
#define SELECTOR_POSY_2 270

#define TIMER_TEXTURE_PATH "assets/UI/timer.png"
#define TIMER_WIDTH 264
#define TIMER_HEIGHT 80
#define TIMER_X_POS 750
#define TIMER_Y_POS 980
#define TIMER_SCALE 1

#define CURSOR_NORMAL_TEXTURE_PATH "assets/cursors/sepia.png"
#define CURSOR_HOVER_TEXTURE_PATH "assets/cursors/light_green.png"
#define CURSOR_ERROR_TEXTURE_PATH "assets/cursors/red.png"
#define CURSOR_WIDTH 49
#define CURSOR_HEIGHT 46
#define CURSOR_SCALE 1

#define WAVE_SCORE_TEXTURE_1_PATH "assets/UI/wave_scores/star_1.png"
#define WAVE_SCORE_TEXTURE_2_PATH "assets/UI/wave_scores/star_2.png"
#define WAVE_SCORE_TEXTURE_3_PATH "assets/UI/wave_scores/star_3.png"
#define WAVE_SCORE_WIDTH 728
#define WAVE_SCORE_HEIGHT 169
#define WAVE_SCORE_SCALE 2
#define WAVE_SCORE_X_POS 778
#define WAVE_SCORE_Y_POS 600

#define TEXT_MONEY_X_POS 140
#define TEXT_MONEY_Y_POS 55

#define TEXT_TIME_X_POS
#define TEXT_TIME_Y_POS

#define TEXT_STAGE_X_POS 1695
#define TEXT_STAGE_Y_POS 126

#define TEXT_TIMER_X_POS 910
#define TEXT_TIMER_Y_POS 1016

#define RANGE_TO_SHOW_ALPHA 35

typedef const std::string cstr;

enum FontType
{
	FANCY_FONT,
	SMALL_FONT,
	TOOLTIP_FONT,
	HUD_FONT,
	NORMAL_FONT,
	BIG_FONT,
	BUBBLE_FONT
};

enum TextProperty
{
	ALIGN_CENTER,
	ALIGN_LEFT,
	ALIGN_RIGHT
};

enum CursorType
{
	CURSOR_NORMAL,
	CURSOR_HOVER,
	CURSOR_ERROR
};

class UserInterface
{
public:
	explicit UserInterface(Window* p_window = nullptr, GameInfo* p_gameInfo = nullptr);
	~UserInterface();

	GameInfo* GetGameInfo() const { return m_gameInfo; }
	Window* GetWindow() const { return m_window; }
	SDL_Color& GetCurrentColor() { return m_currentColor; }
	SDL_Color GetCurrentColor() const { return m_currentColor; }
	TTF_Font* GetCurrentFont() const { return m_currentFont; }
	uint8_t GetCurrentAlign() const { return m_alignProperty; }
	SDL_Rect& GetImportantMessageBackground() { return m_importantMessageBackgroundRect; }
	SDL_Rect& GetTimerRect() { return m_timerRect; }
	SDL_Rect& GetTowerSelectorRect() { return m_towerSelectorRect; }
	SDL_Rect& GetCastleLifebarRect() { return m_castleLifebarRect; }
	SDL_Rect& GetTowerRangeRect() { return m_towerRangeRect; }
	SDL_Rect& GetCursorRect() { return m_cursorRect; }
	SDL_Texture* GetTowerSelectorTexture() const { return m_towerSelectorTexture; }
	SDL_Texture* GetCursorTexture() const { return m_cursorTexture; }
	
	bool MustShowTowerRange() const { return m_showTowerRange; }

	void SetShowTowerRange(const bool p_value) { m_showTowerRange = p_value; }
	void SetCurrentColor(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a = 255);
	void SetCurrentFont(const uint8_t p_font);
	void SetAlign(const uint8_t p_property) { m_alignProperty = p_property; }
	void SetTowerInfo(cstr l1 = "", cstr l2 = "", cstr l3 = "", cstr l4 = "", cstr l5 = "", cstr l6 = "", cstr l7 = "", cstr l8 = "", cstr l9 = "", cstr l10 = "");
	void SetCursorTexture(SDL_Texture* p_value) { m_cursorTexture = p_value; }

	void SetCursor(const uint8_t p_type);

	void ShowText(const std::string p_text, const int p_x, const int p_y, const uint8_t p_alpha = 255) const;
	void ShowTowerInfo();
	void ShowImportantText(const std::string p_text);
	void ShowWaveClearScore() const;
	void ShowTimer(const std::string p_text);
	void ShowCursor();

	void Update();
	void Display();

private:
	TTF_Font* m_currentFont;
	TTF_Font* m_smallFont;
	TTF_Font* m_hudFont;
	TTF_Font* m_tooltipFont;
	TTF_Font* m_normalFont;
	TTF_Font* m_bigFont;
	TTF_Font* m_fancyFont;
	TTF_Font* m_bubbleFont;

	bool m_showTowerRange;

	std::string m_consoleLine[10];

	SDL_Color m_currentColor;

	SDL_Rect m_importantMessageBackgroundRect;
	SDL_Texture* m_importantMessageBackgroundTexture;

	SDL_Rect m_castleLifebarRect;
	SDL_Texture* m_castleLifebarTexture;

	SDL_Rect m_towerSelectorRect;
	SDL_Texture* m_towerSelectorTexture;

	SDL_Rect m_timerRect;
	SDL_Texture* m_timerTexture;

	SDL_Rect m_towerRangeRect;
	SDL_Texture* m_towerRangeTexture;

	SDL_Rect m_cursorRect;
	SDL_Texture* m_cursorTexture;

	SDL_Rect m_waveScoreRect;
	SDL_Texture* m_waveScoreTexture1;
	SDL_Texture* m_waveScoreTexture2;
	SDL_Texture* m_waveScoreTexture3;

	SDL_Texture* m_normalCursorTexture;
	SDL_Texture* m_hoverCursorTexture;
	SDL_Texture* m_errorCursorTexture;

	uint8_t m_alignProperty;

	GameInfo* m_gameInfo;
	Window* m_window;
};

#endif // !_USERINTERFACE_