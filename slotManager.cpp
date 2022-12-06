#include "slotManager.h"
#include "camera.h"
#include "TrainingCrowManager.h"
#include "input.h"
#include "debugproc.h"


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


#ifdef _DEBUG	// デバッグ情報を表示する
	if ((GetKeyboardTrigger(DIK_R)))
	{
		if (!m_isRainbow) m_isRainbow = TRUE;
		else m_isRainbow = FALSE;
	}

	if (m_isRainbow) PrintDebugProc("[TRUE]:レインボーカラースモード\n");
	else PrintDebugProc("[FALSE]:レインボーカラースモード\n");

#endif

	m_pSlot->Update();

	if (m_isRainbow) m_pSlot->GetHousing()->SetRainbow(TRUE);
	else m_pSlot->GetHousing()->SetRainbow(FALSE);

	int CrowNum = m_pSlot->GetCrowNum();
	if (m_isRainbow) CrowNum = 3;

	if (m_pSlot->GetShot())
	{
		for (int i = 0; i < CrowNum; i++)
		{
			m_pSlot->SetShot(false);
			int color = m_pSlot->GetColorType();

			if (!m_isRainbow)
			{
				m_pFlyingCrowManager->SetShotCrows(m_pSlot->GetColor(),
					this->GetGod()->GetQuestBoardManager()->GetSerchBoard(color), i);
			}
			else
			{
				m_pFlyingCrowManager->SetShotCrows(m_pSlot->GetColor(),
					this->GetGod()->GetQuestBoardManager()->GetSerchBoardRainbow(), i);
			}
		}
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

void SlotManager::SetRainbowMode(void)
{
	m_isRainbow = TRUE;
	m_pSlot->SetRainbowModel();
}

void SlotManager::ResetRainbowMode(void)
{
	m_isRainbow = FALSE;
	m_pSlot->ResetRainbowModel();
}
