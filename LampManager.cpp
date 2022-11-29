//=============================================================================
//
// ランプマネージャー処理 [LampManager.cpp]
// Author : 柏村大地
//
//=============================================================================
#include "LampManager.h"
#include "input.h"
#include "debugproc.h"
#include "QuestBoardManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LAMP_OFSETX		(20.0f)
#define LAMP_OFSETY		(70.0f)

//=============================================================================
// コンストラクタ
//=============================================================================
LampManager::LampManager(void)
{

	for (int i = 0; i < LAMP_MAX; i++)
	{

		//m_lamps[i].GetPrefab()->SetModel(g_ModelName[LAMP_TYPE_RED]);
		XMFLOAT3 pos = { -LAMP_OFSETX + (i*LAMP_OFSETX),LAMP_OFSETY,0.0f };
		m_lamps[i].GetPrefab()->SetPos(pos);
		m_lamps[i].SetIsUse(TRUE);

		//int colorId = rand() % 4;
		//m_lamps[i].SetColorTypeId(colorId);
		//m_lamps[i].GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[colorId];

	}

}

//=============================================================================
// デストラクター
//=============================================================================
LampManager::~LampManager()
{
	for (int i = 0; i < LAMP_MAX; i++)
	{
		//if (m_lamps[i])
		//{
		//	delete m_lamps[i];
		//}
	}

	for (int i = 0; i < LAMP_TYPE_MAX; i++)
	{
		if (m_Texture[i])
		{// テクスチャの解放
			m_Texture[i]->Release();
			m_Texture[i] = nullptr;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void LampManager::Update(void)
{
	for (int i = 0; i < LAMP_MAX; i++)
	{
		m_lamps[i].Update();
	}
}


//=============================================================================
// 描画処理
//=============================================================================
void LampManager::Draw(XMMATRIX WorldMatrix)
{
	for (int i = 0; i < LAMP_MAX; i++)
	{
		if (m_lamps[i].GetIsUse())
		{
			m_lamps[i].Draw(WorldMatrix);
		}
	}
}