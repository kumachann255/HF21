#include "TrainingCrowManager.h"
#include "input.h"
#include "debugproc.h"
#include "bonusSlotManager.h"
#include "texManager.h"

TrainingCrowManager::TrainingCrowManager(God * god) :GodObject(god)
{
	m_pTrainingCrowSquat = new TrainingCrowSquat(god);
	m_pTrainingCrowBench = new TrainingCrowBench(god);
	m_pTrainingCrowDumbbell = new TrainingCrowDumbbell(god);
	m_pRoom = new Room();
}

void TrainingCrowManager::Update()
{
#ifdef _DEBUG	// デバッグ情報を表示する
	PrintDebugProc("<%d>:ストック数\n", m_stock);

	if (GetKeyboardTrigger(DIK_T))
	{
		m_Type++;
		m_Type %= No_TrainingMax;
	}

	if (GetKeyboardTrigger(DIK_B))
	{
		if(!m_isBonus) m_isBonus = TRUE;
		else m_isBonus = FALSE;
	}

	if (GetKeyboardTrigger(DIK_S))
	{
		if (!m_isSpeedUp) m_isSpeedUp = TRUE;
		else
		{
			m_isSpeedUp = FALSE;
		}
		SetSuccess(TRUE);
	}

	if (GetKeyboardTrigger(DIK_U))
	{
		AddStock();
	}
#endif

	switch (m_Type)
	{
	case No_Squat:
		m_pTrainingCrowSquat->Update();
		break;

	case No_Bench:
		m_pTrainingCrowBench->Update();
		break;

	case No_Dumbbell:
		m_pTrainingCrowDumbbell->Update();
		break;
	}

	if (m_isTrainingSuccess)
	{
		m_isTrainingSuccess = FALSE;
		m_isBonus = TRUE;
		m_isSuccess = FALSE;
	}

	if (!m_isSpeedUp && !m_isTrainingSuccess && !m_isBonus)
	{
		if (UseStock())
		{
			m_isSpeedUp = TRUE;
		}
	}

	m_pRoom->Update();
}

void TrainingCrowManager::Draw()
{
	switch (m_Type)
	{
	case No_Squat:
		m_pTrainingCrowSquat->Draw();
		break;

	case No_Bench:
		m_pTrainingCrowBench->Draw();
		break;

	case No_Dumbbell:
		m_pTrainingCrowDumbbell->Draw();
		break;
	}
	
	m_pRoom->Draw();
}

BOOL TrainingCrowManager::UseStock(void)
{
	BOOL ans = FALSE;

	if (m_stock > 0)
	{
		m_stock--;
		ans = TRUE;
		m_isFalseTelop = FALSE;

		SetTrainingTypeRandom();

		this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
			telop_evolution, texType_cutIn_up, XMFLOAT3(744.0f, 20.0f, 0.0f), 4);

	}

	return ans;
}
