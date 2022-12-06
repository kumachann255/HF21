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
		if (m_countDownCount == BONUS_COUNTDOWN_START)
		{
			this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
				telop_3, texType_cutIn_up, m_telopPos, 2);
			this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
				telop_guidance, texType_cutIn_right, m_telopPos2, 10);
		}
		else if (m_countDownCount == BONUS_COUNTDOWN_START + BONUS_COUNTDOWN_DESTANCE) this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
			telop_2, texType_cutIn_up, m_telopPos, 2);
		else if (m_countDownCount == BONUS_COUNTDOWN_START + BONUS_COUNTDOWN_DESTANCE * 2) this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
			telop_1, texType_cutIn_up, m_telopPos, 2);
		else if (m_countDownCount == BONUS_COUNTDOWN_START + BONUS_COUNTDOWN_DESTANCE * 3)
		{
			this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
				telop_3, texType_normal, m_telopPos, 2);
			SetTime();
		}

		if (m_pSlot->GetHousing()->GetTimeStop())
		{
			m_isTimeMove = FALSE;
			m_pSlot->GetHousing()->SetTimeStop(FALSE);
		}

		if (m_isTimeMove)
		{
			// 時間計測
			clock_t time = clock();
			m_now = (float)(time - m_start) / CLOCKS_PER_SEC;
			m_now = MAX_BONUS_TIME - m_now;
			if (m_now < 0.0f)
			{
				m_timeUpWait++;
				m_now = 0.0f;

				this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
					telop_bonusChance, texType_cutIn_up, m_telopPos4, 3);
			}

			if (m_timeUpWait == MAX_TIMEUP_WAIT - TRANSITION_HALF_TIME)
			{
				this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
					trandition_crow, texType_tansition, m_transitionPos, TRANSITION_TIME_SEC);
			}

			if (m_timeUpWait > MAX_TIMEUP_WAIT)
			{
				this->GetGod()->GetTrainingCrowManager()->SetBonus(FALSE);
				m_pSlot->GetHousing()->SetEnt(FALSE);
				m_pSlot->GetHousing()->ResetColor();
				m_isTimeMove = FALSE;
				m_countDownCount = 0;
				m_timeUpWait = 0;
			}
		}

#ifdef _DEBUG
		PrintDebugProc("[%f]:ボーナスチャンスの制限時間\n", m_now);
#endif
	}

	if (m_pSlot->GetHousing()->GetTransition())
	{
		this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
			trandition_whiteFull, texType_fade, m_transitionPos2, TRANSITION_TIME_SEC);

		m_pSlot->GetHousing()->SetTransition(FALSE);
	}

	if (m_pSlot->GetHousing()->GetEnd())
	{
		this->GetGod()->GetTrainingCrowManager()->SetBonus(FALSE);
		m_pSlot->GetHousing()->SetEnt(FALSE);
		m_pSlot->GetHousing()->ResetColor();
		m_isTimeMove = FALSE;
		m_countDownCount = 0;

		this->GetGod()->GetSlotManager()->SetRainbowMode();

		this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
			trandition_white, texType_fade, m_telopPos3, 4);

		this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
			telop_bonusChance, texType_cutIn_up, m_telopPos, 4);

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


