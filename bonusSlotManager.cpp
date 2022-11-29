#include "bonusSlotManager.h"
#include "camera.h"
#include "TrainingCrowManager.h"

BonusSlotManager::BonusSlotManager(God * god) :GodObject(god)
{
	m_pSlot = new BonusSlot();
}

void BonusSlotManager::Update()
{
	if (this->GetGod()->GetTrainingCrowManager()->GetBonus())
	{
		m_pSlot->Update();
		
	}

}

void BonusSlotManager::Draw()
{
	m_pSlot->Draw();
}
