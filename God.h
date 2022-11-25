//=============================================================================
//
// 神の処理 [God.h]
// Author : 柏村大地
//
//=============================================================================
#pragma once

//*****************************************************************************
// マクロ定義
//*****************************************************************************
class SkyManager;
class Roller;
class QuestBoardManager;
class Slot;
class FlyingCrowManager;
class SlotManager;
class Room;
class TrainingCrowSquat;
class TrainingCrowManager;

enum SCENE_ID {
	TITLE_ID,
	STAGE_01ID,
	GAME_CLEAR_ID,
	GAME_OVER_ID,
	SCENE_MAX
};

class God
{

private:
	// シーンを用意する
	class Scene *Scenes[SCENE_MAX];

	// 神に持たせる
	 SkyManager *m_pSkymanager = nullptr;
	 Roller *m_pRoller = nullptr;
	 QuestBoardManager *m_pQuestBoardManager = nullptr;
	 //Slot *m_pSlot = nullptr;
	 //FlyingCrowManager *m_pFlyingCrowManager = nullptr;
	 SlotManager *m_pSlotManager = nullptr;
	 Room *m_pRoom = nullptr;
	 TrainingCrowSquat *m_pTrainingCrowSquat = nullptr;
	 TrainingCrowManager *m_pTrainingCrowManager = nullptr;

public:
	God();
	~God();

	// メンバ関数
	void Update();
	void Draw();
	void ChangeScene(SCENE_ID sceneId);

	// ゲッター
	SkyManager *GetSkyManager() { return m_pSkymanager; }
	Roller *GetRoller() { return m_pRoller; }
	QuestBoardManager *GetQuestBoardManager() { return m_pQuestBoardManager; }
	//Slot *GetSlot() { return m_pSlot; }
	//FlyingCrowManager *GetFlyingCrowManager() { return m_pFlyingCrowManager; }
	SlotManager *GetSlotManager() { return m_pSlotManager; }
	Room *GetRoom() { return m_pRoom; }
	TrainingCrowSquat *GetTrainingCrowSquat() { return m_pTrainingCrowSquat; }
	TrainingCrowManager *GetTrainingCrowManager() { return m_pTrainingCrowManager; }
};

//*****************************************************************************
// シーンIDのゲッター
//*****************************************************************************
SCENE_ID GetSceneID(void);
//*****************************************************************************
// シーンIDのセッター
//*****************************************************************************
void SetSceneID(SCENE_ID nextSceneId);