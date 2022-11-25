#include "trainingCrowDumbbell.h"

void TrainingCrowDumbbell::Update()
{
	if ((GetRot().x < m_wing_Rot.x) || (GetRot().x - DUMBBELL_MAX_ROT > m_wing_Rot.x))
	{
		m_vec *= -1.0f;
	}

	m_wing_Rot.x += DUMBBELL_SPEED * m_vec;
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
