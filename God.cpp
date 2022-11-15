//=============================================================================
//
// 神の処理 [God.cpp]
// Author : 柏村大地
//
//=============================================================================
#include "God.h"
#include "debugproc.h"
#include "input.h"
#include "Title.h"
#include "Stage_01.h"
#include "SkyManager.h"
#include "Roller.h"
#include "QuestBoardManager.h"
#include "Slot.h"
#include "FlyingCrowManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

// 現在のシーンID
static SCENE_ID g_curSceneId;

//=============================================================================
// コンストラクター
//=============================================================================
God::God()
{
	// 初めのシーンIDを設定
	g_curSceneId = STAGE_01ID;

	//　管理するシーンを登場させる
	Scenes[TITLE_ID] = new Title(this);
	Scenes[STAGE_01ID] = new Stage_01(this);


	// お互いの情報を共有できるようにインスタンス化
	m_pSkymanager = new SkyManager(this);
	m_pRoller = new Roller(this);
	m_pQuestBoardManager = new QuestBoardManager(this);
	m_pSlot = new Slot(this);
	m_pFlyingCrowManager = new FlyingCrowManager(this);

}

//=============================================================================
// デストラクター
//=============================================================================
God::~God()
{
	for (int i = 0; i < SCENE_MAX; i++) {
		delete Scenes[i];
	}

	delete m_pSkymanager;
	delete m_pRoller;
	delete m_pQuestBoardManager;
	delete m_pSlot;
	delete m_pFlyingCrowManager;
}

//=============================================================================
// 更新処理
//=============================================================================
void God::Update(void)
{
	// 現在のシーンを更新
	Scenes[g_curSceneId]->Update();

	//if (GetKeyboardTrigger(DIK_F1))
	//{
	//	Scenes[m_curSceneId]->NextScene();
	//}

}

//=============================================================================
// 描画処理
//=============================================================================
void God::Draw(void)
{
	// 現在のシーンを更新
	Scenes[g_curSceneId]->Draw();

}


//=============================================================================
// シーン切り替え処理
//=============================================================================
void God::ChangeScene(SCENE_ID sceneId)
{
	g_curSceneId = sceneId;
	Scenes[g_curSceneId]->Init();
}


//*****************************************************************************
// シーンのゲッター
//*****************************************************************************
SCENE_ID GetSceneID(void)
{
	return g_curSceneId;
}
//*****************************************************************************
// シーンのセッター
//*****************************************************************************
void SetSceneID(SCENE_ID nextSceneId)
{
	g_curSceneId = nextSceneId;
}
