//=============================================================================
//
// プレハブ [prefab.h]
// Author： 柏村大地
//=============================================================================
// Objectクラスが持つ共通のデータ
// 主にモデルデータの読み込みとローカル座標の設定に使う
// ※ローカルの回転はよく使う
//=============================================================================
#pragma once
#include"model.h"
#include <string> 

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// クラス定義
//*****************************************************************************


class Prefab
{
	BOOL m_isLoadModel;	// モデル読み込み済みフラグ

	XMFLOAT3 m_pos;		// ローカル座標
	XMFLOAT3 m_rot;		// ローカル回転
	XMFLOAT3 m_scl;		// ローカル拡縮

	std::string m_name;	// ファイル名
	DX11_MODEL m_model;	// モデルデータ

public:
	Prefab();	
	~Prefab();	

	// ゲッター・セッター
	void SetModel(std::string modelName);		// モデル読み込み

	BOOL GetIsLoad(void) { return m_isLoadModel; }
	void SetIsLoad(BOOL flag) {  m_isLoadModel = flag; }

	void SetPos(XMFLOAT3 pos) { m_pos = pos; }
	XMFLOAT3 GetPos(void) { return m_pos; }
	void SetRot(XMFLOAT3 rot) { m_rot = rot; }
	XMFLOAT3 GetRot(void) { return m_rot; }
	void SetScl(XMFLOAT3 scl) { m_scl = scl; }
	XMFLOAT3 GetScl(void) { return m_scl; }

	void SetName(std::string name) { m_name = name; }
	void SetColor(XMFLOAT4 color);

	DX11_MODEL * GetModel(void) { return &m_model; }
	XMMATRIX GetMtxWorld(void) { return GetWorldMatrix(m_pos, m_rot, m_scl); }
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
