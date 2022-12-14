//=============================================================================
//
// オブジェクト処理 [object.cpp]
// Author： 
//
//=============================================================================
#include "Object.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************


//=============================================================================
// コンストラクタ
//=============================================================================
Object::Object()
{
	m_isUse = TRUE;

	m_pos = { 0.0f, 0.0f, 0.0f };
	m_rot = { 0.0f, 0.0f, 0.0f };
	m_scl = { 1.0f, 1.0f, 1.0f };

}


//=============================================================================
// デストラクタ
//=============================================================================
Object::~Object()
{
}


//=============================================================================
// 更新処理
//=============================================================================
void Object::Update(void)
{
	if (m_isUse == FALSE || m_prefab == NULL) return;
}


//=============================================================================
// 描画処理
//=============================================================================
void Object::Draw(void)
{
	if (!m_isUse || !m_prefab) return;

	SetDepthEnable(TRUE);

	// ラスタライザ設定
	SetCullingMode(CULL_MODE_NONE);
	//SetBlendState(BLEND_MODE_ADD);

	// ワールドマトリクス生成
	XMMATRIX mtxWorld = GetWorldMatrix(m_pos, m_rot, m_scl);

	// プレハブ(ローカル座標)にワールドマトリクスをかける
	mtxWorld = XMMatrixMultiply(m_prefab->GetMtxWorld(), mtxWorld);

	SetWorldMatrix(&mtxWorld);	// シェーダーにデータを送る

	DrawModel(m_prefab->GetModel());
}