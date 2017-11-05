#include "Actor.h"

Actor::Actor(Window* p_window, GameInfo* p_gameInfo, const float p_x, const float p_y)
{
	SetWindow(p_window);
	SetGameInfo(p_gameInfo);

	SetSayInRed(false);
	SetPosition(p_x, p_y);
	SetUpdatable(true);
	SetMovable(true);
	SetTickable(true);
	SetDisplayable(true);
	SetClickable(false);
	SetAbleToDie(false);
	SetMessageAnimated(true);
	SetMessageOffset(0);
	SetLifeTime(0);
	SetDistanceTravaled(0);
	SetBaseAlpha(ACTOR_BASE_ALPHA);
	SetHoverAlpha(ACTOR_HOVER_ALPHA);

	GetDirection().X() = 0;
	GetDirection().Y() = 0;

	SetSpeed(5);
	SetRotationAngle(DEFAULT_ROTATION_ANGLE);

	SetAnimatedMessageTexture(IMG_LoadTexture(GetWindow()->GetRenderer(), ACTOR_ANIMATED_MESSAGE_TEXTURE_PATH));
}

Actor::~Actor()
{
	if (GetSpeakTexture())
		SDL_DestroyTexture(GetSpeakTexture());

	if (m_texture)
		SDL_DestroyTexture(m_texture);
}

void Actor::Update(EventManager& p_eventManager)
{
	SetLifeTime(GetLifeTime() - 1);

	if (GetMessageLifetime() > 0)
		SetMessageLifetime(GetMessageLifetime() - 1);
	else
		SetMessageToSay("");

	if (IsUpdatable())
	{
		if (MustDie() && IsAbleToDie())
			SetUpdatable(false);

		if (IsDisplayable())
			Display();

		if (WannaTalk())
			SpeakNow();

		if (IsTickable())
		{
			IncrementTickCounter();
			Tick();
		}

		if (IsMovable())
			UpdatePosition();

		if (MouseOver() && IsHoverable())
			OnMouseOver();

		if (IsClickable() && MouseOver() && p_eventManager.GetEvent(LEFT_CLICK_EVENT).IsOn())
		{
			OnClick();
			p_eventManager.GetEvent(LEFT_CLICK_EVENT).Toggle();
		}

		if (IsClickable() && MouseOver() && p_eventManager.GetEvent(RIGHT_CLICK_EVENT).IsOn())
		{
			OnRightClick();
			p_eventManager.GetEvent(RIGHT_CLICK_EVENT).Toggle();
		}
	}
}

void Actor::SetLifeTime(const size_t p_lifeTime)
{
	m_lifeTime = p_lifeTime;
}


Vector2D<int> Actor::GetMiddle()
{
	Vector2D<int> middle;

	middle.X() = GetHitbox().x + GetHitbox().w / 2;
	middle.Y() = GetHitbox().y + GetHitbox().h / 2;

	return middle;
}

void Actor::SetPosition(const float p_x, const float p_y)
{
	m_position.X() = p_x;
	m_position.Y() = p_y;
}

void Actor::Move(const float p_x, const float p_y)
{
	m_position.X() += p_x * GetGameInfo()->GetDeltaTime();
	m_position.Y() += p_y * GetGameInfo()->GetDeltaTime();

	AddDistanceTravaled(abs(p_x) * GetGameInfo()->GetDeltaTime() + abs(p_y) * GetGameInfo()->GetDeltaTime());
}

void Actor::SetDirection(const float p_vx, const float p_vy)
{
	m_direction.X() = p_vx;
	m_direction.Y() = p_vy;
}

void Actor::SetSize(const int p_w, const int p_h)
{
	GetHitbox().w = p_w;
	GetHitbox().h = p_h;
}

void Actor::SetTexture(const std::string p_pathToTexture)
{
	if (m_texture)
		SDL_DestroyTexture(m_texture);

	if (m_window)
		m_texture = IMG_LoadTexture(m_window->GetRenderer(), p_pathToTexture.c_str());
}

void Actor::Display()
{
	MergePosition();

	if (GetWindow())
	{
		const SDL_RendererFlip flip = SDL_FLIP_NONE;
		SDL_RenderCopyEx(GetWindow()->GetRenderer(), m_texture, nullptr, &GetHitbox(), GetRotationAngle(), nullptr, flip);
	}

	if (WannaTalk() && GetSpeakTexture() && !IsMessageAnimated())
	{
		GetSpeakRect().x = GetMiddle().X();
		GetSpeakRect().y = GetHitbox().y + ACTOR_SPEAK_Y_OFFSET;
		SDL_RenderCopy(GetWindow()->GetRenderer(), GetSpeakTexture(), nullptr, &GetSpeakRect());
	}
}

void Actor::Destroy(const std::string p_message)
{
	if (p_message != "")
		Say(p_message);

	SetLifeTime(0);
	SetUpdatable(false);
}

void Actor::UpdatePosition()
{
	if (GetTargetToFollow())
		MoveTo(GetTargetToFollow());
	else
		Move(m_direction.X() * GetSpeed(), m_direction.Y() * GetSpeed());
}

void Actor::MoveTo(Actor* p_target)
{
	GetDirection().X() = static_cast<float>(p_target->GetMiddle().X() - GetMiddle().X());
	GetDirection().Y() = static_cast<float>(p_target->GetMiddle().Y() - GetMiddle().Y());
	GetDirection().Normalize();

	Move(GetDirection().X() * GetSpeed(), GetDirection().Y() * GetSpeed());
}

bool Actor::Intersect(Actor& p_otherActor)
{
	const auto x1 = GetHitbox().x;
	const auto y1 = GetHitbox().y;
	const auto w1 = GetHitbox().w;
	const auto h1 = GetHitbox().h;

	const auto x2 = p_otherActor.GetHitbox().x;
	const auto y2 = p_otherActor.GetHitbox().y;
	const auto w2 = p_otherActor.GetHitbox().w;
	const auto h2 = p_otherActor.GetHitbox().h;

	return x1 + w1 >= x2 && x1 <= x2 + w2 && y1 + h1 >= y2 && y1 <= y2 + h2;
}

bool Actor::MouseOver()
{
	const auto x1 = GetHitbox().x;
	const auto y1 = GetHitbox().y;
	const auto w1 = GetHitbox().w;
	const auto h1 = GetHitbox().h;

	int x2, y2;
	SDL_GetMouseState(&x2, &y2);

	return x1 + w1 >= x2 && x1 <= x2 && y1 + h1 >= y2 && y1 <= y2;
}

void Actor::MergePosition()
{
	GetHitbox().x = static_cast<int>(m_position.X());
	GetHitbox().y = static_cast<int>(m_position.Y());
}

void Actor::Say(const std::string p_toSay, const int p_messageLifetime, const bool p_sayInRed)
{
	SetMessageToSay(p_toSay);
	SetMessageTotalLifetime(p_messageLifetime);
	SetMessageLifetime(p_messageLifetime);
	SetSayInRed(p_sayInRed);
}

void Actor::SpeakNow()
{
	int alpha = 255;
	int messagePosX;
	int messagePosY;

	if (IsMessageAnimated())
	{
		const int animationOffset = static_cast<int>(static_cast<float>(GetMessageLifetime()) / GetMessageTotalLifetime() * 100.f);

		if (GetMessageLifetime() <= GetMessageTotalLifetime() / 4)
			alpha = static_cast<int>(static_cast<float>(GetMessageLifetime()) / GetMessageTotalLifetime() * 1020);

		GetAnimatedMessageRect().w = ACTOR_ANIMATED_MESSAGE_WIDTH / ACTOR_ANIMATED_MESSAGE_SCALE;
		GetAnimatedMessageRect().h = ACTOR_ANIMATED_MESSAGE_HEIGHT / ACTOR_ANIMATED_MESSAGE_SCALE;
		GetAnimatedMessageRect().x = GetMiddle().X() - GetAnimatedMessageRect().w / 2;
		GetAnimatedMessageRect().y = GetHitbox().y - GetAnimatedMessageRect().h / 2 + animationOffset;
		
		SDL_SetTextureAlphaMod(GetAnimatedMessageTexture(), alpha);
		SDL_RenderCopy(GetWindow()->GetRenderer(), GetAnimatedMessageTexture(), nullptr, &GetAnimatedMessageRect());

		messagePosX = GetMiddle().X();
		messagePosY = GetHitbox().y + animationOffset;

		if (MustBeRed())
			GetUserInterface()->SetCurrentColor(255, 0, 0);
		else
			GetUserInterface()->SetCurrentColor(255, 255, 0);

		GetUserInterface()->SetCurrentFont(SMALL_FONT);
	}
	else
	{
		messagePosX = GetMiddle().X();
		messagePosX += GetSpeakRect().w / 2;
		messagePosY = GetSpeakRect().y + GetSpeakRect().h / ACTOR_SPEAK_DIVIDE_PART;
		GetUserInterface()->SetCurrentColor(0, 0, 0);
		GetUserInterface()->SetCurrentFont(BUBBLE_FONT);
	}

	
	GetUserInterface()->SetAlign(ALIGN_CENTER);
	GetUserInterface()->ShowText(GetMessageToSay(), messagePosX, messagePosY, alpha);
}

void Actor::Tick()
{
	UnHighlight();
}

void Actor::OnMouseOver()
{
	Highlight();
	GetUserInterface()->SetCursor(CursorType::CURSOR_HOVER);
}

void Actor::OnClick()
{
}

void Actor::OnRightClick()
{
}
