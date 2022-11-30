#include "eventManager.h"
#include "bonusSlotManager.h"
#include "FlyingCrowManager.h"
#include "QuestBoardManager.h"
#include "TrainingCrowManager.h"
#include "slotManager.h"
#include "GodObject.h"

EventManager::EventManager(God *god) : GodObject(god)
{
	m_pQuestBoardManager = this->GetGod()->GetQuestBoardManager();
	m_pTrainingCrowManager = this->GetGod()->GetTrainingCrowManager();
	m_pSlotManager = this->GetGod()->GetSlotManager();
	m_pBonusSlotManager = this->GetGod()->GetBonusSlotManager();
}

EventManager::~EventManager()
{
}

void EventManager::Update()
{

}
