//=============================================================================
//
// ゲーム画面処理 [game.h]
// Author : 
//
//=============================================================================
#pragma once


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

void DrawPizzle(void);
void SetShotCrows(XMFLOAT4 color);

XMFLOAT3 GetFlyingCrowPos(void);
