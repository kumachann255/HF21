#pragma once
#include "main.h"
#include "GodObject.h"
#include "slot.h"
#include "FlyingCrowManager.h"
#include "Morphing.h"
#include "bonusSlot.h"

class BonusSlotManager : GodObject
{
private:
	BonusSlot *m_pSlot = nullptr;


public:
	BonusSlotManager(God *god);

	~BonusSlotManager() { delete m_pSlot; };

	void Update();
	void Draw();
};