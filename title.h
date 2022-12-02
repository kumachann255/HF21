//=============================================================================
//
// �^�C�g����ʏ��� [Title.h]
// Author : 
//
//=============================================================================
#pragma once
#include "Scene.h"
#include "UI.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEX_MAX					(3)				// �e�N�X�`���̐�

enum
{
	FIRST_CLOSE   = 0,
	OPEN_CURTAIN  = 1,
	CHOICE		  = 2,
	GAME_START    = 3,
	CLOSE_CURTAIN = 4,
	EXIT_CLOSE    = 5
};

class TitleUI
{
private:
	UIObject *m_UIObject[TEX_MAX];

public:
	//TitleUI();
	//~TitleUI();

	UIObject *GetUIObject(void){ return m_UIObject[0]; }
};



class Title : public Scene
{
private:
	bool m_DebugSwich = true;	// �f�o�b�O���[�h�؂�ւ��pSW
	int m_DebugNum = 0;			// �f�o�b�O�p�ϐ�
	int m_modeSw = FIRST_CLOSE;	// titleMode�؂�ւ��p
	TitleUI *m_TitleUI;

public:
	Title(God * god);
	~Title();
	void Init();
	void Update();
	void Draw();
	void NextScene();


	// �A�j���[�V�����؂�ւ��֐�
	int SetMode(int mode);
	// �n�܂�̏�Ԃ�\���֐�
	void FirstClose(void);
	// �J�[�e�����J���֐�
	/* �������E�J�[�e���A���������J�[�e�� */
	void OpenCurtain(float *curtainR, float *curtainL);
	// �V�[���J�ڐ��I�Ԋ֐�
	/* ������ExitPosX�A������ExitPosY�A��O����GamePosX�A��l����GamePosY�A��܈���ChoicePosX�A��Z����ChoicePosY */
	void Choice(float *posExitX, float *posGameX, float *posChoiceX);
	void CloseCurtain(float *curtainR, float *curtainL);

	// �f�o�b�O�@�\
	int ChangeNum(int *Num);
	void DebugPrint(float posX, float posY);
	void PosCustom(float *posX, float *posY);

};

struct s_Title
{
	BOOL		g_Use;		// TRUE:�g���Ă���  FALSE:���g�p
	XMFLOAT3	g_Pos;		// �|���S���̍��W
	float		g_w, g_h;	// ���ƍ���
	int			g_TexNo;	// �e�N�X�`���ԍ�
	float		alpha;
	BOOL		flag_alpha;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

