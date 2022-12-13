//=============================================================================
//
// �T�E���h���� [sound.h]
//
//=============================================================================
#pragma once

#include <windows.h>
#include "xaudio2.h"						// �T�E���h�����ŕK�v

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
enum 
{
	SOUND_LABEL_BGM_sample000,	// BGM0
	SOUND_LABEL_BGM_sample001,	// BGM1
	SOUND_LABEL_BGM_sample002,	// BGM2
	SOUND_LABEL_SE_bomb000,		// ������
	SOUND_LABEL_SE_defend000,	// 
	SOUND_LABEL_SE_defend001,	// 
	SOUND_LABEL_SE_hit000,		// 
	SOUND_LABEL_SE_laser000,	// 
	SOUND_LABEL_SE_lockon000,	// 
	SOUND_LABEL_SE_shot000,		// 
	SOUND_LABEL_SE_shot001,		// 

	SOUND_LABEL_SE_se_slot_button_01,	// �X���b�g���~�߂�
	SOUND_LABEL_SE_se_slot_lever_01,	// �X���b�g�𓮂���
	SOUND_LABEL_SE_se_crow_cry_01,		// �J���[�X�̖���
	SOUND_LABEL_SE_se_crow_flap_04,		// �J���[�X����
	SOUND_LABEL_SE_se_quest_appear,		// �N�G�X�g�o��
	SOUND_LABEL_SE_se_quest_clear,		// �N�G�X�g�B��
	SOUND_LABEL_SE_se_map_change,		// �}�b�v�ω�

	SOUND_LABEL_MAX,
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
BOOL InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(int label);
void StopSound(int label);
void StopSound(void);

