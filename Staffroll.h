//=============================================================================
//
// �X�^�b�t���[����ʏ��� [Staffroll.h]
// Author : 
//
//=============================================================================
#pragma once
#include "Scene.h"
#include "UI.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_STOPTIME		(100)
#define STAFFROLL_MAX		(13)				// �e�N�X�`���̐�
#define CHECK_MAX			(5)

enum StaffRoll_enum
{
	RESULT	= 0,
	GOLD	= 1,
	SILVER	= 2,
	BRONSE	= 3,
	BLUE	= 4,
	GREEN	= 5,
	ENDROLL = 6
};

class StaffRoll : public Scene
{
private:
	int m_Mode = RESULT;
	bool m_ScrollSw = false;	// �X�N���[���J�n�pSW
	bool m_DebugSwich = true;	// �f�o�b�O���[�h�؂�ւ��pSW
	int m_DebugNum = 0;			// �f�o�b�O�p�ϐ�
	int m_StopTime = 0;
	bool m_isTelop = false;		// �e���b�v���o�������ǂ���
	int m_isWait = 0;


public:
	StaffRoll(God * god);
	~StaffRoll();
	void Init();
	void Update();
	void Draw();
	void NextScene();

	// �G���h���[����ʂ��~�߂�p
	void Stop(void);
	// �G���h���[���J�n�p�A�����ɊJ�n�ʒu������
	void Scroll(float *posY);

	// �f�o�b�O�@�\
	int ChangeNum(int *Num);
	void DebugPrint(float posX, float posY, float w, float h);
	void PosCustom(float *posX, float *posY);
	void SizeCustom(float *width, float *height);

	// ���U���g�p
	void SetRank(int mode);
	void CheckIcon(int *m_icon);
	void CheckMark(int *time, BOOL *use);
	void Slide(float *posX);
};

struct s_StaffRoll
{
	BOOL		g_Use;		// TRUE:�g���Ă���  FALSE:���g�p
	XMFLOAT3	g_Pos;		// �|���S���̍��W
	float		g_w, g_h;	// ���ƍ���
	int			g_TexNo;	// �e�N�X�`���ԍ�
};

struct s_Check
{
	BOOL		g_Use;		// TRUE:�g���Ă���  FALSE:���g�p
	XMFLOAT3	g_Pos;		// �|���S���̍��W
	float		g_w, g_h;	// ���ƍ���
	int			g_TexNo;	// �e�N�X�`���ԍ�
	int			checkTime;	// �`�F�b�N�}�[�N�o���p
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitStaffRoll(void);
void UninitStaffRoll(void);


