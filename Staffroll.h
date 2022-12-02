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


class StaffRoll : public Scene
{
private:
	bool m_DebugSwich = true;	// �f�o�b�O���[�h�؂�ւ��pSW
	int m_DebugNum = 0;			// �f�o�b�O�p�ϐ�

public:
	StaffRoll(God * god);
	~StaffRoll();
	void Init();
	void Update();
	void Draw();
	void NextScene();


	void Scroll(float *posY);

	// �f�o�b�O�@�\
	//int ChangeNum(int *Num);
	void DebugPrint(float posY);
	void PosCustom(float *posY);

};

struct s_StaffRoll
{
	BOOL		g_Use;		// TRUE:�g���Ă���  FALSE:���g�p
	XMFLOAT3	g_Pos;		// �|���S���̍��W
	float		g_w, g_h;	// ���ƍ���
	int			g_TexNo;	// �e�N�X�`���ԍ�
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitStaffRoll(void);
void UninitStaffRoll(void);
void UpdateStaffRoll(void);
void DrawStaffRoll(void);


