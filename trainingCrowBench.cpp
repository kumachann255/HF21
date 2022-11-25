#include "trainingCrowBench.h"

void TrainingCrowBench::Update()
{
	if ((GetPos().y < m_wing_Pos.y) || (GetPos().y - BENCH_MAX_HEIGHT > m_wing_Pos.y))
	{
		m_vec *= -1.0f;
	}

	m_wing_Pos.y += BENCH_SPEED * m_vec;
	m_barbell_Pos.y += BENCH_SPEED * m_vec;

}

void TrainingCrowBench::Draw()
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
		XMFLOAT3 pos = m_wing_Pos;
		pos.y += BENCH_Y_OFFSET;
		// ワールドマトリクス生成
		XMMATRIX mtxWorld = GetWorldMatrix(pos, GetRot(), GetScl());

		// プレハブ(ローカル座標)にワールドマトリクスをかける
		mtxWorld = XMMatrixMultiply(m_prefabWing->GetMtxWorld(), mtxWorld);

		SetWorldMatrix(&mtxWorld);	// シェーダーにデータを送る

		DrawModel(m_prefabWing->GetModel());
	}

	// バーベルの描画
	{
		XMFLOAT3 pos = m_barbell_Pos;
		pos.y += BENCH_Y_OFFSET;
		// ワールドマトリクス生成
		XMMATRIX mtxWorld = GetWorldMatrix(pos, GetRot(), GetScl());

		// プレハブ(ローカル座標)にワールドマトリクスをかける
		mtxWorld = XMMatrixMultiply(m_prefabbarbell->GetMtxWorld(), mtxWorld);

		SetWorldMatrix(&mtxWorld);	// シェーダーにデータを送る

		DrawModel(m_prefabbarbell->GetModel());
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
