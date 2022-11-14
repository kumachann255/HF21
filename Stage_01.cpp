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
#include "debugproc.h"

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
	GetGod()->GetSkyManager()->Update();
	GetGod()->GetRoller()->Update();
	GetGod()->GetQuestBoardManager()->Update();

	// シーン切り替えチェック
	NextScene();
}

//=============================================================================
// 描画処理
//=============================================================================
void Stage_01::Draw(void)
{
	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };


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

		SetViewPort(TYPE_LEFT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		GetGod()->GetSkyManager()->Draw();
		GetGod()->GetRoller()->Draw();
		GetGod()->GetQuestBoardManager()->Draw();

	//右上画面===================================

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
// シーン遷移処理
//=============================================================================
void Stage_01::NextScene(void)
{
	// フェードアウトを開始させる
	if (GetKeyboardTrigger(DIK_RETURN))
	{
		SetFade(FADE_OUT);
	}

	// フェードアウトが終わったらシーンを切り替える
	if (GetFadeOut_EndFlag())
	{
		GetGod()->ChangeScene(TITLE_ID);

	}
}
