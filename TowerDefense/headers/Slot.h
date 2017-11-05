#ifndef _SLOT_
#define _SLOT_

#include "Actor.h"
#include "Tower.h"

#define SLOT_TEXTURE "assets/actors/slot.png"
#define SLOT_WIDTH 128
#define SLOT_HEIGHT 128
#define SLOT_SCALE 1

class Slot : public Actor
{
public:
	explicit Slot(Window* p_window = nullptr, GameInfo* p_gameInfo = nullptr);
	virtual ~Slot() {}

	void SetTower(Tower* p_newTower) { m_tower = p_newTower; }

	Tower* GetTower() const { return m_tower; }
	int GetTowerCost() const;

	bool CanCreateTower() const;

	void AddTower();
	void RemoveTower();

	void Display() override;
	void OnMouseOver() override;
	void OnClick() override;
	void Tick() override;

private:
	Tower* m_tower;
};

#endif // !_SLOT_
