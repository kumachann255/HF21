//=============================================================================
//
// �X�e�[�W�P�̏��� [Stage_01.cpp]
// Author : ������n
//
//=============================================================================
#include "Stage_01.h"
#include "SkyManager.h"
#include "roller.h"
#include "input.h"
#include "QuestBoardManager.h"
#include "fade.h"
#include "camera.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//=============================================================================
// �R���X�g���N�^�[ ���V�[���̃R���X�g���N�^�[�ɓn���Ă�����
//=============================================================================
Stage_01::Stage_01(God *god):Scene(god)
{

}

//=============================================================================
// �f�X�g���N�^�[
//=============================================================================
Stage_01::~Stage_01()
{
}

//=============================================================================
// ����������
//=============================================================================
void Stage_01::Init(void)
{
	// �r���[�|�[�g�̐؂芷��
	SetViewPort(TYPE_LEFT_HALF_SCREEN);

}

//=============================================================================
// �X�V����
//=============================================================================
void Stage_01::Update(void)
{
	GetGod()->GetSkyManager()->Update();
	GetGod()->GetRoller()->Update();
	GetGod()->GetQuestBoardManager()->Update();

	// �V�[���؂�ւ��`�F�b�N
	NextScene();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Stage_01::Draw(void)
{
	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };


#ifdef _DEBUG
	// �f�o�b�O�\��
	PrintDebugProc("GetViewPortType():%d\n", GetViewPortType());

#endif

	switch (GetViewPortType())
	{
	case TYPE_FULL_SCREEN:
	//�t���X�N���[��=============================

		SetViewPort(TYPE_FULL_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		break;

	case TYPE_LEFT_HALF_SCREEN:
	case TYPE_RIGHT_HALF_SCREEN:

	//�����=====================================

		SetViewPort(TYPE_LEFT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		GetGod()->GetSkyManager()->Draw();
		GetGod()->GetRoller()->Draw();
		GetGod()->GetQuestBoardManager()->Draw();

	//�E����===================================

		SetViewPort(TYPE_RIGHT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		GetGod()->GetSkyManager()->Draw();


		break;

	case TYPE_UP_HALF_SCREEN:
	case TYPE_DOWN_HALF_SCREEN:
		SetViewPort(TYPE_UP_HALF_SCREEN);

		SetCameraAT(pos);
		SetCamera();
		SetViewPort(TYPE_DOWN_HALF_SCREEN);
		break;

	}

}

//=============================================================================
// �V�[���J�ڏ���
//=============================================================================
void Stage_01::NextScene(void)
{
	// �t�F�[�h�A�E�g���J�n������
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetFade(FADE_OUT);
	}

	// �t�F�[�h�A�E�g���I�������V�[����؂�ւ���
	if (GetFadeOut_EndFlag())
	{
		GetGod()->ChangeScene(TITLE_ID);

	}
}
