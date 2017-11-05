#ifndef _BUTTON_
#define _BUTTON_

#include <vector>

#include "Vector2D.h"
#include "EventManager.h"
#include "GameInfo.h"
#include "Window.h"
#include "Sprite.h"

#define BUTTON_BACKGROUND_NOT_HOVER_TEXTURE "assets/UI/buttons/background.png"
#define BUTTON_BACKGROUND_HOVER_TEXTURE "assets/UI/buttons/background_hover.png"
#define BUTTON_BACKGROUND_WIDTH 132
#define BUTTON_BACKGROUND_HEIGHT 132
#define BUTTON_BACKGROUND_X_SCALE 1
#define BUTTON_BACKGROUND_Y_SCALE 1

#define BUTTON_CONTENT_X_OFFSET 0
#define BUTTON_CONTENT_Y_OFFSET 0

#define BUTTON_DEFAULT_ANIMATION ANIMATION_BALANCING

enum AnimationMode
{
	ANIMATION_BALANCING,
	ANIMATION_ROTATING
};

class Button
{
public:
	explicit Button(Window* p_window, EventManager* p_eventManager, GameInfo* p_gameInfo, const int p_x = 0, const int p_y = 0, const int p_offetX = BUTTON_CONTENT_X_OFFSET, const int p_offsetY = BUTTON_CONTENT_Y_OFFSET);
	virtual ~Button();

	bool IsUpdatable() const { return m_updatable; }
	bool IsDisplayable() const { return m_displayable; }
	bool IsClickable() const { return m_clickable; }
	bool IsHoverable() const { return m_hoverable; }
	bool IsAnimated() const { return m_animated; }
	bool MouseIsOver() const;

	Window* GetWindow() const { return m_window; }
	EventManager* GetEventManager() const { return m_eventManager; }
	GameInfo* GetGameInfo() const { return m_gameInfo; }
	Sprite* GetBackgroundCurrentSprite() const { return m_backgroundCurrentSprite; }
	Sprite* GetBackgroundNotHoverSprite() const { return m_backgroundNotHoverSprite; }
	Sprite* GetBackgroundHoverSprite() const { return m_backgroundHoverSprite; }
	std::vector<Sprite*>& GetSprites() { return m_sprites; }
	Vector2D<float>& GetPosition() { return m_position; }
	Vector2D<int>& GetContentOffset() { return m_contentOffset; }
	float GetAnimationTimer() const { return m_animationTimer; }
	uint8_t GetAnimationMode() const { return m_animationMode; }

	void SetUpdatable(const bool p_value) { m_updatable = p_value; }
	void SetDisplayable(const bool p_value) { m_displayable = p_value; }
	void SetClickable(const bool p_value) { m_clickable = p_value; }
	void SetHoverable(const bool p_value) { m_hoverable = p_value; }
	void SetAnimated(const bool p_value) { m_animated = p_value; }
	void SetWindow(Window* p_window) { m_window = p_window; }
	void SetEventManager(EventManager* p_eventManager) { m_eventManager = p_eventManager; }
	void SetGameInfo(GameInfo* p_gameInfo) { m_gameInfo = p_gameInfo; }
	void SetBackgroundCurrentSprite(Sprite* p_sprite) { m_backgroundCurrentSprite = p_sprite; }
	void SetBackgroundNotHoverSprite(Sprite* p_sprite) { m_backgroundNotHoverSprite = p_sprite; }
	void SetBackgroundHoverSprite(Sprite* p_sprite) { m_backgroundHoverSprite = p_sprite; }
	void SetPosition(const float p_x, const float p_y); 
	void SetPosition(const int p_x, const int p_y) { SetPosition(static_cast<float>(p_x), static_cast<float>(p_y)); }
	void SetPosition(Vector2D<int>& p_position) { SetPosition(p_position.X(), p_position.Y()); }
	void SetPosition(Vector2D<float>& p_position) { SetPosition(p_position.X(), p_position.Y()); }
	void SetContentOffset(const int p_offsetX, const int p_offsetY);
	void SetAnimationTimer(const float p_value) { m_animationTimer = p_value; }
	void SetAnimationMode(const uint8_t p_value) { m_animationMode = p_value; }

	void UpdateAnimationTimer();
	void ResetAnimationTimer() { m_animationTimer = 0; }
	void AddSprite(Sprite* p_toAdd) { GetSprites().push_back(p_toAdd); }
	virtual void MergeSpritesPosition();
	
	void ApplyOffsets();
	void Update();
	void Display();

	void BalancingAnimation();
	void RotatingAnimation();

	virtual void Animate();
	virtual void OnMouseOver();
	virtual void OnMouseNotOver();
	virtual void OnMouseLeftClick();
	virtual void OnMouseRightClick();

protected:
	Vector2D<float> m_position;
	Vector2D<int> m_contentOffset;
	
	Window* m_window;
	EventManager* m_eventManager;
	GameInfo* m_gameInfo;

	Sprite* m_backgroundCurrentSprite;
	Sprite* m_backgroundNotHoverSprite;
	Sprite* m_backgroundHoverSprite;
	std::vector<Sprite*> m_sprites;

	bool m_updatable;
	bool m_displayable;
	bool m_clickable;
	bool m_hoverable;
	bool m_animated;

	float m_animationTimer;
	uint8_t m_animationMode;
};

#endif // !_BUTTON_