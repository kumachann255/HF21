//=============================================================================
//
// タイトル画面処理 [Title.h]
// Author : 
//
//=============================================================================
#pragma once
#include "Scene.h"
#include "UI.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEX_MAX					(3)				// テクスチャの数

enum
{
	FIRST_CLOSE   = 0,
	OPEN_CURTAIN  = 1,
	CHOICE		  = 2,
	GAME_START    = 3,
	CLOSE_CURTAIN = 4,
	EXIT_CLOSE    = 5
};

class TitleUI
{
private:
	UIObject *m_UIObject[TEX_MAX];

public:
	//TitleUI();
	//~TitleUI();

	UIObject *GetUIObject(void){ return m_UIObject[0]; }
};



class Title : public Scene
{
private:
	bool m_DebugSwich = true;	// デバッグモード切り替え用SW
	int m_DebugNum = 0;			// デバッグ用変数
	int m_modeSw = FIRST_CLOSE;	// titleMode切り替え用
	TitleUI *m_TitleUI;

public:
	Title(God * god);
	~Title();
	void Init();
	void Update();
	void Draw();
	void NextScene();


	// アニメーション切り替え関数
	int SetMode(int mode);
	// 始まりの状態を表す関数
	void FirstClose(void);
	// カーテンを開く関数
	/* 第一引数右カーテン、第二引数左カーテン */
	void OpenCurtain(float *curtainR, float *curtainL);
	// シーン遷移先を選ぶ関数
	/* 第一引数ExitPosX、第二引数ExitPosY、第三引数GamePosX、第四引数GamePosY、第五引数ChoicePosX、第六引数ChoicePosY */
	void Choice(float *posExitX, float *posGameX, float *posChoiceX);
	void CloseCurtain(float *curtainR, float *curtainL);

	// デバッグ機構
	int ChangeNum(int *Num);
	void DebugPrint(float posX, float posY);
	void PosCustom(float *posX, float *posY);

};

struct s_Title
{
	BOOL		g_Use;		// TRUE:使っている  FALSE:未使用
	XMFLOAT3	g_Pos;		// ポリゴンの座標
	float		g_w, g_h;	// 幅と高さ
	int			g_TexNo;	// テクスチャ番号
	float		alpha;
	BOOL		flag_alpha;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

