#include "TrainingCrowManager.h"
#include "input.h"

TrainingCrowManager::TrainingCrowManager(God * god) :GodObject(god)
{
	m_pTrainingCrowSquat = new TrainingCrowSquat(god);
	m_pTrainingCrowBench = new TrainingCrowBench(god);
	m_pTrainingCrowDumbbell = new TrainingCrowDumbbell(god);




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
	
}
