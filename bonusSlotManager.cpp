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

	if (m_pSlot->GetHousing()->GetEnd())
	{
		this->GetGod()->GetTrainingCrowManager()->SetBonus(FALSE);
		m_pSlot->GetHousing()->SetEnt(FALSE);
	}
}

void BonusSlotManager::Draw()
{
	m_pSlot->Draw();
}
