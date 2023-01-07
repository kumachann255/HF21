#include "TrainingCrowManager.h"
#include "input.h"
#include "debugproc.h"
#include "bonusSlotManager.h"
#include "texManager.h"
#include "sound.h"
#include "slotManager.h"

TrainingCrowManager::TrainingCrowManager(God * god) :GodObject(god)
{
	m_pTrainingCrowSquat = new TrainingCrowSquat(god);
	m_pTrainingCrowBench = new TrainingCrowBench(god);
	m_pTrainingCrowDumbbell = new TrainingCrowDumbbell(god);
	m_pRoom = new Room();
	m_pProteinIcon = new ProteinIcon();
}

TrainingCrowManager::~TrainingCrowManager()
{
	delete m_pTrainingCrowSquat;
	delete m_pTrainingCrowBench;
	delete m_pTrainingCrowDumbbell;
	delete m_pRoom;
	delete m_pProteinIcon;
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

	m_pProteinIcon->SetIconNum(m_stock);
	m_pProteinIcon->Update();

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

	if (!m_isSpeedUp && !m_isTrainingSuccess && !m_isBonus && !GetGod()->GetSlotManager()->GetRainbow())
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
	m_pProteinIcon->Draw();
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

		PlaySound(SOUND_LABEL_SE_se_training_hart);

		// プレゼン用1回目失敗　2回目成功
		if (m_failureCount == 0)
		{
			m_failureCount++;
		}
		else
		{
			m_failureCount = 0;
			m_isSuccess = TRUE;
		}

		// 本来
		//int probability = rand() % 10;

		//if (probability - m_failureCount < 2)
		//{
		//	m_failureCount = 0;
		//	this->GetGod()->GetTrainingCrowManager()->SetSuccess(TRUE);
		//}
		//else
		//{
		//	m_failureCount++;
		//}


	}

	return ans;
}

void TrainingCrowManager::Init()
{
	m_Type = No_Bench;

	m_isBonus = FALSE;
	m_isSpeedUp = FALSE;
	m_isTrainingSuccess = FALSE;
	m_count = 0;

	m_isSuccess = FALSE;
	m_isFalseTelop = FALSE;

	m_stock = 0;
	m_failureCount = 0;

	m_pTrainingCrowSquat->Init();
	m_pTrainingCrowBench->Init();
	m_pTrainingCrowDumbbell->Init();
}
