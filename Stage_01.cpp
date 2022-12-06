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
#include "FLUID3D_GPU.h"
#include "renderer.h"
#include "texManager.h"
#include "UI.h"
#include "particle.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

FLUID3D_GPU* m_pSolverGPU;


//=============================================================================
// コンストラクター ※シーンのコンストラクターに渡してあげる
//=============================================================================
Stage_01::Stage_01(God *god):Scene(god)
{
	////ソルバー生成
	m_pSolverGPU = new FLUID3D_GPU;

	m_pSolverGPU->Init(GetDevice(), GetDeviceContext(), SCREEN_WIDTH, SCREEN_HEIGHT
		, GetRenderTargetView(), GetDepthStencilView());

	XMFLOAT3 pos = { -50.0f,-10.0f,0.0f };
	XMFLOAT3 scl = { 100.0f,50.0f,100.0f };

	m_pSolverGPU->SetPos(pos);
	m_pSolverGPU->SetScl(scl);

	// パーティクル初期化
	InitParticle();

}

//=============================================================================
// デストラクター
//=============================================================================
Stage_01::~Stage_01()
{
	delete m_pSolverGPU;

	// パーティクル終了
	UninitParticle();

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

	// パーティクル更新
	UpdateParticle();


	//流体計算
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


	// テクスチャの更新処理
	{
		for (int i = 0; i < TELOP_TEXTURE_MAX; i++)
		{
			GetGod()->GetTexManager()->GetUIManager()->GetUIObject(0)->Update();
		}
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

		GetGod()->GetBonusSlotManager()->Draw();
		m_pSolverGPU->DrawFluid();

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
		DrawParticle();

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


	// テクスチャの更新処理
	{
		for (int i = 0; i < TELOP_TEXTURE_MAX; i++)
		{
			GetGod()->GetTexManager()->GetUIManager()->GetUIObject(0)->Draw();
		}
	}

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
		GetGod()->ChangeScene(ENDROLL_ID);

	}
}
