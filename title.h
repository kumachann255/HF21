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
#define TITLE_MAX					(23)				// �e�N�X�`���̐�

enum
{
	CHOICE = 0,
	GAME_START = 1,
	EXIT = 2,
};


// ���ꂪ�^�C�g���}�l�[�W���̖����B�֐��Ŗ��߂��o���B�֐��̈������_��Ƀ|�C���^�Ő؂�ւ�
class Title : public Scene
{
private:
	bool m_DebugSwich = true;	// �f�o�b�O���[�h�؂�ւ��pSW
	int m_DebugNum = 0;			// �f�o�b�O�p�ϐ�
	int m_modeSw = CHOICE;		// titleMode�؂�ւ��p

public:
	Title(God * god);
	~Title();
	void Init();
	void Update();
	void Draw();
	void NextScene();

	/* �w�i���i�Q����֐� */


	// ���[�h�؂�ւ��֐�
	/* �񋓎q���Z�b�g */
	int SetMode(int mode);

	// �摜��\���p�֐�
	/* ������BOOL�^ */
	void SetBOOL(BOOL *use);

	// �V�[���J�ڐ��I�Ԋ֐�
	/* ������ExitPosX�A������GameStartPosX�A��O����ChoicePosX */
	void Choice(float *posExitx, float *posGameX, float *posChoiceX);

	// �������̃A�h���X�̉�]�p�ɔC�ӂ̉�]�ʂ��Z�b�g����֐�
	/* ��������]�ΏۃA�h���X�A��������]�� */
	void Rot(float *RotZ, float valueRot);

	// �������̃A�h���X�̉�]�p�ɔC�ӂ̉�]�ʂ��Z�b�g���A���X�ɉ���������֐�
	/* ��������]�ΏۃA�h���X�A��������]�� */
	void RotAccel(float *RotZ, float valueRot);

	// �I�u�W�F�N�g�㉺�֐�
	/* �������Ώ�bool�A�������ΏۃA�h���XYPos�A��O�����ړ��� */
	void UpDown(bool *udFlug, float *posY, float addY);

	// �I�u�W�F�N�g�g�����W�V�����֐�
	/* �������ΏۃA�h���XXPos�A�������ړ��ʁA��O�������Ԍ��Z�p�ϐ� */
	void Transition(float *posX, float moveValue, float timeSub);

	// �C�ӂ̕��p�ֈ��̎��Ԃ𖞂��������]���Ȃ���ˏo����֐�
	// �������̃A�h���X�̉�]�p�ɔC�ӂ̉�]�ʂ��Z�b�g����֐�
	void RotRocket(float *posX, float *posY, float addX, float addY, float *RotZ, float valueRot, int time);

	// �o�C�u���[�V�����֐��i�����̒l���������قǍ����Ƀo�C�u���[�V�����j
	/* �������o�C�u���[�V�����p�x�̐����A��������]�Ώۂ̃A�h���X */
	void Swaying(int i, float *RotZ);



	/* �f�o�b�O�@�\ */



	// �f�o�b�O�Ώې؂�ւ�
	int ChangeNum(int *Num);

	// �f�o�b�O���e�\��
	void DebugPrint(float posX, float posY, float w, float h);

	// �Ώۈʒu�̕ύX
	void PosCustom(float *posX, float *posY);

	// �ΏۃT�C�Y�̕ύX
	void SizeCustom(float *width, float *height);
};

// �����炪����Ώۂ̕��i�ɓ�����
struct s_Title
{
	bool		g_UD_Change;// UpDown�p�֐��X�C�b�`
	BOOL		g_Use;		// TRUE:�g���Ă���  FALSE:���g�p
	XMFLOAT3	g_Pos;		// �|���S���̍��W
	XMFLOAT3	g_Rot;		// �|���S���̉�]
	float		g_w, g_h;	// ���ƍ���
	int			g_TexNo;	// �e�N�X�`���ԍ�
};

// �����炪����Ώۂ̕��i�ɓ�����
struct s_OpenEgg
{
	BOOL		g_Use;		// TRUE:�g���Ă���  FALSE:���g�p
	XMFLOAT3	g_Pos;		// �|���S���̍��W
	XMFLOAT3	g_Rot;		// �|���S���̉�]
	float		g_w, g_h;	// ���ƍ���
	int			g_TexNo;	// �e�N�X�`���ԍ�
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

