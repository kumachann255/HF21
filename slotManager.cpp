#include "slotManager.h"
#include "camera.h"
#include "TrainingCrowManager.h"
#include "input.h"
#include "debugproc.h"
#include "texManager.h"
#include <time.h>


SlotManager::SlotManager(God *god) : GodObject(god)
{
	m_pSlot = new Slot();
	m_pFlyingCrowManager = new FlyingCrowManager(god);
	m_pRainbowTimer = new RainbowTimer();
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


	if (m_isRainbow)
	{
		m_pRainbowTimer->SetUse(TRUE);
		m_rainbowStartWait++;
	}

	if (m_rainbowStartWait == MAX_RAINBOW_STRAT_WAIT)
	{
		m_start = clock();
	}
	else if (m_rainbowStartWait > MAX_RAINBOW_STRAT_WAIT)
	{
		// 時間計測
		clock_t time = clock();
		m_now = (float)(time - m_start) / CLOCKS_PER_SEC;
		m_now = MAX_RAINBOW_TIME - m_now;

		m_pRainbowTimer->SetTime(m_now);

		if (m_now < 0.0f)
		{
			m_timeUpWait++;
			m_now = 0.0f;
			m_isRainbow = FALSE;

			this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
				telop_bonusChance, texType_zoomIn, XMFLOAT3(480.0f, 300.0f, 0.0f), 4);

			if (m_timeUpWait > MAX_RAINBOW_TIMEUP_WAIT)
			{
				m_pRainbowTimer->SetUse(FALSE);
			}

			if (m_timeUpWait == MAX_RAINBOW_TIMEUP_WAIT + MAX_RAINBOW_TIMEUP_WAIT / 2)
			{
				m_timeUpWait = 0;
				m_rainbowStartWait = 0;
				ResetRainbowMode();

				this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
					trandition_white, texType_fade, XMFLOAT3(744.0f, 350.0f, 0.0f), 4);
			}
		}
	}
}

void SlotManager::Draw(int type)
{
	switch (type)
	{
	case No_slot:
		m_pSlot->Draw();
		m_pRainbowTimer->Draw();
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
