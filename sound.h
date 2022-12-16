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

	SOUND_LABEL_SE_se_bom0,				// ���j
	SOUND_LABEL_SE_se_bom1,				// ���j
	SOUND_LABEL_SE_se_bom2,				// ���j
	SOUND_LABEL_SE_se_bom4,				// ���j

	SOUND_LABEL_SE_se_se_countDown,		// �J�E���g�_�E��
	SOUND_LABEL_SE_se_timer,			// �J�`�J�`��
	SOUND_LABEL_SE_se_timer_speedup,	// �J�`�J�`��

	SOUND_LABEL_SE_se_crow_25s,			// �J���X�̖���
	SOUND_LABEL_SE_se_crow_x1,			// �J���X�̖���
	SOUND_LABEL_SE_se_crow_x3,			// �J���X�̖���

	SOUND_LABEL_SE_se_mens_hihi,		// �j���̐�
	SOUND_LABEL_SE_se_mens_ou,			// �j���̐�
	SOUND_LABEL_SE_se_mens_yei,			// �j���̐�
	SOUND_LABEL_SE_se_women_ou,			// �j���̐�
	SOUND_LABEL_SE_se_women_kya,		// �����̐�


	SOUND_LABEL_SE_se_slot_stop,		// �X���b�g�̎~�߂鉹

	SOUND_LABEL_SE_se_chance,		// �X���b�g�̎~�߂鉹
	SOUND_LABEL_SE_se_pkieeen,		// �X���b�g�̎~�߂鉹
	SOUND_LABEL_SE_se_Roulette_high,		// �X���b�g�̎~�߂鉹

	SOUND_LABEL_SE_se_spotlight,		// �X�|�b�g���C�g
	SOUND_LABEL_SE_se_syakin,			// �V���L�[���I
	SOUND_LABEL_SE_se_zyan,				// �W�����I
	SOUND_LABEL_SE_se_shock,			// �K�[���I
	SOUND_LABEL_SE_se_doom,				// �h�[���I
	SOUND_LABEL_se_gong,				// �J���I�I


	SOUND_LABEL_SE_se_training_false,	// �؃g�����s
	SOUND_LABEL_SE_se_training_hart,	// �؃g���h�L�h�L
	SOUND_LABEL_SE_se_transition,		// �u�I��
	SOUND_LABEL_SE_se_wing_x1,			// �H�΂���1��
	SOUND_LABEL_SE_se_wing_x6,			// �H�΂���6��

	SOUND_LABEL_SE_se_title_bu,			// �J���u�U�[

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

