#include "TrainingCrowManager.h"
#include "input.h"
#include "debugproc.h"

TrainingCrowManager::TrainingCrowManager(God * god) :GodObject(god)
{
	m_pTrainingCrowSquat = new TrainingCrowSquat(god);
	m_pTrainingCrowBench = new TrainingCrowBench(god);
	m_pTrainingCrowDumbbell = new TrainingCrowDumbbell(god);
	m_pRoom = new Room();
}

void TrainingCrowManager::Update()
{
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
	}

	if (GetKeyboardTrigger(DIK_U))
	{
		AddStock();
	}

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
		m_count++;
		if (m_count > BONUS_START_TIME)
		{
			m_count = 0; 
			m_isTrainingSuccess = FALSE;
			m_isBonus = TRUE;
		}
	}

	if (!m_isSpeedUp && !m_isTrainingSuccess && !m_isBonus)
	{
		if (UseStock())
		{
			m_isSpeedUp = TRUE;
		}
	}


	m_pRoom->Update();

#ifdef _DEBUG	// デバッグ情報を表示する
	PrintDebugProc("<%d>:ストック数\n",m_stock);
#endif


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
	}

	return ans;
}
