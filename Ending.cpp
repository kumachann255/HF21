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
	// ビューポートの切り換え
	SetViewPort(TYPE_UP_HALF_SCREEN);

}

void Ending::Update()
{
	// シーン切り替えチェック
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
		//フルスクリーン=============================

		break;

	case TYPE_LEFT_HALF_SCREEN:
	case TYPE_RIGHT_HALF_SCREEN:

		//右下画面=====================================

		//左画面=====================================

		//右上画面===================================

		break;

	case TYPE_UP_HALF_SCREEN:
		//上画面=====================================
		SetViewPort(TYPE_FULL_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		GetGod()->GetSkyManager()->Draw(SKYBG_MODE_Shining);
		GetGod()->GetAnimationManager()->Draw();


	case TYPE_DOWN_HALF_SCREEN:
		//下画面=====================================
		SetViewPort(TYPE_DOWN_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();



		break;

	}

}

void Ending::NextScene()
{
	// フェードアウトを開始させる
	if (GetKeyboardTrigger(DIK_1))
	{
		SetFade(FADE_OUT);
	}

	// フェードアウトが終わったらシーンを切り替える
	if (GetFadeOut_EndFlag())
	{
		GetGod()->ChangeScene(TITLE_ID);

	}
}
