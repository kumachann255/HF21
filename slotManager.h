#pragma once
#include "main.h"
#include "GodObject.h"
#include "slot.h"
#include "FlyingCrowManager.h"
#include "bonusSlot.h"
#include "QuestBoardManager.h"

enum
{
	No_slot,
	No_FlyingCrow,
};


class SlotManager : GodObject
{
private:
	Slot *m_pSlot = nullptr;
	FlyingCrowManager *m_pFlyingCrowManager = nullptr;
	//QuestBoardManager *

public:
	SlotManager(God *god);
	~SlotManager();

	void Update();

	void Draw(int type);


};







