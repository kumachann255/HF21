#pragma once
#include "main.h"
#include "bonusSlotManager.h"
#include "QuestBoardManager.h"
#include "TrainingCrowManager.h"
#include "slotManager.h"
#include "GodObject.h"

class EventManager : public GodObject
{
private:
	QuestBoardManager *m_pQuestBoardManager = nullptr;
	TrainingCrowManager *m_pTrainingCrowManager = nullptr;
	SlotManager *m_pSlotManager = nullptr;
	BonusSlotManager *m_pBonusSlotManager = nullptr;


public:
	EventManager(God *god);
	~EventManager();

	void Update();

};