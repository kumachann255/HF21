#include "slotManager.h"



SlotManager::SlotManager(God *god) : GodObject(god)
{
	m_pSlot = new Slot(god);
	m_pFlyingCrowManager = new FlyingCrowManager(god);
}

SlotManager::~SlotManager()
{
	delete m_pSlot;
	delete m_pFlyingCrowManager;
}

void SlotManager::Update()
{
	m_pSlot->Update();

	if (m_pSlot->GetShot())
	{
		m_pSlot->SetShot(false);
		m_pFlyingCrowManager->SetShotCrows(m_pSlot->GetColor());
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
