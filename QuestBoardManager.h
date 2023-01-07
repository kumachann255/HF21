//=============================================================================
//
// クエストボードマネージャー処理 [QuestBoardManager.h]
// Author : 柏村大地
//
//=============================================================================
#pragma once
#include "QuestBoard.h"
#include "GodObject.h"
#include <vector>
#include "LampManager.h"
#include "garbageIcon.h"
#include "calendar_num.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MAX_MISSION_POINT	(20)
#define MAX_GARBAGE_NUM		(6)
#define BOARD_MAKETIME		(810)							// ボードの出現時間

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Prefab;
class ParticlManager;

// クラスを格納する配列の定義（STL）
typedef std::vector<QuestBoard*> QuestBoardArray;

class QuestBoardManager :public GodObject
{
private:
	QuestBoardArray BoardArray;
	QuestBoard *pQuestBoard = nullptr;
	Prefab *m_pHumanPrefab = nullptr;
	XMFLOAT3 m_StartPos{ 0.0f ,0.0f,0.0f };
	int m_MakeCnt = 0;			// 出現カウント
	int m_EffectCnt = 0;		// エッフェクト発生カウント
	int m_colorId[5][3];		// ボード５個分
	int m_MaxGarbageCnt = MAX_GARBAGE_NUM;	// ゴミの上限

	GarbageIcon *m_pGarbageIcon = nullptr;
	int m_MissionPoint = 0;

	int m_Speed = BOARD_MAKETIME;

	// ランプのテクスチャー
	ID3D11ShaderResourceView	*m_Texture[LAMP_TYPE_MAX] = { nullptr };
	ParticlManager *pParticlManager = nullptr;

public:
	QuestBoardManager(God *god);
	~QuestBoardManager();

	QuestBoardArray *GetBoardArray(void) { return &BoardArray; }

	int GetRampColor(void) { BoardArray.size(); }

	void Update(void);
	void Draw(void);

	int GetSerchBoard(int colorType);
	int GetSerchBoardRainbow(void);

	void Init();
};

