#include "trainingCrowDumbbell.h"
#include "TrainingCrowManager.h"
#include "texManager.h"
#include "sound.h"

void TrainingCrowDumbbell::Update()
{
	if (this->GetGod()->GetTrainingCrowManager()->GetIsSpeedUp())
	{
		m_isUp = TRUE;
		if (m_speed < MAX_DUMBBELL_SPEED) m_speed += ADD_DUMBBELL_SPEED;
		else
		{
			m_count++;
		}
	}
	else
	{
		m_speed = DUMBBELL_SPEED;
		m_count = 0;
		
		if (m_isUp)
		{
			m_isUp = FALSE;
			m_wing_Rot = { 0.0f, 3.14f *  0.75f, 0.0f };
		}
	}

	if (m_speed < MAX_DUMBBELL_SPEED)
	{
		if ((GetRot().x + DUMBBELL_MAX_ROT < m_wing_Rot.x) || (GetRot().x - DUMBBELL_MAX_ROT > m_wing_Rot.x))
		{
			m_vec *= -1.0f;
		}
	}
	else
	{
		m_vec = -1.0f;
	}

	if (m_count < MAX_DUMBBELL_MAXSPEED_TIME)
	{
		m_wing_Rot.x += m_speed * m_vec;
	}
	else if(this->GetGod()->GetTrainingCrowManager()->GetSuccess())
	{
		m_wing_Rot.x = GetRot().x - 1.72f;
		m_waitCount++;

		StopSound(SOUND_LABEL_SE_se_training_hart);

		if (m_waitCount == 1)
		{
			this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
				telop_bonusChance, texType_zoomIn_rot, XMFLOAT3(480.0f, 400.0f, 0.0f), 5);

			PlaySound(SOUND_LABEL_SE_se_zyan);
		}

		if (m_waitCount == WAIT_SQUAT_TIME * 4 - TRANSITION_HALF_TIME)
		{
			this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
				trandition_crow, texType_tansition, XMFLOAT3(-TRANSITION_WIDTH, 270.0f, 0.0f), 4);
			PlaySound(SOUND_LABEL_SE_se_crow_25s);
		}

		if (m_waitCount > WAIT_SQUAT_TIME * 4)
		{
			this->GetGod()->GetTrainingCrowManager()->SetIsSpeedUp(FALSE);
			this->GetGod()->GetTrainingCrowManager()->SetBonusStart();
			m_waitCount = 0;
			m_speed = DUMBBELL_SPEED;
			m_count = 0;
		}
	}
	else if(this->GetGod()->GetTrainingCrowManager()->GetIsSpeedUp())
	{
		m_wing_Rot.x = GetRot().x + 0.72f;
		m_waitCount++;

		StopSound(SOUND_LABEL_SE_se_training_hart);

		if (!GetGod()->GetTrainingCrowManager()->GetFalseTelop())
		{
			GetGod()->GetTrainingCrowManager()->SetFalseTelop(TRUE);

			this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
				telop_wing, texType_cutIn_up, XMFLOAT3(744.0f, 20.0f, 0.0f), 4);
			PlaySound(SOUND_LABEL_SE_se_training_false);
		}

		if (m_waitCount > WAIT_SQUAT_TIME * 4)
		{
			this->GetGod()->GetTrainingCrowManager()->SetIsSpeedUp(FALSE);
			m_waitCount = 0;
			m_speed = DUMBBELL_SPEED;
			m_count = 0;
		}
	}
}

void TrainingCrowDumbbell::Draw()
{
	if (!m_prefab) return;

	SetDepthEnable(TRUE);

	// ラスタライザ設定
	SetCullingMode(CULL_MODE_NONE);
	//SetBlendState(BLEND_MODE_ADD);

	// 胴体の描画
	{
		// ワールドマトリクス生成
		XMMATRIX mtxWorld = GetWorldMatrix(GetPos(), GetRot(), GetScl());

		// プレハブ(ローカル座標)にワールドマトリクスをかける
		mtxWorld = XMMatrixMultiply(m_prefab->GetMtxWorld(), mtxWorld);

		SetWorldMatrix(&mtxWorld);	// シェーダーにデータを送る

		DrawModel(m_prefab->GetModel());
	}

	// 羽の描画
	{
		// ワールドマトリクス生成
		XMMATRIX mtxWorld = GetWorldMatrix(m_wing_Pos, m_wing_Rot, GetScl());

		// プレハブ(ローカル座標)にワールドマトリクスをかける
		mtxWorld = XMMatrixMultiply(m_prefabWing->GetMtxWorld(), mtxWorld);

		SetWorldMatrix(&mtxWorld);	// シェーダーにデータを送る

		DrawModel(m_prefabWing->GetModel());
	}

	// ベンチの描画
	{
		// ワールドマトリクス生成
		XMMATRIX mtxWorld = GetWorldMatrix(GetPos(), GetRot(), GetScl());

		// プレハブ(ローカル座標)にワールドマトリクスをかける
		mtxWorld = XMMatrixMultiply(m_prefabBench->GetMtxWorld(), mtxWorld);

		SetWorldMatrix(&mtxWorld);	// シェーダーにデータを送る

		DrawModel(m_prefabBench->GetModel());
	}
}

void TrainingCrowDumbbell::Init()
{
	m_vec = 1.0f;
	m_speed = DUMBBELL_SPEED;
	m_count = 0;
	m_isUp = FALSE;
	m_waitCount = 0;
}
