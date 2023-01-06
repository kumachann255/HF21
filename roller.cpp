//=============================================================================
//
// ローラー処理 [roller.cpp]
// Author : 柏村大地
//
//=============================================================================

#include "main.h"
#include "roller.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	ROLLER_SCL			(10.0f)			// ローラーの大きさ


//=============================================================================
// ローラークラス
//=============================================================================

Roller::Roller()
{
	// モデルの設定
	m_prefab = new Prefab;
	//m_prefab->SetModel(g_TextureName[0]);

	// ローカル設定
	XMFLOAT3 pos = { -50.0f, 0.0f, 0.0f };
	XMFLOAT3 rot = { 0.0f, 0.0f , 0.0f };
	XMFLOAT3 scl = { ROLLER_SCL*1.5, ROLLER_SCL, ROLLER_SCL };

	m_prefab->SetPos(pos);
	m_prefab->SetRot(rot);
	m_prefab->SetScl(scl);

	//SetIsUse(TRUE);

}

Roller::~Roller()
{
	if (m_prefab) { delete m_prefab; }
}



void Roller::Update(void)
{
	if (GetIsUse())
	{
		// ローカル回転
		static XMFLOAT3 rot = { 0.0f,XMConvertToRadians(225.0f), 0.0f };

		rot.x += ROTATE_SPEED;

		if (rot.x > XM_PI * 2)
		{
			rot.x = 0.0f;
		}

		m_prefab->SetRot(rot);
	}

}

void Roller::Draw(void)
{
	if (!GetIsUse()) return;

	SetDepthEnable(TRUE);

	// ラスタライザ設定
	SetCullingMode(CULL_MODE_BACK);

	XMFLOAT3 rot = { 0.0f, 0.0f , 0.0f };

	// ワールドマトリクス生成
	XMMATRIX mtxWorld = GetWorldMatrix(GetPos(), rot, GetScl());

	// プレハブ(ローカル座標)にワールドマトリクスをかける
	mtxWorld = XMMatrixMultiply(m_prefab->GetMtxWorld(), mtxWorld);

	SetWorldMatrix(&mtxWorld);	// シェーダーにデータを送る

	DrawModel(m_prefab->GetModel());

}
