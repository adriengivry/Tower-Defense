#ifndef _TOWERBUTTON_
#define _TOWERBUTTON_

#include "Actor.h"
#include "Tower.h"

#define CASTLE_TOWER_PATH "assets/buttons/tower_button.png"
#define CASTLE_TOWER_X_POS 1797
#define CASTLE_TOWER_Y_POS 118

#define ARCHER_TOWER_PATH "assets/buttons/archer_tower_button.png"
#define ARCHER_TOWER_X_POS 1797
#define ARCHER_TOWER_Y_POS 260

#define BUTTON_X_SIZE 110
#define BUTTON_Y_SIZE 110

#define BUTTON_BASE_ALPHA 200
#define BUTTON_HOVER_ALPHA 255

class TowerButton : public Actor
{
public:
	explicit TowerButton(Window* p_window = nullptr, GameInfo* p_gameInfo = nullptr, const uint8_t p_type = TowerType::CASTLE_TOWER, const float p_x = 0, const float p_y = 0);
	~TowerButton() {}

	void SetType(const uint8_t p_value) { m_type = p_value; }

	uint8_t GetType() const { return m_type; }

	void Tick() override;
	void OnMouseOver() override;
	void OnClick() override;

private:
	uint8_t m_type;
	float m_rotateIncrement;
};

#endif // !_TOWERBUTTON_
