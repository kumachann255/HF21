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
#define CROWS_MAX (100)

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

#endif


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame0(void)
{

}

void DrawGame(void)
{


	GameGod->Draw();






//	XMFLOAT3 pos = {0.0f,0.0f,0.0f};
//
//
//
//	// プレイヤー視点
//	//pos = GetPlayer()->pos;
//	pos.y = 0.0f;			// カメラ酔いを防ぐためにクリアしている
//	SetCameraAT(pos);
//	SetCamera();
//
//	SetShader(SHADER_MODE_PHONG);
//	//SetShader(SHADER_MODE_DEFAULT);
//
//	switch (g_ViewPortType_Game)
//	{
//	case TYPE_FULL_SCREEN:
//		SetViewPort(TYPE_FULL_SCREEN);
//		DrawGame0();
//		break;
//
//	case TYPE_LEFT_HALF_SCREEN:
//	case TYPE_RIGHT_HALF_SCREEN:
//		SetViewPort(TYPE_LEFT_HALF_SCREEN);
//		SetCameraAT(pos);
//		SetCamera();
//
//		DrawGame0();
//
//		pos.y = 0.0f;
//		//SetCameraAT(pos);
//		//SetCamera();
//		SetViewPort(TYPE_RIGHT_HALF_SCREEN);
//
//		SetCameraAT(pos);
//		SetCamera();
//
//		//SetShader(SHADER_MODE_DEFAULT);
//		DrawGame0();
//		break;
//
//	case TYPE_UP_HALF_SCREEN:
//	case TYPE_DOWN_HALF_SCREEN:
//		SetViewPort(TYPE_UP_HALF_SCREEN);
//		DrawGame0();
//
//		// エネミー視点
//		//pos = GetEnemy()->pos;
//		pos.y = 0.0f;
//		SetCameraAT(pos);
//		SetCamera();
//		SetViewPort(TYPE_DOWN_HALF_SCREEN);
//		DrawGame0();
//		break;
//
//	}
}


void SetShotCrows(XMFLOAT4 color)
{
	//int a = rand() % (CROWS_MAX - 2) + 2;

	//for (int i = 0; i < a; i++)
	//{
	//	XMFLOAT3 targetPos = { -50.0f, 20.0f, -100.0f };
	//	// 飛んでいくカラスの初期化
	//	pFlyingCrow[i] = new FlyingCrow(color, targetPos);

	//	// 飛んでいくカラスの大きさセット
	//	pFlyingCrow[i]->SetPrefab(pPrefabFlyingCrow[0]);
	//	XMFLOAT3 scl3 = { 0.3f,0.3f,0.3f };
	//	pFlyingCrow[i]->SetScl(scl3);
	//	pPrefabFlyingCrow[0]->SetColor(color);
	//}
}
