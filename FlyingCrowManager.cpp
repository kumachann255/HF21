//=============================================================================
//
// カラース管理処理 [FlyingCrowManager.cpp]
// Author : 
//
//=============================================================================
#include "FlyingCrowManager.h"
#include "input.h"

//=============================================================================
// コンストラクタ
//=============================================================================
FlyingCrowManager::FlyingCrowManager(God *god):GodObject(god)
{
	m_pFlyingCrow = new FlyingCrow[CROWS_MAX];

	for (int i = 0; i < CROWS_MAX; i++)
	{
		m_pFlyingCrow[i].GetPrefab()->SetModel("model_crow.obj");
		m_pFlyingCrow[i].SetIsUse(FALSE);
	}

}

//=============================================================================
// デストラクター
//=============================================================================
FlyingCrowManager::~FlyingCrowManager()
{
	// 配列のデリート
	delete[] m_pFlyingCrow;

}

//=============================================================================
// 更新処理
//=============================================================================
void FlyingCrowManager::Update(void)
{

	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };

	// 空飛ぶカラスの更新
	for (int i = 0; i < CROWS_MAX; i++)
	{
		if (m_pFlyingCrow[i].GetIsUse())
		{
			m_pFlyingCrow[i].Update();

			// リセット処理
			if (m_pFlyingCrow[i].GetTime() >= 1.0f)
			{
				m_pFlyingCrow[i].SetIsUse(FALSE);
				m_pFlyingCrow[i].SetPos(pos);
				m_pFlyingCrow[i].ResetControlPos();

			}
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void FlyingCrowManager::Draw(void)
{
	// 空飛ぶカラスの描画処理
	for (int i = 0; i < CROWS_MAX; i++)
	{
		if (m_pFlyingCrow[i].GetIsUse())
		{
			m_pFlyingCrow[i].Draw();
		}
	}

}

//=============================================================================
// 生成処理
//=============================================================================
void FlyingCrowManager::SetShotCrows(XMFLOAT4 color)
{
	int a = rand() % (CROWS_MAX - 2) + 2;

	for (int i = 0; i < a; i++)
	{
		if (!m_pFlyingCrow[i].GetIsUse())
		{

			XMFLOAT3 targetPos = { -50.0f, 20.0f, -100.0f };
			XMFLOAT3 scl = { 0.5f,0.5f,0.5f };
			float speed = (float)(rand() % FLYINGCROW_SPEED_MAX + 10) * 0.001f;

			// パラメーターのセット
			m_pFlyingCrow[i].SetIsUse(TRUE);
			m_pFlyingCrow[i].SetControlPos();
			m_pFlyingCrow[i].SetScl(scl);
			m_pFlyingCrow[i].SetTargetPos(targetPos);
			m_pFlyingCrow[i].SetColor(color);
			m_pFlyingCrow[i].SetSpeed(speed);
			m_pFlyingCrow[i].SetTime(0.0f);
		}
	}

}
