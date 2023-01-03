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
#include "tutorial.h"
#include "Stage_01.h"
#include "SkyManager.h"
#include "Roller.h"
#include "QuestBoardManager.h"
#include "Slot.h"
#include "FlyingCrowManager.h"
#include "slotManager.h"
#include "room.h"
#include "trainingCrow.h"
#include "TrainingCrowManager.h"
#include "bonusSlotManager.h"
#include "AnimationManager.h"
#include "Ending.h"
#include "texManager.h"
#include "Staffroll.h"
#include "RollerManager.h"

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
	g_curSceneId = TITLE_ID;

	//　管理するシーンを登場させる
	Scenes[TITLE_ID] = new Title(this);
	Scenes[TUTORIAL_ID] = new Tutorial(this);
	Scenes[STAGE_01ID] = new Stage_01(this);
	Scenes[ENDROLL_ID] = new StaffRoll(this);


	// お互いの情報を共有できるようにインスタンス化
	m_pSkymanager = new SkyManager(this);
	m_pQuestBoardManager = new QuestBoardManager(this);
	m_pSlotManager = new SlotManager(this);
	m_pTrainingCrowSquat = new TrainingCrowSquat(this);
	m_pTrainingCrowManager = new TrainingCrowManager(this);
	m_pBonusSlotManager = new BonusSlotManager(this);
	m_pTexManager = new TexManager(this);

	m_pAnimationManager = new AnimationManager(this);
	m_pRollerManager = new RollerManager(this);
	m_pCalendarNum = new CalendarNum(this);

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
	delete m_pQuestBoardManager;
	delete m_pSlotManager;
	delete m_pTrainingCrowSquat;
	delete m_pTrainingCrowManager;
	delete m_pBonusSlotManager;
	delete m_pAnimationManager;
	delete m_pTexManager;
	delete m_pRollerManager;
	delete m_pCalendarNum;

}

//=============================================================================
// 更新処理
//=============================================================================
void God::Update(void)
{
	// 現在のシーンを更新
	Scenes[g_curSceneId]->Update();

	// そのモードに再度入った際に初期化処理が行われるようにする
	if (g_curSceneId != TUTORIAL_ID) Scenes[TUTORIAL_ID]->SetInit(FALSE);
	else if (g_curSceneId != STAGE_01ID) Scenes[STAGE_01ID]->SetInit(FALSE);


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

SCENE_ID God::GetScene(void)
{
	return g_curSceneId;
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
