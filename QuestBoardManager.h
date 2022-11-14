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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MODEL_NAME			"model_quest_questboard.obj"	// 読み込むモデル名

//*****************************************************************************
// クラス定義
//*****************************************************************************

// クラスを格納する配列の定義（STL）
typedef std::vector<QuestBoard*> QuestBoardArray;

class QuestBoardManager :public GodObject
{
private:
	QuestBoardArray BoardArray;
	XMFLOAT3 m_StartPos{ 0.0f ,0.0f,0.0f };

	//std::vector<QuestBoard>BoardArray;

public:
	QuestBoardManager(God *god);
	~QuestBoardManager();

	// メンバ関数
	void Update(void);
	void Draw(void);

};

