//=============================================================================
//
// ステージ１の処理 [Stage_01.cpp]
// Author : 柏村大地
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
// マクロ定義
//*****************************************************************************


//=============================================================================
// コンストラクター ※シーンのコンストラクターに渡してあげる
//=============================================================================
Stage_01::Stage_01(God *god):Scene(god)
{

}

//=============================================================================
// デストラクター
//=============================================================================
Stage_01::~Stage_01()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
void Stage_01::Init(void)
{
	// ビューポートの切り換え
	SetViewPort(TYPE_LEFT_HALF_SCREEN);

}

//=============================================================================
// 更新処理
//=============================================================================
void Stage_01::Update(void)
{
	// シーン切り替えチェック
	NextScene();

	GetGod()->GetSkyManager()->Update();
	GetGod()->GetRoller()->Update();
	GetGod()->GetQuestBoardManager()->Update();
	GetGod()->GetSlot()->Update();
	GetGod()->GetFlyingCrowManager()->Update();


	XMFLOAT4 color = { 0.2f,0.2f,0.2f,1.0f };

	// カラース発生
	if (GetKeyboardTrigger(DIK_5))
	{
		GetGod()->GetFlyingCrowManager()->SetShotCrows(color);
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void Stage_01::Draw(void)
{
	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	SetShader(SHADER_MODE_PHONG);
	
#ifdef _DEBUG
	// デバッグ表示
	PrintDebugProc("GetViewPortType():%d\n", GetViewPortType());
#endif

	switch (GetViewPortType())
	{
	case TYPE_FULL_SCREEN:
	//フルスクリーン=============================

		SetViewPort(TYPE_FULL_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		break;

	case TYPE_LEFT_HALF_SCREEN:
	case TYPE_RIGHT_HALF_SCREEN:

	//左画面=====================================

		SetViewPort(TYPE_DOWN_RIGHT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		XMFLOAT3 lightPos = { 100.0f, 0.0f, -100.0f };
		SetLightPos(0, lightPos);

		GetGod()->GetSkyManager()->Draw(SKYBG_MODE_Shining);
		GetGod()->GetSlot()->Draw();

	//左画面=====================================

		SetViewPort(TYPE_LEFT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		XMFLOAT3 lightPos2 = { -500.0f, 50.0f, -100.0f };
		SetLightPos(0, lightPos2);

		GetGod()->GetSkyManager()->Draw(SKYBG_MODE_Aozora);
		GetGod()->GetRoller()->Draw();
		GetGod()->GetQuestBoardManager()->Draw();
		GetGod()->GetFlyingCrowManager()->Draw();

	//右上画面===================================

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
// シーン遷移処理
//=============================================================================
void Stage_01::NextScene(void)
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
