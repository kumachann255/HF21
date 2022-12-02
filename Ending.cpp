#include "Ending.h"
#include "input.h"
#include "fade.h"
#include "camera.h"
#include "debugproc.h"
#include "SkyManager.h"
#include "AnimationManager.h"

Ending::Ending(God * god) :Scene(god)
{

}

Ending::~Ending()
{
}

void Ending::Init()
{
	// �r���[�|�[�g�̐؂芷��
	SetViewPort(TYPE_UP_HALF_SCREEN);

}

void Ending::Update()
{
	// �V�[���؂�ւ��`�F�b�N
	NextScene();

	GetGod()->GetAnimationManager()->Update();
}

void Ending::Draw()
{
	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	SetShader(SHADER_MODE_PHONG);

	switch (GetViewPortType())
	{
	case TYPE_FULL_SCREEN:
		//�t���X�N���[��=============================

		break;

	case TYPE_LEFT_HALF_SCREEN:
	case TYPE_RIGHT_HALF_SCREEN:

		//�E�����=====================================

		//�����=====================================

		//�E����===================================

		break;

	case TYPE_UP_HALF_SCREEN:
		//����=====================================
		SetViewPort(TYPE_FULL_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		GetGod()->GetSkyManager()->Draw(SKYBG_MODE_Shining);
		GetGod()->GetAnimationManager()->Draw();


	case TYPE_DOWN_HALF_SCREEN:
		//�����=====================================
		SetViewPort(TYPE_DOWN_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();



		break;

	}

}

void Ending::NextScene()
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
