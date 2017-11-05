#ifndef _FIELD_
#define _FIELD_

#include "Actor.h"

#define FIELD_TEXTURE "assets/field/background.png"
#define FIELD_X_POS 0
#define FIELD_Y_POS 0

class Field : public Actor
{
public:
	explicit Field(Window* p_window = nullptr, GameInfo* p_gameInfo = nullptr);
	~Field() {}

	void OnMouseOver() override;
};

#endif // !_FIELD_