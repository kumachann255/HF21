//=============================================================================
//
// クエストボードマネージャー処理 [QuestBoardManager.cpp]
// Author : 柏村大地
//
//=============================================================================
#include "QuestBoardManager.h"
#include "input.h"
#include "debugproc.h"
#include "Roller.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	BOARD_ROTATE_SPEED	(0.001f)		// 回転速度
#define	BOARD_SCL			(5.0f)			// 大きさ
#define	MODEL_NAME01		"model_quest_gomi_01.obj"	// 読み込むモデル名


//=============================================================================
// コンストラクター
//=============================================================================
QuestBoardManager::QuestBoardManager(God *god) :GodObject(god)
{

}

//=============================================================================
// デストラクター
//=============================================================================
QuestBoardManager::~QuestBoardManager()
{
	const QuestBoardArray::iterator itEnd = BoardArray.end();

	for (QuestBoardArray::iterator it = BoardArray.begin(); it != itEnd; ++it) {
		delete *it;
	}

	BoardArray.clear();

}

//=============================================================================
// 更新処理
//=============================================================================
void QuestBoardManager::Update(void)
{
	if (GetKeyboardTrigger(DIK_F5))
	{
		m_StartPos = { 0.0f + (rand()%100),70.0f,0.0f };
		BoardArray.push_back(new QuestBoard(MODEL_NAME01, m_StartPos));
	}

	if (GetKeyboardTrigger(DIK_F6))
	{
		BoardArray.erase(std::cbegin(BoardArray));
	}

	const QuestBoardArray::iterator itEnd = BoardArray.end();

	for (QuestBoardArray::iterator it = BoardArray.begin(); it != itEnd; ++it)
	{
		(*it)->Update();
	}


#ifdef _DEBUG	// デバッグ情報を表示する
	PrintDebugProc("Board.Size:%d\n", BoardArray.size());
	//PrintDebugProc("BoardArray.back().GetIsUse():%d\n", BoardArray.back().GetIsUse());
#endif

}


//=============================================================================
// 描画処理
//=============================================================================
void QuestBoardManager::Draw(void)
{

	// ワールドマトリックスの初期化
	XMMATRIX mtxWorld = XMMatrixIdentity();

	const QuestBoardArray::iterator itEnd = BoardArray.end();

	for (QuestBoardArray::iterator it = BoardArray.begin(); it != itEnd; ++it) 
	{
		// 親（ローラー）のワールドマトリクス生成
		mtxWorld = GetWorldMatrix(
			GetGod()->GetRoller()->GetPrefab()->GetPos(),
			GetGod()->GetRoller()->GetPrefab()->GetRot(),
			GetGod()->GetRoller()->GetScl());

		(*it)->Draw(mtxWorld);
	}
}



//=============================================================================
// <vector>のfor文記述方式
//=============================================================================
/*

std::vector<QuestBoard>::iterator itr;     // vector<QuestBoard> の要素へのイテレータ
std::vector<QuestBoard>::iterator itr = BoardArray.begin();   // 最初の要素を指すイテレータ
auto itr = BoardArray.begin();   // 最初の要素を指すイテレータ

[1]
for (auto itr = BoardArray.begin(); itr != BoardArray.end(); ++itr) 
{

	(*itr).Draw();

}

[2]
for (int i=0; i < BoardArray.size(); i++)
{
	BoardArray[i].Draw();

}

[3]
for (QuestBoard& Board : BoardArray)
{
	Board.Draw();
}																		

*/

//=============================================================================
// <vector>の使い方
//=============================================================================
//末尾の要素を取り除くには、pop_back関数を使います。
//back関数を使うと、末尾の要素にアクセスすることができます
//任意の要素を取り除くには、erase関数を使います。
// v.erase(std::cbegin(v) + 1);で要素１を削除

//【連続している複数の要素をまとめて取り除く】
//終了位置をあらわすには「１つ後ろ」を指すよう
//v.erase(std::cbegin(v), std::cbegin(v) + 2);にすることに注意してください。0と1を削除
