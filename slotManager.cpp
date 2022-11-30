#include "slotManager.h"
#include "camera.h"
#include "TrainingCrowManager.h"


SlotManager::SlotManager(God *god) : GodObject(god)
{
	m_pSlot = new Slot();
	m_pFlyingCrowManager = new FlyingCrowManager(god);
}

SlotManager::~SlotManager()
{
	delete m_pSlot;
	delete m_pFlyingCrowManager;
}

void SlotManager::Update()
{
	if (this->GetGod()->GetTrainingCrowManager()->GetBonus()) return;

	m_pSlot->Update();

	if (m_pSlot->GetShot())
	{
		m_pSlot->SetShot(false);
		int color = m_pSlot->GetColorType();
		m_pFlyingCrowManager->SetShotCrows(m_pSlot->GetColor(), 
			this->GetGod()->GetQuestBoardManager()->GetSerchBoard(color));
	}

	m_pFlyingCrowManager->Update();
}

void SlotManager::Draw(int type)
{
	switch (type)
	{
	case No_slot:
		m_pSlot->Draw();
		break;

	case No_FlyingCrow:
		m_pFlyingCrowManager->Draw();
		break;
	}
}
