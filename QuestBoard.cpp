//=============================================================================
//
// クエストボード処理 [QuestBoard.cpp]
// Author : 柏村大地
//
//=============================================================================
#include "QuestBoard.h"
#include "Roller.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	BOARD_ROTATE_SPEED	(0.001f)		// 回転速度
#define	BOARD_SCL			(3.0f)			// 大きさ
#define	ROLLER_RADIUS		(85.0f)			// ローラーの半径


//=============================================================================
// コンストラクター
//=============================================================================
QuestBoard::QuestBoard(std::string name , XMFLOAT3 pos, XMFLOAT3 rot)
{

	pLampManager = new LampManager;
	m_prefab = new Prefab;
	m_prefab->SetModel(name);
	XMFLOAT3 scl = { BOARD_SCL, BOARD_SCL, BOARD_SCL };

	m_prefab->SetPos(pos);
	m_prefab->SetRot(rot);
	m_prefab->SetScl(scl);

	SetIsUse(TRUE);
}

//=============================================================================
// デストラクター
//=============================================================================
QuestBoard::~QuestBoard()
{
	if (m_prefab) {
		delete m_prefab;
	}

	if (pLampManager) {
		delete pLampManager;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void QuestBoard::Update(void)
{

	XMFLOAT3 rot = { GetRot().x, 0.0f, 0.0f };
	rot.x += ROTATE_SPEED;
	SetRot(rot);
	if (rot.x >= XM_2PI)	rot.x = 0.0f;

	pLampManager->Update();
}


//=============================================================================
// 描画処理
//=============================================================================
void QuestBoard::Draw(XMMATRIX WorldMatrix)
{

	if (!GetIsUse())	return;

	SetCullingMode(CULL_MODE_BACK);

	SetDepthEnable(TRUE);

	SetBlendState(BLEND_MODE_NONE);

	// ワールドマトリクス生成
	XMMATRIX mtxWorld = GetWorldMatrix(m_prefab->GetPos(), m_prefab->GetRot(), m_prefab->GetScl());

	// プレハブ(ローカル座標)にワールドマトリクスをかける
	mtxWorld = XMMatrixMultiply(mtxWorld, WorldMatrix);

	// 座標を取り出す
	XMFLOAT3 pos = { mtxWorld.r[3].m128_f32[0], 
					 mtxWorld.r[3].m128_f32[1], 
					 mtxWorld.r[3].m128_f32[2] };

	SetPos(pos);

	//XMVECTOR r[4];
	//struct
	//{
	//	float _11, _12, _13, _14;
	//	float _21, _22, _23, _24;
	//	float _31, _32, _33, _34;
	//	float _41, _42, _43, _44;
	//};
	//float m[4][4];


	SetWorldMatrix(&mtxWorld);	// シェーダーにデータを送る

	DrawModel(m_prefab->GetModel());

	SetBlendState(BLEND_MODE_ALPHABLEND);
}
