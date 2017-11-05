#include "Field.h"

Field::Field(Window* p_window, GameInfo* p_gameInfo) : Actor(p_window)
{
	SetMovable(false);
	SetTickable(false);
	SetHoverable(true);

	SetPosition(FIELD_X_POS, FIELD_Y_POS);
	SetSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	SetTexture(FIELD_TEXTURE);

	SetGameInfo(p_gameInfo);
}

void Field::OnMouseOver()
{
	GetUserInterface()->SetTowerInfo();
	GetUserInterface()->SetShowTowerRange(false);
	GetUserInterface()->SetCursor(CursorType::CURSOR_NORMAL);
}
