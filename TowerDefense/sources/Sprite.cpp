#include "Sprite.h"
#include "GameLoader.h"

Sprite::Sprite(Window* p_window, const std::string p_path, const int p_x, const int p_y, const int p_w, const int p_h, const uint8_t p_positionMode, const uint8_t p_rotationAngle)
{
	SetWindow(p_window);
	SetPositionMode(p_positionMode);
	SetRect(p_x, p_y, p_w, p_h);
	SetRotationAngle(p_rotationAngle);

	if (p_path != "")
		CreateTexture(p_path);
}

Sprite::~Sprite()
{
	DestroyTexture();
}

void Sprite::SetRect(const int p_x, const int p_y, const int p_w, const int p_h)
{
	SetSize(p_w, p_h);
	SetPosition(p_x, p_y);
}

void Sprite::SetPosition(const int p_x, const int p_y)
{
	switch (GetPositionMode())
	{
	default:
	case POSITION_NORMAL:
		GetRect().x = p_x;
		GetRect().y = p_y;
		break;

	case POSITION_CENTERED:
		GetRect().x = p_x - GetRect().w / 2;
		GetRect().y = p_y - GetRect().h / 2;
		break;
	}
}

void Sprite::SetSize(const int p_w, const int p_h)
{
	GetRect().w = p_w;
	GetRect().h = p_h;
}

Vector2D<int>& Sprite::GetCenterPoint()
{
	CalculateCenterPoint();
	return m_centerPoint;
}

SDL_Point& Sprite::GetSDLCenterPoint()
{
	CalculateSDLCenterPoint();
	return m_sdlCenterPoint;
}

void Sprite::CalculateCenterPoint()
{
	m_centerPoint.X() = GetRect().x + GetRect().w / 2;
	m_centerPoint.Y() = GetRect().y + GetRect().h / 2;
}

void Sprite::CalculateSDLCenterPoint()
{
	m_sdlCenterPoint.x = GetRect().x + GetRect().w / 2;
	m_sdlCenterPoint.y = GetRect().y + GetRect().h / 2;
}

void Sprite::CreateTexture(const std::string p_texturePath)
{
	if (GetTexture())
		DestroyTexture();

	SetTexture(LoadTexture(p_texturePath));
}

void Sprite::DestroyTexture()
{
	SDL_DestroyTexture(GetTexture());
	SetTexture(nullptr);
}

void Sprite::Move(const int p_offsetX, const int p_offsetY)
{
	GetRect().x += p_offsetX;
	GetRect().y += p_offsetY;
}

void Sprite::Display()
{
	SDL_RenderCopyEx(GetWindow()->GetRenderer(), GetTexture(), nullptr, &GetRect(), GetRotationAngle(), nullptr, SDL_FLIP_NONE);
}
