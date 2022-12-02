//=============================================================================
//
// スタッフロール画面処理 [Staffroll.h]
// Author : 
//
//=============================================================================
#pragma once
#include "Scene.h"
#include "UI.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


class StaffRoll : public Scene
{
private:
	bool m_DebugSwich = true;	// デバッグモード切り替え用SW
	int m_DebugNum = 0;			// デバッグ用変数

public:
	StaffRoll(God * god);
	~StaffRoll();
	void Init();
	void Update();
	void Draw();
	void NextScene();


	void Scroll(float *posY);

	// デバッグ機構
	//int ChangeNum(int *Num);
	void DebugPrint(float posY);
	void PosCustom(float *posY);

};

struct s_StaffRoll
{
	BOOL		g_Use;		// TRUE:使っている  FALSE:未使用
	XMFLOAT3	g_Pos;		// ポリゴンの座標
	float		g_w, g_h;	// 幅と高さ
	int			g_TexNo;	// テクスチャ番号
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitStaffRoll(void);
void UninitStaffRoll(void);
void UpdateStaffRoll(void);
void DrawStaffRoll(void);


