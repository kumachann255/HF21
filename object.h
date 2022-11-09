//=============================================================================
//
// オブジェクト処理 [Object.h]
// Author： 
//=============================================================================
// オブジェクトの基底クラス(このクラスを"継承"してオブジェクトを生成します)
// プレハブデータ( モデルデータ読み込み と ローカル座標の変換 )を持ちます。
//  Draw() 関数でワールドマトリクスを生成してそのままドローコールしています。
//  Update()関数は継承先で自由にオーバーライドしてください。
//=============================================================================
#pragma once

#include "main.h"
#include "Prefab.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// クラス定義
//*****************************************************************************

class Object
{
private:
	BOOL m_isUse;			// 使用中フラグ

	XMFLOAT3 m_pos;			// ワールド座標
	XMFLOAT3 m_rot;			// ワールド回転
	XMFLOAT3 m_scl;			// ワールド拡縮

	XMMATRIX m_mtxWorld;	// ワールドマトリクス

protected:
	Prefab *m_prefab;		// プレハブデータ( モデルデータ読み込み と ローカル座標の変換 )
public:

	// コンストラクタ・デストラクタ
	Object();
	virtual ~Object();

	// ゲッター・セッター
	BOOL GetIsUse(void) { return m_isUse; }
	void SetIsUse(BOOL flag) {  m_isUse = flag; }

	virtual void SetPos(XMFLOAT3 pos) { m_pos = pos; }
	XMFLOAT3 GetPos(void) { return m_pos; }
	void SetRot(XMFLOAT3 rot) { m_rot = rot; }
	XMFLOAT3 GetRot(void) { return m_rot; }
	void SetScl(XMFLOAT3 scl) { m_scl = scl; }
	XMFLOAT3 GetScl(void) { return m_scl; }
	void SetSRT(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl) { m_pos = pos; m_rot = rot; m_scl = scl; }

	XMMATRIX GetMtxWorld(void) { return m_mtxWorld; }
	void SetMtxWorld(void) { m_mtxWorld = GetWorldMatrix(m_pos, m_rot, m_scl); }

	void SetPrefab(Prefab * prefab) { m_prefab = prefab; }
	Prefab * GetPrefab(void) { return m_prefab; }
	void SetPrefabPos(XMFLOAT3 pos) { m_prefab->SetPos(pos); }
	void SetPrefabRot(XMFLOAT3 rot) { m_prefab->SetRot(rot); }

	// メンバ関数
	virtual void Update(void);
	virtual void Draw(void);
};

