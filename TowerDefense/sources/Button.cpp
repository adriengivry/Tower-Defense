#include "Button.h"

Button::Button(Window* p_window, EventManager* p_eventManager, GameInfo* p_gameInfo, const int p_x, const int p_y, const int p_offsetX, const int p_offsetY)
{
	SetUpdatable(true);
	SetDisplayable(true);
	SetClickable(true);
	SetHoverable(true);
	SetAnimated(true);

	SetWindow(p_window);
	SetEventManager(p_eventManager);
	SetGameInfo(p_gameInfo);

	SetBackgroundNotHoverSprite(new Sprite(GetWindow(), BUTTON_BACKGROUND_NOT_HOVER_TEXTURE));
	GetBackgroundNotHoverSprite()->SetSize(BUTTON_BACKGROUND_WIDTH * BUTTON_BACKGROUND_X_SCALE, BUTTON_BACKGROUND_HEIGHT * BUTTON_BACKGROUND_Y_SCALE);
	GetBackgroundNotHoverSprite()->SetPositionMode(POSITION_CENTERED);
	
	SetBackgroundHoverSprite(new Sprite(GetWindow(), BUTTON_BACKGROUND_HOVER_TEXTURE));
	GetBackgroundHoverSprite()->SetSize(BUTTON_BACKGROUND_WIDTH * BUTTON_BACKGROUND_X_SCALE, BUTTON_BACKGROUND_HEIGHT * BUTTON_BACKGROUND_Y_SCALE);
	GetBackgroundHoverSprite()->SetPositionMode(POSITION_CENTERED);

	SetBackgroundCurrentSprite(GetBackgroundNotHoverSprite());

	SetPosition(p_x, p_y);
	SetContentOffset(p_offsetX, p_offsetY);
	SetAnimationMode(BUTTON_DEFAULT_ANIMATION);
}


Button::~Button()
{
	delete m_backgroundNotHoverSprite;
	delete m_backgroundHoverSprite;

	for (auto it = GetSprites().begin(); it != GetSprites().end(); ++it)
		if (*it)
			delete *it;
}

bool Button::MouseIsOver() const
{
	const auto x1 = GetBackgroundCurrentSprite()->GetRect().x;
	const auto y1 = GetBackgroundCurrentSprite()->GetRect().y;
	const auto w1 = GetBackgroundCurrentSprite()->GetRect().w;
	const auto h1 = GetBackgroundCurrentSprite()->GetRect().h;

	int x2, y2;
	SDL_GetMouseState(&x2, &y2);

	return x1 + w1 >= x2 && x1 <= x2 && y1 + h1 >= y2 && y1 <= y2;
}

void Button::SetPosition(const float p_x, const float p_y)
{
	GetPosition().X() = p_x;
	GetPosition().Y() = p_y;
}

void Button::SetContentOffset(const int p_offsetX, const int p_offsetY)
{
	m_contentOffset.X() = p_offsetX;
	m_contentOffset.Y() = p_offsetY;
}

void Button::UpdateAnimationTimer()
{
	SetAnimationTimer(GetAnimationTimer() + GetGameInfo()->GetDeltaTime() * 1000.f);
}

void Button::MergeSpritesPosition()
{
	GetBackgroundNotHoverSprite()->SetPosition(GetPosition().X(), GetPosition().Y());
	GetBackgroundHoverSprite()->SetPosition(GetPosition().X(), GetPosition().Y());

	for (auto it = GetSprites().begin(); it != GetSprites().end(); ++it)
		if (*it)
			(*it)->SetPosition(GetPosition().X(), GetPosition().Y());
}

void Button::ApplyOffsets()
{
	for (auto it = GetSprites().begin(); it != GetSprites().end(); ++it)
		if (*it)
			(*it)->Move(GetContentOffset().X(), GetContentOffset().Y());
}

void Button::Update()
{
	if (IsUpdatable())
	{
		UpdateAnimationTimer();

		MergeSpritesPosition();

		ApplyOffsets();

		if (IsAnimated())
			Animate();		
		
		if (IsClickable() && MouseIsOver() && GetEventManager()->GetEvent(LEFT_CLICK_EVENT).IsOn())
		{
			OnMouseLeftClick();
			GetEventManager()->GetEvent(LEFT_CLICK_EVENT).Toggle();
		}

		if (IsClickable() && MouseIsOver() && GetEventManager()->GetEvent(RIGHT_CLICK_EVENT).IsOn())
		{
			OnMouseRightClick();
			GetEventManager()->GetEvent(RIGHT_CLICK_EVENT).Toggle();
		}
			
		if (IsHoverable() && MouseIsOver())
			OnMouseOver();
		else
			OnMouseNotOver();

		if (IsDisplayable())
			Display();
	}
}

void Button::Display()
{
	GetBackgroundCurrentSprite()->Display();

	for (auto it = GetSprites().begin(); it != GetSprites().end(); ++it)
		if (*it)
			(*it)->Display();
}

void Button::BalancingAnimation()
{
	if (GetAnimationTimer() <= 1000)
	{
		GetSprites()[0]->CircularMove(0.2f);
	}
	else if (GetAnimationTimer() <= 2000)
	{
		GetSprites()[0]->CircularMove(-0.2f);
	}
	else
	{
		ResetAnimationTimer();
	}
}

void Button::RotatingAnimation()
{
	GetSprites()[0]->CircularMove(1);
}

void Button::Animate()
{
	switch (GetAnimationMode())
	{
	default:
	case ANIMATION_BALANCING:
		BalancingAnimation();
		break;

	case ANIMATION_ROTATING:
		RotatingAnimation();
		break;
	}
}

void Button::OnMouseOver()
{
	SetBackgroundCurrentSprite(m_backgroundHoverSprite);
}

void Button::OnMouseNotOver()
{
	SetBackgroundCurrentSprite(m_backgroundNotHoverSprite);
}

void Button::OnMouseLeftClick()
{
	GetGameInfo()->GetAudioManager()->PlaySound(CLICK_SOUND_PATH);
	// TODO: On mouse left click
}

void Button::OnMouseRightClick()
{
	// TODO: On mouse right click
}
