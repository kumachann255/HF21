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

	SOUND_LABEL_SE_se_bom0,				// 爆破
	SOUND_LABEL_SE_se_bom1,				// 爆破
	SOUND_LABEL_SE_se_bom2,				// 爆破
	SOUND_LABEL_SE_se_bom4,				// 爆破

	SOUND_LABEL_SE_se_se_countDown,		// カウントダウン
	SOUND_LABEL_SE_se_timer,			// カチカチ音
	SOUND_LABEL_SE_se_timer_speedup,	// カチカチ音

	SOUND_LABEL_SE_se_crow_25s,			// カラスの鳴き声
	SOUND_LABEL_SE_se_crow_x1,			// カラスの鳴き声
	SOUND_LABEL_SE_se_crow_x3,			// カラスの鳴き声

	SOUND_LABEL_SE_se_mens_hihi,		// 男性の声
	SOUND_LABEL_SE_se_mens_ou,			// 男性の声
	SOUND_LABEL_SE_se_mens_yei,			// 男性の声
	SOUND_LABEL_SE_se_women_ou,			// 男性の声
	SOUND_LABEL_SE_se_women_kya,		// 女性の声


	SOUND_LABEL_SE_se_slot_stop,		// スロットの止める音

	SOUND_LABEL_SE_se_chance,		// スロットの止める音
	SOUND_LABEL_SE_se_pkieeen,		// スロットの止める音
	SOUND_LABEL_SE_se_Roulette_high,		// スロットの止める音

	SOUND_LABEL_SE_se_spotlight,		// スポットライト
	SOUND_LABEL_SE_se_syakin,			// シャキーン！
	SOUND_LABEL_SE_se_zyan,				// ジャン！
	SOUND_LABEL_SE_se_shock,			// ガーン！
	SOUND_LABEL_SE_se_doom,				// ドーン！
	SOUND_LABEL_se_gong,				// カン！！


	SOUND_LABEL_SE_se_training_false,	// 筋トレ失敗
	SOUND_LABEL_SE_se_training_hart,	// 筋トレドキドキ
	SOUND_LABEL_SE_se_transition,		// ブオン
	SOUND_LABEL_SE_se_wing_x1,			// 羽ばたき1回
	SOUND_LABEL_SE_se_wing_x6,			// 羽ばたき6回

	SOUND_LABEL_SE_se_title_bu,			// 開幕ブザー

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

