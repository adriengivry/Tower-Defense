#ifndef _ACTOR_
#define _ACTOR_

#include <list>
#include <map>
#include <algorithm>

#include <SDL.h>
#include <SDL_image.h>

#include "Window.h"
#include "EventManager.h"
#include "GameInfo.h"
#include "UserInterface.h"

#include "Vector2D.h"
#include "string_operation.h"

#define DEFAULT_MESSAGE_LIFETIME 50
#define DEFAULT_ROTATION_ANGLE 0

#define ACTOR_BASE_ALPHA 255
#define ACTOR_HOVER_ALPHA 150

#define ACTOR_ANIMATED_MESSAGE_TEXTURE_PATH "assets/UI/animated_message_background.png"
#define ACTOR_ANIMATED_MESSAGE_WIDTH 373
#define ACTOR_ANIMATED_MESSAGE_HEIGHT 80
#define ACTOR_ANIMATED_MESSAGE_SCALE 2
#define ACTOR_SPEAK_TEXTURE_PATH "assets/UI/speak.png"
#define ACTOR_SPEAK_WIDTH 300
#define ACTOR_SPEAK_HEIGHT 89
#define ACTOR_SPEAK_SCALE 1.5
#define ACTOR_SPEAK_Y_OFFSET -73
#define ACTOR_SPEAK_DIVIDE_PART 3

class Enemy;
class Tower;
class Slot;
class Projectile;

class Actor
{
public:
	explicit Actor(Window* p_window = nullptr, GameInfo* p_gameInfo = nullptr, const float p_x = 0, const float p_y = 0);
	virtual ~Actor();

	bool IsUpdatable() const { return m_canBeUpdated; }
	bool IsDisplayable() const { return m_canBeDisplayed; }
	bool IsTickable() const { return m_canBeTicked; }
	bool IsMovable() const { return m_canBeMoved; }
	bool IsClickable() const { return m_canBeClicked; }
	bool IsAttackable() const { return m_canBeAttacked; }
	bool IsHealable() const { return m_canBeHealed; }
	bool IsAbleToDie() const { return m_canDie; }
	bool IsHoverable() const { return m_canBeHovered; }
	bool IsMessageAnimated() const { return m_messageIsAnimated; }

	bool MustBeRed() const { return m_sayInRed; }
	virtual bool MustDie() const { return m_lifeTime == 0; }
	bool WannaTalk() const { return GetMessageToSay() != ""; }
	bool Intersect(Actor& p_otherActor);
	bool MouseOver();

	SDL_Rect& GetHitbox() { return m_hitbox; }
	Vector2D<int> GetMiddle();
	Window* GetWindow() const { return m_window; }
	GameInfo* GetGameInfo() const { return m_gameInfo; }
	UserInterface* GetUserInterface() const { return m_userInterface; }
	std::list<Enemy*>* GetEnemyList() const { return m_enemyList; }
	std::list<Slot*>* GetSlotList() const { return m_slotList; }
	std::list<Tower*>* GetTowerList() const { return m_towerList; }
	std::list<Projectile*>* GetProjectileList() const { return m_projectileList; }
	Actor* GetTargetToFollow() const { return m_targetToFollow; }
	Vector2D<float>& GetDirection() { return m_direction; }
	float GetSpeed() const { return m_speed; }
	size_t GetLifeTime() const { return m_lifeTime; }
	size_t GetTickCounter() const { return m_tickCounter; }
	std::string GetMessageToSay() const { return m_messageToSay; }
	int GetMessageTotalLifetime() const { return m_messageTotalLifetime; }
	int GetMessageLifetime() const { return m_messageLifetime; }
	size_t GetMessageOffset() const { return m_messageOffset; }
	float GetRotationAngle() const { return m_rotationAngle; }
	float GetDistanceTraveled() const { return m_distanceTraveled; }
	uint8_t GetBaseAlpha() const { return m_baseAlpha; }
	uint8_t GetHoverAlpha() const { return m_hoverAlpha; }
	SDL_Rect& GetSpeakRect() { return m_speakRect; }
	SDL_Texture* GetSpeakTexture() const { return m_speakTexture; }
	SDL_Rect& GetAnimatedMessageRect() { return m_animatedMessageRect; }
	SDL_Texture* GetAnimatedMessageTexture() const { return m_animatedMessageTexture; }

	void SetWindow(Window* p_newWindow) { m_window = p_newWindow; }
	void SetGameInfo(GameInfo* p_newGameInfo) { m_gameInfo = p_newGameInfo; }
	void SetUserInterface(UserInterface* p_userInterface) { m_userInterface = p_userInterface; }
	void SetEnemyList(std::list<Enemy*>* p_enemyList) { m_enemyList = p_enemyList; }
	void SetSlotList(std::list<Slot*>* p_slotList) { m_slotList = p_slotList; }
	void SetTowerList(std::list<Tower*>* p_towerList) { m_towerList = p_towerList; }
	void SetProjectileList(std::list<Projectile*>* p_projectileList) { m_projectileList = p_projectileList; }
	void SetTargetToFollow(Actor* p_toFollow) { m_targetToFollow = p_toFollow; }
	void SetPosition(const float p_x, const float p_y);
	void SetSize(const int p_w, const int p_h);
	void SetDirection(const float p_vx, const float p_vy);
	void SetSpeed(const float p_speed) { m_speed = p_speed; }
	void SetLifeTime(const size_t p_lifeTime);
	void SetTexture(const std::string p_pathToTexture);
	void SetMessageToSay(const std::string p_messageToSay) { m_messageToSay = p_messageToSay; }
	void SetMessageTotalLifetime(const int p_value) { m_messageTotalLifetime = p_value; }
	void SetMessageLifetime(const int p_value) { m_messageLifetime = p_value; }
	void SetUpdatable(const bool p_value) { m_canBeUpdated = p_value; }
	void SetDisplayable(const bool p_value) { m_canBeDisplayed = p_value; }
	void SetTickable(const bool p_value) { m_canBeTicked = p_value; }
	void SetMovable(const bool p_value) { m_canBeMoved = p_value; }
	void SetClickable(const bool p_value) { m_canBeClicked = p_value; }
	void SetAttackable(const bool p_value) { m_canBeAttacked = p_value; }
	void SetHealable(const bool p_value) { m_canBeHealed = p_value; }
	void SetAbleToDie(const bool p_value) { m_canDie = p_value; }
	void SetHoverable(const bool p_value) { m_canBeHovered = p_value; }
	void SetMessageAnimated(const bool p_value) { m_messageIsAnimated = p_value; }
	void SetMessageOffset(const size_t p_value) { m_messageOffset = p_value; }
	void SetRotationAngle(const float p_value) { m_rotationAngle = p_value; }
	void SetDistanceTravaled(const float p_value) { m_distanceTraveled = p_value; }
	void SetBaseAlpha(const uint8_t p_value) { m_baseAlpha = p_value; }
	void SetHoverAlpha(const uint8_t p_value) { m_hoverAlpha = p_value; }
	void SetSpeakTexture(SDL_Texture* p_value) { m_speakTexture = p_value; }
	void SetSayInRed(const bool p_value) { m_sayInRed = p_value; }
	void SetAnimatedMessageTexture(SDL_Texture* p_value) { m_animatedMessageTexture = p_value; }

	void ResetTickCounter() { m_tickCounter = 0; }
	void IncrementTickCounter() { ++m_tickCounter; }
	void AddDistanceTravaled(const float p_value) { SetDistanceTravaled(GetDistanceTraveled() + p_value); }

	void MergePosition();
	virtual void Say(const std::string p_toSay, const int p_messageLifetime = DEFAULT_MESSAGE_LIFETIME, const bool p_sayInRed = false);
	void SpeakNow();
	virtual void Move(const float p_x, const float p_y);
	void MoveTo(Actor* p_target);
	void Highlight() const { SDL_SetTextureAlphaMod(m_texture, GetHoverAlpha()); }
	void UnHighlight() const { SDL_SetTextureAlphaMod(m_texture, GetBaseAlpha()); }

	void Highlight(SDL_Texture* p_texture) const { SDL_SetTextureAlphaMod(p_texture, GetHoverAlpha()); }
	void UnHighlight(SDL_Texture* p_texture) const { SDL_SetTextureAlphaMod(p_texture, GetBaseAlpha()); }

	virtual void Destroy(const std::string p_message = "");

	virtual void UpdatePosition();
	virtual void Update(EventManager& p_eventManager);
	virtual void Display();

	virtual void Tick();
	virtual void OnMouseOver();
	virtual void OnClick();
	virtual void OnRightClick();
	
protected:
	bool m_canBeUpdated;
	bool m_canBeDisplayed;
	bool m_canBeTicked;
	bool m_canBeMoved;
	bool m_canBeClicked;
	bool m_canBeAttacked;
	bool m_canBeHealed;
	bool m_canDie;
	bool m_canBeHovered;

	bool m_sayInRed;

	uint8_t m_baseAlpha;
	uint8_t m_hoverAlpha;

	Window* m_window;
	GameInfo* m_gameInfo;
	UserInterface* m_userInterface;

	SDL_Texture* m_texture;
	SDL_Rect m_hitbox;

	SDL_Rect m_speakRect;
	SDL_Texture* m_speakTexture;

	SDL_Rect m_animatedMessageRect;
	SDL_Texture* m_animatedMessageTexture;

	Vector2D<float> m_position;
	Vector2D<float> m_direction;
	float m_speed;
	float m_rotationAngle;

	std::list<Enemy*>* m_enemyList;
	std::list<Slot*>* m_slotList;
	std::list<Tower*>* m_towerList;
	std::list<Projectile*>* m_projectileList;
	Actor* m_targetToFollow;

	std::string m_messageToSay = "";
	size_t m_messageTotalLifetime;
	size_t m_messageLifetime;
	SDL_Color m_messageColor;
	bool m_messageIsAnimated;
	size_t m_messageOffset;

	float m_distanceTraveled;

	size_t m_tickCounter;
	size_t m_lifeTime;
};

#endif // !_ACTOR_