//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#pragma once

#include <windows.h>
#include "xaudio2.h"						// サウンド処理で必要

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
enum 
{
	SOUND_LABEL_BGM_sample000,	// BGM0
	SOUND_LABEL_BGM_sample001,	// BGM1
	SOUND_LABEL_BGM_sample002,	// BGM2
	SOUND_LABEL_SE_bomb000,		// 爆発音
	SOUND_LABEL_SE_defend000,	// 
	SOUND_LABEL_SE_defend001,	// 
	SOUND_LABEL_SE_hit000,		// 
	SOUND_LABEL_SE_laser000,	// 
	SOUND_LABEL_SE_lockon000,	// 
	SOUND_LABEL_SE_shot000,		// 
	SOUND_LABEL_SE_shot001,		// 

	SOUND_LABEL_SE_se_slot_button_01,	// スロットを止める
	SOUND_LABEL_SE_se_slot_lever_01,	// スロットを動かす
	SOUND_LABEL_SE_se_crow_cry_01,		// カラースの鳴き声
	SOUND_LABEL_SE_se_crow_flap_04,		// カラース発射
	SOUND_LABEL_SE_se_quest_appear,		// クエスト出現
	SOUND_LABEL_SE_se_quest_clear,		// クエスト達成
	SOUND_LABEL_SE_se_map_change,		// マップ変化

	SOUND_LABEL_MAX,
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
BOOL InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(int label);
void StopSound(int label);
void StopSound(void);

