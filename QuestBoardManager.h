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

//*****************************************************************************
// マクロ定義
//*****************************************************************************

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
	int m_MakeCnt = 0;		// 出現カウント
	int m_colorId[5][3];	// ボード５個分

	int m_failureCount = 0;

	// ランプのテクスチャー
	ID3D11ShaderResourceView	*m_Texture[LAMP_TYPE_MAX] = { nullptr };

public:
	QuestBoardManager(God *god);
	~QuestBoardManager();

	QuestBoardArray *GetBoardArray(void) { return &BoardArray; }
	int GetRampColor(void) { BoardArray.size(); }

	void Update(void);
	void Draw(void);

	int GetSerchBoard(int colorType);
	int GetSerchBoardRainbow(void);
};

