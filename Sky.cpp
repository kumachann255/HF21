//=============================================================================
//
// Sky管理 [Sky.cpp]
// Author : 
//
//=============================================================================
#include"Sky.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	SKY_ROTATE_SPEED	(0.001f)		// 回転速度
#define	SKY_SCL				(4.0f)			// 大きさ



//=============================================================================
// コンストラクター
//=============================================================================
Sky::Sky()
{
	m_prefab = new Prefab;
	//m_prefab->SetModel("model_sky_spring_01.obj");

	XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 scl = { SKY_SCL, SKY_SCL, SKY_SCL };

	m_prefab->SetPos(pos);
	m_prefab->SetRot(rot);
	m_prefab->SetScl(scl);

}

//=============================================================================
// デストラクター
//=============================================================================
Sky::~Sky()
{
	if (m_prefab) {
		delete m_prefab; 
		m_prefab = nullptr;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Sky::Update(void)
{

	// ローカル回転
	XMFLOAT3 rot2 = GetRot();
	rot2.y += SKY_ROTATE_SPEED;

	if (rot2.y >= XM_PI * 2) { rot2.y = 0.0f; }

	SetRot(rot2);


}


//=============================================================================
// 描画処理
//=============================================================================
void Sky::Draw(void)
{
	// ラスタライザ設定
	SetCullingMode(CULL_MODE_FRONT);	//表のポリゴンを描画しない

	SetDepthEnable(TRUE);

	// ワールドマトリクス生成
	XMMATRIX mtxWorld = GetWorldMatrix(GetPos(), GetRot(), GetScl());

	// プレハブ(ローカル座標)にワールドマトリクスをかける
	mtxWorld = XMMatrixMultiply(mtxWorld, m_prefab->GetMtxWorld());

	SetWorldMatrix(&mtxWorld);	// シェーダーにデータを送る

	DrawModel(m_prefab->GetModel());

	SetCullingMode(CULL_MODE_BACK);		//カリングを戻す


}
