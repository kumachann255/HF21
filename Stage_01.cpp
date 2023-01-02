//=============================================================================
//
// ステージ１の処理 [Stage_01.cpp]
// Author : 柏村大地
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
// マクロ定義
//*****************************************************************************

static ParticlManager *pParticlManager = nullptr;


//=============================================================================
// コンストラクター ※シーンのコンストラクターに渡してあげる
//=============================================================================
Stage_01::Stage_01(God *god):Scene(god)
{
	pParticlManager = new ParticlManager();
}

//=============================================================================
// デストラクター
//=============================================================================
Stage_01::~Stage_01()
{
	delete pParticlManager;
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
	// 初期化処理をしていない場合、メンバ変数などを一括初期化
	if (!m_isInit) InitDate();

	// シーン切り替えチェック
	NextScene();


	// カレンダー更新
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

	// テクスチャの更新処理
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
// 描画処理
//=============================================================================
void Stage_01::Draw(void)
{
	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	SetShader(SHADER_MODE_DEFAULT);
	
#ifdef _DEBUG
	// デバッグ表示
	PrintDebugProc("GetViewPortType():%d\n", GetViewPortType());
	PrintDebugProc("[enter]:スロット開始\n");
	PrintDebugProc("[space]:スロット停止\n");
	PrintDebugProc("[T]:筋トレメニュー変更\n");
	PrintDebugProc("[S]:筋トレスピードアップ / リセット\n");
	PrintDebugProc("[H]:筐体モーフィング進める\n");
	PrintDebugProc("[N]:筐体モーフィングリセット\n");

#endif

	switch (GetViewPortType())
	{
	case TYPE_FULL_SCREEN:
	//フルスクリーン=============================

		SetViewPort(TYPE_FULL_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		GetGod()->GetBonusSlotManager()->Draw();

		// テクスチャの描画処理
		{
			GetGod()->GetTexManager()->Draw();
		}


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

		SetShader(SHADER_MODE_PHONG);

		SetViewPort(TYPE_LEFT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		XMFLOAT3 lightPos2 = { -500.0f, 50.0f, -100.0f };
		SetLightPos(0, lightPos2);


		GetGod()->GetSkyManager()->Draw();

		// パーティクル
		pParticlManager->Draw(0);

		SetShader(SHADER_MODE_DEFAULT);
		SetViewPort(TYPE_LEFT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		GetGod()->GetRollerManager()->Draw();
		GetGod()->GetSlotManager()->Draw(No_FlyingCrow);
		GetGod()->GetQuestBoardManager()->Draw();

		// カレンダー描画
		GetGod()->GetCalendarNum()->Draw();



	//右上画面===================================

		SetShader(SHADER_MODE_PHONG);

		SetViewPort(TYPE_RIGHT_HALF_SCREEN);
		SetCameraAT(pos);
		SetCamera();

		//GetGod()->GetSkyManager()->Draw(SKYBG_MODE_Utyuu);
		//GetGod()->GetRoom()->Draw();
		//GetGod()->GetTrainingCrowSquat()->Draw();
		GetGod()->GetTrainingCrowManager()->Draw();

		// テクスチャの描画処理
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


#ifdef _DEBUG	// デバッグ情報を表示する

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
// シーン遷移処理
//=============================================================================
void Stage_01::NextScene(void)
{
#ifdef _DEBUG	// デバッグ情報を表示する
	// フェードアウトを開始させる
	if (GetKeyboardTrigger(DIK_1))
	{
		SetFade(FADE_OUT, TITLE_ID);
	}
#endif

	// フェードアウトが終わったらシーンを切り替える
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
