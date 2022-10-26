//=============================================================================
//
// プレハブ [prefab.cpp]
// Author： 
//
//=============================================================================
#include "prefab.h"


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
Prefab::Prefab()
{
	m_isLoadModel = FALSE;

	m_pos = { 0.0f, 0.0f, 0.0f };
	m_rot = { 0.0f, 0.0f, 0.0f };
	m_scl = { 1.0f, 1.0f, 1.0f };
}


//=============================================================================
// デストラクタ
//=============================================================================
Prefab::~Prefab()
{
	// モデルデータ解放
	if (m_isLoadModel)
	{
		UnloadModel(&m_model);
		m_isLoadModel = FALSE;
	}
}


//=============================================================================
// モデル読み込み処理
//=============================================================================
void Prefab::SetModel(std::string modelName)
{
	char path[256] = "data/MODEL/";

	// strcat(文字連結)の引数はポインターなので
	// c_str()でcharのポインタを取り出しています。
	LoadModel(strcat(path, modelName.c_str()), &m_model);

	m_name = modelName;

	m_isLoadModel = TRUE;
}
