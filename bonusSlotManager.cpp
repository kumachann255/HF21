#include "bonusSlotManager.h"
#include "camera.h"
#include "TrainingCrowManager.h"
#include "slotManager.h"
#include "debugproc.h"
#include "texManager.h"
#include "sound.h"

#define BONUS_COUNTDOWN_DESTANCE	(150)
#define BONUS_COUNTDOWN_START		(60)

BonusSlotManager::BonusSlotManager(God * god) :GodObject(god)
{
	m_pSlot = new BonusSlot();
	m_timer = new BonusTimer();

	//炎初期化
	{
		m_pSolverGPU = new FLUID3D_GPU;

		m_pSolverGPU->Init(GetDevice(), GetDeviceContext(), SCREEN_WIDTH, SCREEN_HEIGHT
			, GetRenderTargetView(), GetDepthStencilView());

		m_pSolverGPU->SetInitFlag(TRUE);

		XMFLOAT3 pos = { -55.0f,-15.0f,30.0f };
		XMFLOAT3 scl = { 110.0f,50.0f,100.0f };

		m_pSolverGPU->SetPos(pos);
		m_pSolverGPU->SetScl(scl);
	}

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
			PlaySound(SOUND_LABEL_SE_se_se_countDown);
		}
		else if (m_countDownCount == BONUS_COUNTDOWN_START + BONUS_COUNTDOWN_DESTANCE) {
			this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
				telop_2, texType_cutIn_up, m_telopPos, 2);
			PlaySound(SOUND_LABEL_SE_se_se_countDown);
		}
		else if (m_countDownCount == BONUS_COUNTDOWN_START + BONUS_COUNTDOWN_DESTANCE * 2) {
			this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
				telop_1, texType_cutIn_up, m_telopPos, 2);
			PlaySound(SOUND_LABEL_SE_se_se_countDown);
		}
		else if (m_countDownCount == BONUS_COUNTDOWN_START + BONUS_COUNTDOWN_DESTANCE * 3)
		{
			this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
				telop_3, texType_normal, m_telopPos, 2);
			SetTime();
			PlaySound(SOUND_LABEL_SE_se_bom4);
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

				if (m_timeUpWait == 1)
				{
					this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
						telop_bonusChanceFalse, texType_cutIn_up, m_telopPos4, 6);
				}
			}

			if (m_timeUpWait == MAX_TIMEUP_WAIT - TRANSITION_HALF_TIME)
			{
				this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
					trandition_crow, texType_tansition, m_transitionPos, TRANSITION_TIME_SEC);
			}

			// 失敗して通常シーンに戻る際の処理
			if (m_timeUpWait > MAX_TIMEUP_WAIT)
			{
				this->GetGod()->GetTrainingCrowManager()->SetBonus(FALSE);
				m_pSlot->GetHousing()->SetEnt(FALSE);
				m_pSlot->GetHousing()->ResetColor();
				m_isTimeMove = FALSE;
				m_countDownCount = 0;
				m_timeUpWait = 0;

				// 炎関連
				// 初期化していなかったら
				if (!m_pSolverGPU->GetInitFlag())
				{
					m_pSolverGPU->SetUse(FALSE);	 // 使用しない
					m_pSolverGPU->Clear(GetDevice());// 初期化
					m_pSolverGPU->SetInitFlag(TRUE); //　初期化した
				}

			}
		}

#ifdef _DEBUG
		PrintDebugProc("[%f]:ボーナスチャンスの制限時間\n", m_now);
#endif


		//炎関連
		{
			if (m_pSolverGPU->GetUseFlag())
			{
				m_pSolverGPU->AddDensitySource(XMFLOAT4(2, 99, 2, 5.0f), XMFLOAT4(0.10f, 0.10f, 0.10f, 0.0f));
				m_pSolverGPU->AddVelocitySource(XMFLOAT4(2, 99, 2, 5.0f), XMFLOAT4(3.0f, -3.0f, 3.0f, 0.0f));
				m_pSolverGPU->Solve();
			}

			// 初期化されていたら
			if (m_pSolverGPU->GetInitFlag())
			{
				m_pSolverGPU->SetUse(TRUE);		  // 使用する
				m_pSolverGPU->SetInitFlag(FALSE); // 初期化フラグOFF

			}

		}

	}

	if (m_pSlot->GetHousing()->GetTransition())
	{
		this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
			trandition_whiteFull, texType_fade, m_transitionPos2, TRANSITION_TIME_SEC);

		m_pSlot->GetHousing()->SetTransition(FALSE);
	}

	// 成功して通常シーンに戻る際の処理
	if (m_pSlot->GetHousing()->GetEnd() &&
	   this->GetGod()->GetTrainingCrowManager()->GetBonus())
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
			telop_bonusChance, texType_zoomIn_Update, m_telopPos, 4);

		// 炎関連
		// 初期化していなかったら
		if (!m_pSolverGPU->GetInitFlag())
		{
			m_pSolverGPU->SetUse(FALSE);	 // 使用しない
			m_pSolverGPU->Clear(GetDevice());// 初期化
			m_pSolverGPU->SetInitFlag(TRUE); //　初期化した
		}

	}

	m_timer->SetTime(m_now);
	m_timer->Update();

}

void BonusSlotManager::Draw()
{
	m_pSlot->Draw();
	m_timer->Draw();

	// 炎描画
	m_pSolverGPU->DrawFluid();

	// シェーダーを戻す
	SetShader(SHADER_MODE_PHONG);
}

void BonusSlotManager::SetTime(void)
{
	m_start = clock();
	m_isTimeMove = TRUE;
}


