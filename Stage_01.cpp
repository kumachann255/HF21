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
#include "slotManager.h"
#include "room.h"
#include "trainingCrow.h"
#include "TrainingCrowManager.h"
#include "bonusSlotManager.h"
#include "FLUID3D_GPU.h"
#include "renderer.h"
#include "texManager.h"
#include "UI.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

FLUID3D_GPU* m_pSolverGPU;


//=============================================================================
// �R���X�g���N�^�[ ���V�[���̃R���X�g���N�^�[�ɓn���Ă�����
//=============================================================================
Stage_01::Stage_01(God *god):Scene(god)
{
	////�\���o�[����
	m_pSolverGPU = new FLUID3D_GPU;

	m_pSolverGPU->Init(GetDevice(), GetDeviceContext(), SCREEN_WIDTH, SCREEN_HEIGHT
		, GetRenderTargetView(), GetDepthStencilView());

	XMFLOAT3 pos = { -50.0f,-10.0f,0.0f };
	XMFLOAT3 scl = { 100.0f,50.0f,100.0f };

	m_pSolverGPU->SetPos(pos);
	m_pSolverGPU->SetScl(scl);
}

//=============================================================================
// �f�X�g���N�^�[
//=============================================================================
Stage_01::~Stage_01()
{
	delete m_pSolverGPU;
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

	//���̌v�Z
	{
		m_pSolverGPU->AddDensitySource(XMFLOAT4(2, 99, 2, 5.0f), XMFLOAT4(0.10f, 0.10f, 0.10f, 0.0f));
		m_pSolverGPU->AddVelocitySource(XMFLOAT4(2, 99, 2, 5.0f), XMFLOAT4(3.0f, -3.0f, 3.0f, 0.0f));
		m_pSolverGPU->Solve();
	}

	GetGod()->GetSkyManager()->Update();
	GetGod()->GetRoller()->Update();
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
		m_pSolverGPU->SetUse(TRUE);
	}
	else
	{
		m_pSolverGPU->SetUse(FALSE);
	}


	// �e�N�X�`���̍X�V����
	{
		for (int i = 0; i < TELOP_TEXTURE_MAX; i++)
		{
			GetGod()->GetTexManager()->GetUIManager()->GetUIObject(i)->Update();
		}
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
			for (int i = 0; i < TELOP_TEXTURE_MAX; i++)
			{
				GetGod()->GetTexManager()->GetUIManager()->GetUIObject(i)->Draw();
			}
		}

		m_pSolverGPU->DrawFluid();

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

		SetViewPort(TYPE_LEFT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		XMFLOAT3 lightPos2 = { -500.0f, 50.0f, -100.0f };
		SetLightPos(0, lightPos2);

		GetGod()->GetSkyManager()->Draw(SKYBG_MODE_Aozora);
		GetGod()->GetRoller()->Draw();
		GetGod()->GetQuestBoardManager()->Draw();
		GetGod()->GetSlotManager()->Draw(No_FlyingCrow);

	//�E����===================================

		SetViewPort(TYPE_RIGHT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		//GetGod()->GetSkyManager()->Draw(SKYBG_MODE_Utyuu);
		//GetGod()->GetRoom()->Draw();
		//GetGod()->GetTrainingCrowSquat()->Draw();
		GetGod()->GetTrainingCrowManager()->Draw();

		// �e�N�X�`���̕`�揈��
		{
			for (int i = 0; i < TELOP_TEXTURE_MAX; i++)
			{
				GetGod()->GetTexManager()->GetUIManager()->GetUIObject(i)->Draw();
			}
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
		GetGod()->GetTexManager()->GetUIManager()->SetTexture(0, texType_fade, XMFLOAT3(500.0f, 200.0f, 0.0f), 5);
	}
	if (GetKeyboardTrigger(DIK_4))
	{
		GetGod()->GetTexManager()->GetUIManager()->SetTexture(0, texType_cutIn_right, XMFLOAT3(500.0f, 200.0f, 0.0f), 5);
	}
	if (GetKeyboardTrigger(DIK_5))
	{
		GetGod()->GetTexManager()->GetUIManager()->SetTexture(0, texType_cutIn_left, XMFLOAT3(500.0f, 200.0f, 0.0f), 5);
	}
	if (GetKeyboardTrigger(DIK_6))
	{
		GetGod()->GetTexManager()->GetUIManager()->SetTexture(0, texType_cutIn_up, XMFLOAT3(500.0f, 200.0f, 0.0f), 5);
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
		SetFade(FADE_OUT);
	}
#endif

	// �t�F�[�h�A�E�g���I�������V�[����؂�ւ���
	if (GetFadeOut_EndFlag())
	{
		GetGod()->ChangeScene(ENDROLL_ID);

	}
}
