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
#include "slotManager.h"
#include "room.h"
#include "trainingCrow.h"
#include "TrainingCrowManager.h"
#include "bonusSlotManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
static char *g_TexturName[STAGE_01_TEX_MAX] = {
	"data/TEXTURE/bg000.jpg",
	"data/TEXTURE/title_logo.png",
	"data/TEXTURE/effect000.jpg",
};



//=============================================================================
// コンストラクター ※シーンのコンストラクターに渡してあげる
//=============================================================================
Stage_01::Stage_01(God *god):Scene(god)
{
	XMFLOAT3 pos0 = { 0.0f,0.0f,0.0f };
	float w0 = 200.0f;
	float h0 = 100.0f;
	int time0 = 2;


	m_UIManager.Register(new UIObject(pos0, w0, h0, time0));

	m_UIManager.GetUIObject(0)->GetUITexData()->Create(g_TexturName[0]);
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


	// テクスチャの更新処理
	{
		m_UIManager.GetUIObject(0)->Update();
	}


	XMFLOAT4 color = { 0.2f,0.2f,0.2f,1.0f };

	// カラース発生
	//if (GetKeyboardTrigger(DIK_5))
	//{
	//	GetGod()->GetFlyingCrowManager()->SetShotCrows(color);
	//}

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

		GetGod()->GetBonusSlotManager()->Draw();

		break;

	case TYPE_LEFT_HALF_SCREEN:
	case TYPE_RIGHT_HALF_SCREEN:

	//右下画面=====================================

		SetViewPort(TYPE_DOWN_RIGHT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		XMFLOAT3 lightPos = { 100.0f, 0.0f, -100.0f };
		SetLightPos(0, lightPos);

		GetGod()->GetSkyManager()->Draw(SKYBG_MODE_Shining);
		GetGod()->GetSlotManager()->Draw(No_slot);


	//左画面=====================================

		SetViewPort(TYPE_LEFT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		XMFLOAT3 lightPos2 = { -500.0f, 50.0f, -100.0f };
		SetLightPos(0, lightPos2);

		GetGod()->GetSkyManager()->Draw(SKYBG_MODE_Aozora);
		GetGod()->GetRoller()->Draw();
		GetGod()->GetQuestBoardManager()->Draw();
		GetGod()->GetSlotManager()->Draw(No_FlyingCrow);

	//右上画面===================================

		SetViewPort(TYPE_RIGHT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		//GetGod()->GetSkyManager()->Draw(SKYBG_MODE_Utyuu);
		//GetGod()->GetRoom()->Draw();
		//GetGod()->GetTrainingCrowSquat()->Draw();
		GetGod()->GetTrainingCrowManager()->Draw();
		break;

	case TYPE_UP_HALF_SCREEN:
	case TYPE_DOWN_HALF_SCREEN:
		SetViewPort(TYPE_UP_HALF_SCREEN);

		SetCameraAT(pos);
		SetCamera();
		SetViewPort(TYPE_DOWN_HALF_SCREEN);
		break;

	}


	m_UIManager.Draw();



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
