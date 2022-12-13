//=============================================================================
//
// ゲーム画面処理 [game.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "model.h"
#include "camera.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "game.h"
#include "collision.h"
#include "debugproc.h"

#include "God.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int	g_ViewPortType_Game = TYPE_LEFT_HALF_SCREEN;

static BOOL	g_bPause = TRUE;	// ポーズON/OFF

// 神
God *GameGod;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{
	g_ViewPortType_Game = TYPE_LEFT_HALF_SCREEN;
	SetViewPort(g_ViewPortType_Game);

	GameGod = new God;

	// BGM再生
	//PlaySound(SOUND_LABEL_BGM_sample001);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	delete GameGod;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_V))
	{
		g_ViewPortType_Game = (g_ViewPortType_Game + 1) % TYPE_NONE;
		SetViewPort(g_ViewPortType_Game);
	}

	if (GetKeyboardTrigger(DIK_P))
	{
		g_bPause = g_bPause ? FALSE : TRUE;
	}

#endif

	if(g_bPause == FALSE)
		return;

	// 更新
	GameGod->Update();

#ifdef _DEBUG
	// デバッグ表示
	PrintDebugProc("ViewPortType:%d\n", g_ViewPortType_Game);
	if (GetKeyboardTrigger(DIK_M))
	{
		PlaySound(SOUND_LABEL_SE_se_map_change); // マップ変化
	}

#endif


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame(void)
{
	GameGod->Draw();
}