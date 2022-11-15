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
#include "slot.h"
#include "FlyingCrowManager.h"
#include "debugproc.h"
#include "light.h"

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
	// �V�[���؂�ւ��`�F�b�N
	NextScene();

	GetGod()->GetSkyManager()->Update();
	GetGod()->GetRoller()->Update();
	GetGod()->GetQuestBoardManager()->Update();
	GetGod()->GetSlot()->Update();
	GetGod()->GetFlyingCrowManager()->Update();


	XMFLOAT4 color = { 0.2f,0.2f,0.2f,1.0f };

	// �J���[�X����
	if (GetKeyboardTrigger(DIK_5))
	{
		GetGod()->GetFlyingCrowManager()->SetShotCrows(color);
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void Stage_01::Draw(void)
{
	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	SetShader(SHADER_MODE_PHONG);
	
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

		SetViewPort(TYPE_DOWN_RIGHT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		XMFLOAT3 lightPos = { 100.0f, 0.0f, -100.0f };
		SetLightPos(0, lightPos);

		GetGod()->GetSkyManager()->Draw(SKYBG_MODE_Shining);
		GetGod()->GetSlot()->Draw();

	//�����=====================================

		SetViewPort(TYPE_LEFT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		XMFLOAT3 lightPos2 = { -500.0f, 50.0f, -100.0f };
		SetLightPos(0, lightPos2);

		GetGod()->GetSkyManager()->Draw(SKYBG_MODE_Aozora);
		GetGod()->GetRoller()->Draw();
		GetGod()->GetQuestBoardManager()->Draw();
		GetGod()->GetFlyingCrowManager()->Draw();

	//�E����===================================

		SetViewPort(TYPE_RIGHT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		GetGod()->GetSkyManager()->Draw(SKYBG_MODE_Utyuu);


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
	if (GetKeyboardTrigger(DIK_1))
	{
		SetFade(FADE_OUT);
	}

	// �t�F�[�h�A�E�g���I�������V�[����؂�ւ���
	if (GetFadeOut_EndFlag())
	{
		GetGod()->ChangeScene(TITLE_ID);

	}
}
