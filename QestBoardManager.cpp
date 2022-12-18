//=============================================================================
//
// クエストボードマネージャー処理 [QuestBoardManager.cpp]
// Author : 柏村大地
//
//=============================================================================
#include "QuestBoardManager.h"
#include "input.h"
//#include "debugproc.h"
#include "RollerManager.h"
#include "TrainingCrowManager.h"
#include "slotManager.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	BOARD_ROTATE_SPEED	(0.001f)		// 回転速度
#define	BOARD_SCL			(5.0f)			// 大きさ
#define	MODEL_NAME01		"model_questboard_garbage02.obj"	// 読み込むモデル名
#define BOARD_OFFSET_Y		(70.0f)							// ボードの足元をあわせる
#define BOARD_MAKETIME		(810)							// ボードの出現時間

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

	m_pGarbageIcon = new GarbageIcon();
	m_pCalendarNum = new CalendarNum();

	XMFLOAT3 rot = { 0.0f, 3.14f, 0.0f };
	pQuestBoard = new QuestBoard(MODEL_NAME01, m_StartPos, rot);

}

//=============================================================================
// デストラクター
//=============================================================================
QuestBoardManager::~QuestBoardManager()
{
	BoardArray.clear();

	for (size_t i = 0; i < BoardArray.size(); i++)
	{
		delete BoardArray[i];
	}

	// ランプテクスチャーの開放
	for (int i = 0; i < LAMP_TYPE_MAX; i++)
	{
		if (m_Texture[i])
		{
			m_Texture[i]->Release();
			m_Texture[i] = nullptr;
		}
	}

	delete m_pGarbageIcon;
	delete m_pCalendarNum;
	delete pQuestBoard;
}

//=============================================================================
// 更新処理
//=============================================================================
void QuestBoardManager::Update(void)
{
	float rotX = GetGod()->GetRollerManager()->GetRoller()->GetPrefab()->GetRot().x;
	rotX = XMConvertToDegrees(rotX);
	int AppearRot = (int)(rotX / 45.0f);

	// カウントの更新とリセット
	m_MakeCnt += 1;
	if (m_MakeCnt > BOARD_MAKETIME) m_MakeCnt = 0;


	// カウント値に達したらボードを出現させる
	if (m_MakeCnt == BOARD_MAKETIME){

		// 出現する座標をセット
		m_StartPos = { -200.0f + (rand() % 280),BOARD_OFFSET_Y,0.0f };

		// 動的に生成
		XMFLOAT3 rot = { 0.0f, 3.14f, 0.0f };
		BoardArray.push_back(new QuestBoard( m_StartPos , rot));

		switch (rand() % 2)
		{
		case 0:
			PlaySound(SOUND_LABEL_SE_se_quest_pop_0); // クエスト出現
			break;

		case 1:
			PlaySound(SOUND_LABEL_SE_se_quest_pop_1); // クエスト出現
			break;
		}

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

	// モデルをセット
	for (int i = 0; i < BoardArray.size(); i++)
	{
		if (BoardArray.empty()) return;

		DX11_MODEL model = pQuestBoard->GetPrefab()->GetModelDate();
		BoardArray[i]->GetPrefab()->SetModelDate(model);
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

			switch (rand() % 4)
			{
			case 0:
				PlaySound(SOUND_LABEL_SE_se_mens_hihi); // クエスト達成
				break;

			case 1:
				PlaySound(SOUND_LABEL_SE_se_mens_ou); // クエスト達成
				break;

			case 2:
				PlaySound(SOUND_LABEL_SE_se_mens_yei); // クエスト達成
				break;

			case 3:
				PlaySound(SOUND_LABEL_SE_se_women_ou); // クエスト達成
				break;
			}

			if (!this->GetGod()->GetSlotManager()->GetRainbow())
			{
				this->GetGod()->GetTrainingCrowManager()->AddStock();
			}

			int probability = rand() % 10;

			if (probability - m_failureCount < 2)
			{
				m_failureCount = 0;
				this->GetGod()->GetTrainingCrowManager()->SetSuccess(TRUE);
			}
			else
			{
				m_failureCount++;
			}

			m_MissionPoint--;

		}
	}

	m_pGarbageIcon->SetIconNum(m_MissionPoint);
	m_pGarbageIcon->Update();

	m_pCalendarNum->Update();

	// 消す処理	(時間切れ)
	if (!BoardArray.empty()){
		// 210度回転したら消す
		if(BoardArray[0]->GetRot().x > XMConvertToRadians(210.0f))
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

//#ifdef _DEBUG	// デバッグ情報を表示する
//	PrintDebugProc("ローラーの回転角度 %f \n", rotX);
//	PrintDebugProc("ローラーの回転角度/45.0f =  %d \n", AppearRot);
//#endif

}


//=============================================================================
// 描画処理
//=============================================================================
void QuestBoardManager::Draw(void)
{
	// ワールドマトリックスの初期化
	XMMATRIX mtxWorld = XMMatrixIdentity();

	for (size_t i = 0; i < BoardArray.size(); i++)
	{
		if (BoardArray.empty()) return;

		XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
		rot.x = BoardArray[i]->GetRot().x;	// 自分自身の回転(0度から始めたいから)
		rot.y = GetGod()->GetRollerManager()->GetRoller()->GetPrefab()->GetRot().y;
		rot.z = GetGod()->GetRollerManager()->GetRoller()->GetPrefab()->GetRot().z;


		//================================
		// ボードの描画(ローラーが親)
		//================================

				// 親（ローラー）のワールドマトリクス生成
		mtxWorld = GetWorldMatrix(
			GetGod()->GetRollerManager()->GetRoller()->GetPrefab()->GetPos(),
			rot,
			//GetGod()->GetRollerManager()->GetRoller()->GetScl());
			XMFLOAT3(1.0f, 1.0f, 1.0f));

		// ボードの描画
		BoardArray[i]->Draw(mtxWorld);

		//================================
		// ランプの描画処理(ボードが親)
		//================================

				// 親(ボード)のワールドマトリクス生成
		mtxWorld = GetWorldMatrix(
			BoardArray[i]->GetPos(),
			rot,
			XMFLOAT3(1.0f, 1.0f, 1.0f));

		// フォンシェーダーへ変更
		//SetShader(SHADER_MODE_PHONG);
		//SetViewPort(TYPE_LEFT_HALF_SCREEN);
		//SetCameraAT(XMFLOAT3(0.0f,0.0f,0.0f));
		//SetCamera();


		// ランプの描画
		BoardArray[i]->GetLampManager()->Draw(mtxWorld);
	}

	m_pGarbageIcon->Draw();
	m_pCalendarNum->Draw();
}

int QuestBoardManager::GetSerchBoard(int colorType)
{
	//Lamp *lampFlont = BoardArray.front()->GetLampManager()->GetLamp();
	//lampFlont[0].GetColorTypeId;

	for (int i = 0; i < BoardArray.size(); i++)
	{
		if (BoardArray.empty()) continue;

		Lamp *lamp = BoardArray[i]->GetLampManager()->GetLamp();
		for (int p = 0; p < 3; p++)
		{
			if ((lamp[p].GetColorTypeId() == colorType) && (lamp[p].GetIsUse()) && (!lamp[p].GetDelete()))
			{
				lamp[p].SetDelete(TRUE);
				PlaySound(SOUND_LABEL_SE_se_lamp_clear);
				
				return i;
			}
		}
	}

	return LAMP_TYPE_NONE;
}

int QuestBoardManager::GetSerchBoardRainbow(void)
{
	for (int i = 0; i < BoardArray.size(); i++)
	{
		if (BoardArray.empty()) continue;

		Lamp *lamp = BoardArray[i]->GetLampManager()->GetLamp();
		for (int p = 0; p < 3; p++)
		{
			if ((lamp[p].GetIsUse()) && (!lamp[p].GetDelete()))
			{
				lamp[p].SetDelete(TRUE);
				return i;
			}
		}
	}

	return LAMP_TYPE_NONE;
}
