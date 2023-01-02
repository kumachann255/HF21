//=============================================================================
//
// �X�e�[�W�P�̏��� [Stage_01.cpp]
// Author : ������n
//
//=============================================================================
#include "Stage_01.h"
#include "SkyManager.h"
#include "rollerManager.h"
#include "input.h"
#include "QuestBoardManager.h"
#include "fade.h"
#include "camera.h"
#include "slot.h"
#include "FlyingCrowManager.h"
#include "debugproc.h"
#include "light.h"
#include "slotManager.h"
#include "room.h"
#include "trainingCrow.h"
#include "TrainingCrowManager.h"
#include "bonusSlotManager.h"
#include "renderer.h"
#include "texManager.h"
#include "UI.h"
#include "particle.h"
#include "calendar_num.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

static ParticlManager *pParticlManager = nullptr;


//=============================================================================
// �R���X�g���N�^�[ ���V�[���̃R���X�g���N�^�[�ɓn���Ă�����
//=============================================================================
Stage_01::Stage_01(God *god):Scene(god)
{
	pParticlManager = new ParticlManager();
}

//=============================================================================
// �f�X�g���N�^�[
//=============================================================================
Stage_01::~Stage_01()
{
	delete pParticlManager;
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
	// ���������������Ă��Ȃ��ꍇ�A�����o�ϐ��Ȃǂ��ꊇ������
	if (!m_isInit) InitDate();

	// �V�[���؂�ւ��`�F�b�N
	NextScene();


	// �J�����_�[�X�V
	GetGod()->GetCalendarNum()->Update();

	GetGod()->GetSkyManager()->Update();
	GetGod()->GetRollerManager()->Update();
	//GetGod()->GetSlot()->Update();
	//GetGod()->GetFlyingCrowManager()->Update();
	if (!GetGod()->GetTrainingCrowManager()->GetBonus())
	{
		GetGod()->GetQuestBoardManager()->Update();
	}
	GetGod()->GetSlotManager()->Update();
	GetGod()->GetTrainingCrowManager()->Update();
	GetGod()->GetBonusSlotManager()->Update();


	if (GetGod()->GetTrainingCrowManager()->GetBonus())
	{
		SetViewPort(TYPE_FULL_SCREEN);
	}

	// �e�N�X�`���̍X�V����
	{
		GetGod()->GetTexManager()->Update();
		//for (int i = 0; i < TELOP_TEXTURE_MAX; i++)
		//{
		//	GetGod()->GetTexManager()->GetUIManager()->GetUIObject(i)->Update();
		//}
	}

	pParticlManager->Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Stage_01::Draw(void)
{
	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	SetShader(SHADER_MODE_DEFAULT);
	
#ifdef _DEBUG
	// �f�o�b�O�\��
	PrintDebugProc("GetViewPortType():%d\n", GetViewPortType());
	PrintDebugProc("[enter]:�X���b�g�J�n\n");
	PrintDebugProc("[space]:�X���b�g��~\n");
	PrintDebugProc("[T]:�؃g�����j���[�ύX\n");
	PrintDebugProc("[S]:�؃g���X�s�[�h�A�b�v / ���Z�b�g\n");
	PrintDebugProc("[H]:➑̃��[�t�B���O�i�߂�\n");
	PrintDebugProc("[N]:➑̃��[�t�B���O���Z�b�g\n");

#endif

	switch (GetViewPortType())
	{
	case TYPE_FULL_SCREEN:
	//�t���X�N���[��=============================

		SetViewPort(TYPE_FULL_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		GetGod()->GetBonusSlotManager()->Draw();

		// �e�N�X�`���̕`�揈��
		{
			GetGod()->GetTexManager()->Draw();
		}


		break;

	case TYPE_LEFT_HALF_SCREEN:
	case TYPE_RIGHT_HALF_SCREEN:

	//�E�����=====================================

		SetViewPort(TYPE_DOWN_RIGHT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		XMFLOAT3 lightPos = { 100.0f, 0.0f, -100.0f };
		SetLightPos(0, lightPos);

		GetGod()->GetSkyManager()->Draw(SKYBG_MODE_Shining);
		GetGod()->GetSlotManager()->Draw(No_slot);


	//�����=====================================

		SetShader(SHADER_MODE_PHONG);

		SetViewPort(TYPE_LEFT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		XMFLOAT3 lightPos2 = { -500.0f, 50.0f, -100.0f };
		SetLightPos(0, lightPos2);


		GetGod()->GetSkyManager()->Draw();

		// �p�[�e�B�N��
		pParticlManager->Draw(0);

		SetShader(SHADER_MODE_DEFAULT);
		SetViewPort(TYPE_LEFT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		GetGod()->GetRollerManager()->Draw();
		GetGod()->GetSlotManager()->Draw(No_FlyingCrow);
		GetGod()->GetQuestBoardManager()->Draw();

		// �J�����_�[�`��
		GetGod()->GetCalendarNum()->Draw();



	//�E����===================================

		SetShader(SHADER_MODE_PHONG);

		SetViewPort(TYPE_RIGHT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		//GetGod()->GetSkyManager()->Draw(SKYBG_MODE_Utyuu);
		//GetGod()->GetRoom()->Draw();
		//GetGod()->GetTrainingCrowSquat()->Draw();
		GetGod()->GetTrainingCrowManager()->Draw();

		// �e�N�X�`���̕`�揈��
		{
			GetGod()->GetTexManager()->Draw();
		}

		break;

	case TYPE_UP_HALF_SCREEN:
	case TYPE_DOWN_HALF_SCREEN:
		SetViewPort(TYPE_UP_HALF_SCREEN);

		SetCameraAT(pos);
		SetCamera();
		SetViewPort(TYPE_DOWN_HALF_SCREEN);
		break;

	}


#ifdef _DEBUG	// �f�o�b�O����\������

	if (GetKeyboardTrigger(DIK_3))
	{
		this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
			telop_rainbowTime, texType_cutIn_up_Update, XMFLOAT3(350.0f, 350.0f, 0.0f), (int)MAX_RAINBOW_TIME);
		this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
			telop_rainbowTimeMakure, texType_cutIn_under_Update, XMFLOAT3(744.0f, 580.0f, 0.0f), (int)MAX_RAINBOW_TIME);
	}
	if (GetKeyboardTrigger(DIK_4))
	{
		GetGod()->GetTexManager()->GetUIManager()->SetTexture(0, texType_spring, XMFLOAT3(500.0f, 200.0f, 0.0f), 5);
	}
	if (GetKeyboardTrigger(DIK_5))
	{
		GetGod()->GetTexManager()->GetUIManager()->SetTexture(0, texType_cutIn_left, XMFLOAT3(500.0f, 200.0f, 0.0f), 5);
	}
	if (GetKeyboardTrigger(DIK_6))
	{
		GetGod()->GetTexManager()->GetUIManager()->SetTexture(telop_1, texType_cutIn_up, XMFLOAT3(500.0f, 200.0f, 0.0f), 5);
	}
	if (GetKeyboardTrigger(DIK_7))
	{
		GetGod()->GetTexManager()->GetUIManager()->SetTexture(0, texType_cutIn_under, XMFLOAT3(500.0f, 200.0f, 0.0f), 5);
	}
	if (GetKeyboardTrigger(DIK_8))
	{
		GetGod()->GetTexManager()->GetUIManager()->SetTexture(0, texType_zoomIn, XMFLOAT3(500.0f, 200.0f, 0.0f), 5);
	}
	if (GetKeyboardTrigger(DIK_9))
	{
		GetGod()->GetTexManager()->GetUIManager()->SetTexture(0, texType_zoomIn_rot, XMFLOAT3(500.0f, 200.0f, 0.0f), 5);
	}
#endif

}

//=============================================================================
// �V�[���J�ڏ���
//=============================================================================
void Stage_01::NextScene(void)
{
#ifdef _DEBUG	// �f�o�b�O����\������
	// �t�F�[�h�A�E�g���J�n������
	if (GetKeyboardTrigger(DIK_1))
	{
		SetFade(FADE_OUT, TITLE_ID);
	}
#endif

	// �t�F�[�h�A�E�g���I�������V�[����؂�ւ���
	if (GetFadeOut_EndFlag())
	{

		m_isInit = FALSE;
	}
}

void Stage_01::InitDate()
{
	m_isInit = TRUE;

	GetGod()->GetCalendarNum()->Init();
	GetGod()->GetRollerManager()->Init();
	GetGod()->GetQuestBoardManager()->Init();
	GetGod()->GetSlotManager()->Init();
	GetGod()->GetTrainingCrowManager()->Init();
	GetGod()->GetBonusSlotManager()->Init();

}



ParticlManager *GetParticlManager(void) 
{ 
	return pParticlManager; 
}
