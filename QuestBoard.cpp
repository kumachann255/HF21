//=============================================================================
//
// クエストボード処理 [QuestBoard.cpp]
// Author : 柏村大地
//
//=============================================================================
#include "QuestBoard.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	BOARD_ROTATE_SPEED	(0.001f)		// 回転速度
#define	BOARD_SCL			(0.6f)			// 大きさ
#define	ROLLER_RADIUS		(85.0f)			// ローラーの半径


//=============================================================================
// コンストラクター
//=============================================================================
QuestBoard::QuestBoard(std::string name , XMFLOAT3 pos)
{

	m_prefab = new Prefab;
	m_prefab->SetModel(name);

	//XMFLOAT3 rot = { 0.0f, XMConvertToRadians(45.0f), XMConvertToRadians(-30.0f) };
	XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 scl = { BOARD_SCL, BOARD_SCL, BOARD_SCL };

	m_prefab->SetPos(pos);
	m_prefab->SetRot(rot);
	m_prefab->SetScl(scl);

	//XMFLOAT4 color = { 1.0f,0.0f,0.0f,1.0f };
	//m_prefab->SetColor(color);
}

//=============================================================================
// デストラクター
//=============================================================================
QuestBoard::~QuestBoard()
{
	if (m_prefab) {
		delete m_prefab;
		m_prefab = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void QuestBoard::Update(void)
{
	//m_time += 0.01f;
	//if (m_time >= XM_2PI)	m_time = 0.0f;

	//m_pos.y = ROLLER_RADIUS * sinf(m_time);
	//m_pos.z = ROLLER_RADIUS * cosf(m_time);
	//m_prefab->SetPos(m_pos);

	//m_rot = { -m_time * 0.25f,XMConvertToRadians(45.0f), XMConvertToRadians(3.0f) };
	//m_prefab->SetRot(m_rot);

}


//=============================================================================
// 描画処理
//=============================================================================
void QuestBoard::Draw(XMMATRIX WorldMatrix)
{
	SetCullingMode(CULL_MODE_NONE);		//カリングなし

	SetDepthEnable(TRUE);

	// ワールドマトリクス生成
	XMMATRIX mtxWorld = GetWorldMatrix(m_prefab->GetPos(), m_prefab->GetRot(), m_prefab->GetScl());

	// プレハブ(ローカル座標)にワールドマトリクスをかける
	mtxWorld = XMMatrixMultiply(mtxWorld, WorldMatrix);

	SetWorldMatrix(&mtxWorld);	// シェーダーにデータを送る

	DrawModel(m_prefab->GetModel());

	SetCullingMode(CULL_MODE_BACK);		//カリングを戻す

}
