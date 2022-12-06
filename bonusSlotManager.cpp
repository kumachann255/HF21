#include "bonusSlotManager.h"
#include "camera.h"
#include "TrainingCrowManager.h"
#include "slotManager.h"
#include "debugproc.h"
#include "texManager.h"

#define BONUS_COUNTDOWN_DESTANCE	(150)
#define BONUS_COUNTDOWN_START		(60)

BonusSlotManager::BonusSlotManager(God * god) :GodObject(god)
{
	m_pSlot = new BonusSlot();
	m_timer = new BonusTimer();
}

void BonusSlotManager::Update()
{
	if (this->GetGod()->GetTrainingCrowManager()->GetBonus())
	{
		m_pSlot->Update();

		m_countDownCount++;
		if (m_countDownCount == BONUS_COUNTDOWN_START) this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
			telop_1, texType_cutIn_up, m_telopPos, 2);
		else if (m_countDownCount == BONUS_COUNTDOWN_START + BONUS_COUNTDOWN_DESTANCE) this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
			telop_2, texType_cutIn_up, m_telopPos, 2);
		else if (m_countDownCount == BONUS_COUNTDOWN_START + BONUS_COUNTDOWN_DESTANCE * 2) this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
			telop_3, texType_cutIn_up, m_telopPos, 2);
		else if (m_countDownCount == BONUS_COUNTDOWN_START + BONUS_COUNTDOWN_DESTANCE * 3)
		{
			this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
				telop_1, texType_cutIn_up, m_telopPos, 2);
			SetTime();
		}

		if (m_isTimeMove)
		{
			// 時間計測
			clock_t time = clock();
			m_now = (float)(time - m_start) / CLOCKS_PER_SEC;
			m_now = MAX_BONUS_TIME - m_now;
			if (m_now < 0)
			{
				this->GetGod()->GetTrainingCrowManager()->SetBonus(FALSE);
				m_pSlot->GetHousing()->SetEnt(FALSE);
				m_pSlot->GetHousing()->ResetColor();
				m_isTimeMove = FALSE;
				m_countDownCount = 0;
			}
		}

#ifdef _DEBUG
		PrintDebugProc("[%f]:ボーナスチャンスの制限時間\n", m_now);
#endif
	}

	if (m_pSlot->GetHousing()->GetEnd())
	{
		this->GetGod()->GetTrainingCrowManager()->SetBonus(FALSE);
		m_pSlot->GetHousing()->SetEnt(FALSE);
		m_pSlot->GetHousing()->ResetColor();
		m_isTimeMove = FALSE;
		m_countDownCount = 0;

		this->GetGod()->GetSlotManager()->SetRainbowMode();
	}

	m_timer->SetTime(m_now);
	m_timer->Update();
}

void BonusSlotManager::Draw()
{
	m_pSlot->Draw();
	m_timer->Draw();
}

void BonusSlotManager::SetTime(void)
{
	m_start = clock();
	m_isTimeMove = TRUE;
}


