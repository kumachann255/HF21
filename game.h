//=============================================================================
//
// �Q�[����ʏ��� [game.h]
// Author : 
//
//=============================================================================
#pragma once


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);

void DrawPizzle(void);
void SetShotCrows(XMFLOAT4 color);

XMFLOAT3 GetFlyingCrowPos(void);
