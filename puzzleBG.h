//=============================================================================
//
// ÉpÉYÉãÇÃBGèàóù [puzzleBG.h]
// Author : åF‡Vã`çO
//
//=============================================================================
#pragma once
#include "main.h"


class PuzzleBG
{
private:
	bool m_Use;
	const int m_TexNo = 0;

public:
	const XMFLOAT2 m_Pos;
	const float m_w;
	const float m_h;
	
	PuzzleBG():m_Use(true)
		, m_Pos( L_SCREEN_WIDTH + R_SCREEN_WIDTH / 2.0f, R_SCREEN_HEIGHT / 2.0f + RU_SCREEN_HEIGHT)
		, m_w(R_SCREEN_WIDTH)
		, m_h(R_SCREEN_HEIGHT) {}

	bool GetUse(void) { return m_Use; }

	void SetUse(bool use) { m_Use = use; }


};


HRESULT InitPuzzleBG(void);
void UninitPuzzleBG(void);
void UpdatePuzzleBG(void);
void DrawPuzzleBG(void);
