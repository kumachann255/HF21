//=============================================================================
//
// クエストボードマネージャー処理 [QuestBoardManager.cpp]
// Author : 柏村大地
//
//=============================================================================
#include "QuestBoardManager.h"
#include "input.h"
//#include "debugproc.h"
#include "Roller.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	BOARD_ROTATE_SPEED	(0.001f)		// 回転速度
#define	BOARD_SCL			(5.0f)			// 大きさ
#define	MODEL_NAME01		"model_quest_questboard.obj"	// 読み込むモデル名
#define BOARD_OFFSET_Y		(70.0f)							// ボードの足元をあわせる
#define BOARD_MAKETIME		(800)							// ボードの出現時間


static char *g_TextureName[LAMP_TYPE_MAX] =
{
	"data/TEXTURE/LAMP/tex_lamp_red.jpg",
	"data/TEXTURE/LAMP/tex_lamp_blue.jpg",
	"data/TEXTURE/LAMP/tex_lamp_green.jpg",
	"data/TEXTURE/LAMP/tex_lamp_yellow.jpg",
	"data/TEXTURE/LAMP/tex_lamp_pink.jpg",
	"data/TEXTURE/LAMP/tex_lamp_purple.jpg",
	"data/TEXTURE/LAMP/tex_lamp_orange.jpg"
};


//=============================================================================
// コンストラクター
//=============================================================================
QuestBoardManager::QuestBoardManager(God *god) :GodObject(god)
{
	// ランプテクスチャーの生成
	for (int i = 0; i < LAMP_TYPE_MAX; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
			nullptr,
			nullptr,
			&m_Texture[i],
			nullptr);
	}

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


	// ランプテクスチャーの開放
	for (int i = 0; i < LAMP_TYPE_MAX; i++)
	{
		if (m_Texture[i])
		{
			m_Texture[i]->Release();
			m_Texture[i] = nullptr;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void QuestBoardManager::Update(void)
{
	// カウントの更新とリセット
	m_MakeCnt += 1;
	if (m_MakeCnt > BOARD_MAKETIME) m_MakeCnt = 0;


	// カウント値に達したらボードを出現させる
	if (m_MakeCnt == BOARD_MAKETIME){

		// 出現する座標をセット
		m_StartPos = { -200.0f + (rand() % 280),BOARD_OFFSET_Y,0.0f };

		// 動的に生成
		XMFLOAT3 rot = { 0.0f,0.0f, 0.0f };
		BoardArray.push_back(new QuestBoard(MODEL_NAME01, m_StartPos , rot));

		//=============================================
		/*ここにサウンド入れて!!クエストボード出現音*/
		//=============================================

		 //ランプのテクスチャーをセット
		Lamp *pLamp = BoardArray.back()->GetLampManager()->GetLamp();
		int colorId = rand() % 4;	// 今は４種類にしている

		// ランプのテクスチャーとColorTypeIdの設定
		for (int i = 0; i < LAMP_MAX; i++)
		{
			int colorId = rand() % 4;
			pLamp[i].SetColorTypeId(colorId);
			pLamp[i].GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[colorId];
		}
	}

	// 消す処理	(成功)
	if (!BoardArray.empty()) {

		// ボード一番前の要素を取得
		Lamp *pLamp = BoardArray.front()->GetLampManager()->GetLamp();

		// ランプの使用フラグを取得
		// ３つのランプが消えていたらボードを消滅させる
		if (!pLamp[0].GetIsUse() &&
			!pLamp[1].GetIsUse() &&
			!pLamp[2].GetIsUse() )
		{
			BoardArray.erase(std::cbegin(BoardArray));

			//=============================================
			/*ここにサウンド入れて!!クエストボード消滅音(成功)*/
			//=============================================

		}

	}


	// 消す処理	(時間切れ)
	if (!BoardArray.empty()){
		// 120度回転したら消す
		if(BoardArray[0]->GetRot().x > XMConvertToRadians(120.0f))
		{
			BoardArray.erase(std::cbegin(BoardArray));

			//=============================================
			/*ここにサウンド入れて!!クエストボード消滅音(時間切れ)*/
			//=============================================

		}
	}


	for (int i = 0; i < BoardArray.size(); i++)
	{
		BoardArray[i]->Update();

	}

	//const QuestBoardArray::iterator itEnd = BoardArray.end();
	//for (QuestBoardArray::iterator it = BoardArray.begin(); it != itEnd; ++it)
	//{
	//	(*it)->Update();
	//}

}


//=============================================================================
// 描画処理
//=============================================================================
void QuestBoardManager::Draw(void)
{
	// ワールドマトリックスの初期化
	XMMATRIX mtxWorld = XMMatrixIdentity();

	const QuestBoardArray::iterator itEnd = BoardArray.end();

	for (QuestBoardArray::iterator board = BoardArray.begin(); board != itEnd; ++board)
	{
		XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
		rot.x = (*board)->GetRot().x;	// 自分自身の回転(0度から始めたいから)
		rot.y = GetGod()->GetRoller()->GetPrefab()->GetRot().y;
		rot.z = GetGod()->GetRoller()->GetPrefab()->GetRot().z;


//================================
// ボードの描画(ローラーが親)
//================================

		// 親（ローラー）のワールドマトリクス生成
		mtxWorld = GetWorldMatrix(
			GetGod()->GetRoller()->GetPrefab()->GetPos(),
			rot,
			GetGod()->GetRoller()->GetScl());

		// ボードの描画
		(*board)->Draw(mtxWorld);

//================================
// ランプの描画処理(ボードが親)
//================================

		// 親(ボード)のワールドマトリクス生成
		mtxWorld = GetWorldMatrix(
			(*board)->GetPos(),
			rot,
			(*board)->GetPrefab()->GetScl());

		// ランプの描画
		(*board)->GetLampManager()->Draw(mtxWorld);
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
