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
#define MAX_STOPTIME		(100)
#define STAFFROLL_MAX		(13)				// テクスチャの数
#define CHECK_MAX			(5)

enum StaffRoll_enum
{
	RESULT	= 0,
	GOLD	= 1,
	SILVER	= 2,
	BRONSE	= 3,
	BLUE	= 4,
	GREEN	= 5,
	ENDROLL = 6
};

class StaffRoll : public Scene
{
private:
	int m_Mode = RESULT;
	bool m_ScrollSw = false;	// スクロール開始用SW
	bool m_DebugSwich = true;	// デバッグモード切り替え用SW
	int m_DebugNum = 0;			// デバッグ用変数
	int m_StopTime = 0;
	bool m_isTelop = false;		// テロップを出したかどうか
	int m_isWait = 0;


public:
	StaffRoll(God * god);
	~StaffRoll();
	void Init();
	void Update();
	void Draw();
	void NextScene();

	// エンドロール画面を止める用
	void Stop(void);
	// エンドロール開始用、引数に開始位置を入れる
	void Scroll(float *posY);

	// デバッグ機構
	int ChangeNum(int *Num);
	void DebugPrint(float posX, float posY, float w, float h);
	void PosCustom(float *posX, float *posY);
	void SizeCustom(float *width, float *height);

	// リザルト用
	void SetRank(int mode);
	void CheckIcon(int *m_icon);
	void CheckMark(int *time, BOOL *use);
	void Slide(float *posX);
};

struct s_StaffRoll
{
	BOOL		g_Use;		// TRUE:使っている  FALSE:未使用
	XMFLOAT3	g_Pos;		// ポリゴンの座標
	float		g_w, g_h;	// 幅と高さ
	int			g_TexNo;	// テクスチャ番号
};

struct s_Check
{
	BOOL		g_Use;		// TRUE:使っている  FALSE:未使用
	XMFLOAT3	g_Pos;		// ポリゴンの座標
	float		g_w, g_h;	// 幅と高さ
	int			g_TexNo;	// テクスチャ番号
	int			checkTime;	// チェックマーク出現用
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitStaffRoll(void);
void UninitStaffRoll(void);


