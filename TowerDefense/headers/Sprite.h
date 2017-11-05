#ifndef _SPRITE_
#define _SPRITE_

#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "Window.h"
#include "Vector2D.h"

enum PositionMode
{
	POSITION_NORMAL,
	POSITION_CENTERED
};

class Sprite
{
public:
	explicit Sprite(Window* p_window, const std::string p_path = "", const int p_x = 0, const int p_y = 0, const int p_w = 0, const int p_h = 0, const uint8_t p_positionMode = POSITION_NORMAL, const uint8_t p_rotationAngle = 0);
	~Sprite();

	void SetTexture(SDL_Texture* p_newTexture) { m_texture = p_newTexture; }
	void SetRect(const int p_x = 0, const int p_y = 0, const int p_w = 0, const int p_h = 0);
	void SetPosition(const int p_x, const int p_y);
	void SetPosition(const float p_x, const float p_y) { SetPosition(static_cast<int>(p_x), static_cast<int>(p_y)); }
	void SetPosition(Vector2D<int>& p_position) { SetPosition(p_position.X(), p_position.Y()); }
	void SetPosition(Vector2D<float>& p_position) { SetPosition(p_position.X(), p_position.Y()); }
	void SetSize(const int p_w, const int p_h);
	void SetSize(const float p_w, const float p_h) { SetSize(static_cast<int>(p_w), static_cast<int>(p_h)); }
	void SetSize(Vector2D<int>& p_size) { SetSize(p_size.X(), p_size.Y()); }
	void SetSize(Vector2D<float>& p_size) { SetSize(p_size.X(), p_size.Y()); }
	void SetWindow(Window* p_window) { m_window = p_window; }
	void SetRotationAngle(const float p_value) { m_rotationAngle = p_value; }
	void SetPositionMode(const uint8_t p_value) { m_positionMode = p_value; }

	Window* GetWindow() const { return m_window; }
	SDL_Texture* GetTexture() const { return m_texture; }
	SDL_Rect& GetRect() { return m_rect; }
	float GetRotationAngle() const { return m_rotationAngle; }
	uint8_t GetPositionMode() const { return m_positionMode; }
	Vector2D<int>& GetCenterPoint();
	SDL_Point& GetSDLCenterPoint();

	void CalculateCenterPoint();
	void CalculateSDLCenterPoint();
	void CircularMove(const float p_angle) { SetRotationAngle(GetRotationAngle() + p_angle); }
	void CreateTexture(const std::string p_texturePath);
	void DestroyTexture();

	void Move(const int p_offsetX, const int p_offsetY);
	void Display();

private:
	SDL_Texture* LoadTexture(const std::string p_texturePath) const { return IMG_LoadTexture(GetWindow()->GetRenderer(), p_texturePath.c_str()); }
	Vector2D<int> m_centerPoint;
	SDL_Point m_sdlCenterPoint;

	Window* m_window;
	SDL_Rect m_rect;
	SDL_Texture* m_texture;

	uint8_t m_positionMode;

	float m_rotationAngle;
};

#endif // !_SPRITE_