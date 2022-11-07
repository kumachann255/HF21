//=============================================================================
//
// ゲーム画面処理 [game.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "model.h"
#include "camera.h"
#include "input.h"
#include "sound.h"
#include "fade.h"
#include "game.h"

#include "player.h"
#include "enemy.h"
#include "meshfield.h"
#include "meshwall.h"
#include "shadow.h"
#include "tree.h"
#include "bullet.h"
#include "score.h"
#include "puzzleBG.h"
#include "drum.h"
#include "particle.h"
#include "collision.h"
#include "debugproc.h"
#include "prefab.h"
#include "object.h"
#include "roller.h"
#include "FlyingCrow.h"
#include "drum3D.h"
#include "housing.h"
#include "slot.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define CROWS_MAX (100)


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void CheckHit(void);



//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int	g_ViewPortType_Game = TYPE_LEFT_HALF_SCREEN;

static BOOL	g_bPause = TRUE;	// ポーズON/OFF

// ローラー
Roller *pRoller;

// ドラム3D
Drum3D* pDrum3DL;
Drum3D* pDrum3DC;
Drum3D* pDrum3DR;
Prefab *pPrefabDrum3D;

// 筐体
Housing* pHousing;
Prefab *pPrefabHousing;

// スロット
Slot* pSlot;

// イベントの建物
Object *pBuilding;
Prefab *pPrefabBuilding;

FlyingCrow *pFlyingCrow[CROWS_MAX] = {nullptr,nullptr,nullptr,nullptr,nullptr};
Prefab *pPrefabFlyingCrow[CROWS_MAX];


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitGame(void)
{
	g_ViewPortType_Game = TYPE_LEFT_HALF_SCREEN;

	// フィールドの初期化
	//InitMeshField(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), 100, 100, 13.0f, 13.0f);

	// ライトを有効化	// 影の初期化処理
	InitShadow();

	// プレイヤーの初期化
	InitPlayer();

	// エネミーの初期化
	//InitEnemy();

	// 壁の初期化
	//InitMeshWall(XMFLOAT3(0.0f, 0.0f, MAP_TOP), XMFLOAT3(0.0f, 0.0f, 0.0f),
	//	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(XMFLOAT3(MAP_LEFT, 0.0f, 0.0f), XMFLOAT3(0.0f, -XM_PI * 0.50f, 0.0f),
	//	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(XMFLOAT3(MAP_RIGHT, 0.0f, 0.0f), XMFLOAT3(0.0f, XM_PI * 0.50f, 0.0f),
	//	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(XMFLOAT3(0.0f, 0.0f, MAP_DOWN), XMFLOAT3(0.0f,  XM_PI, 0.0f),
	//	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), 16, 2, 80.0f, 80.0f);

	// 壁(裏側用の半透明)
	//InitMeshWall(XMFLOAT3(0.0f, 0.0f, MAP_TOP), XMFLOAT3(0.0f,    XM_PI, 0.0f),
	//	XMFLOAT4(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(XMFLOAT3(MAP_LEFT, 0.0f, 0.0f), XMFLOAT3(0.0f,   XM_PI * 0.50f, 0.0f),
	//	XMFLOAT4(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(XMFLOAT3(MAP_RIGHT, 0.0f, 0.0f), XMFLOAT3(0.0f, -XM_PI * 0.50f, 0.0f),
	//	XMFLOAT4(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);
	//InitMeshWall(XMFLOAT3(0.0f, 0.0f, MAP_DOWN), XMFLOAT3(0.0f, 0.0f, 0.0f),
	//	XMFLOAT4(1.0f, 1.0f, 1.0f, 0.25f), 16, 2, 80.0f, 80.0f);

	// 木を生やす
	InitTree();

	// 弾の初期化
	InitBullet();

	// スコアの初期化
	InitScore();

	// パーティクルの初期化
	InitParticle();

	// パズルのBGの初期化
	InitPuzzleBG();

	//==================================
	// ローラーの初期化
	pRoller = new Roller();
	pRoller->GetPrefab()->SetModel("model_map.obj");


	for (int i = 0; i < CROWS_MAX; i++)
	{
		//pFlyingCrow[i] = nullptr;
		pPrefabFlyingCrow[i] = nullptr;

		// カラスのモデル読み込み
		pPrefabFlyingCrow[i] = new Prefab();
	}

	pPrefabFlyingCrow[0]->SetModel("model_crow.obj");

	// ドラムの初期化
	InitDrum();


	// ドラム3Dの初期化
	pDrum3DL = new Drum3D();
	pDrum3DC = new Drum3D();
	pDrum3DR = new Drum3D();
	pPrefabDrum3D = new Prefab();
	pPrefabDrum3D->SetModel("model_slot_roll.obj");

	// ドラム3Dの大きさセット
	pDrum3DL->SetPrefab(pPrefabDrum3D);
	pDrum3DC->SetPrefab(pPrefabDrum3D);
	pDrum3DR->SetPrefab(pPrefabDrum3D);
	XMFLOAT3 sclDrum3D = { 1.0f,1.0f,1.0f };
	pDrum3DL->SetScl(sclDrum3D);
	pDrum3DC->SetScl(sclDrum3D);
	pDrum3DR->SetScl(sclDrum3D);

	// ドラム3Dの位置セット
	XMFLOAT3 posDrum3DL = { -5.0f,0.0f,0.0f };
	XMFLOAT3 posDrum3DC = { 0.0f,0.0f,0.0f };
	XMFLOAT3 posDrum3DR = { 5.0f,0.0f,0.0f };
	pDrum3DL->SetPos(posDrum3DL);
	pDrum3DC->SetPos(posDrum3DC);
	pDrum3DR->SetPos(posDrum3DR);

	// 筐体の初期化
	pHousing = new Housing();
	pPrefabHousing = new Prefab();
	pPrefabHousing->SetModel("model_slot.obj");

	// 筐体の大きさセット
	pHousing->SetPrefab(pPrefabHousing);
	XMFLOAT3 sclHousing = { 1.0f,1.0f,1.0f };
	pHousing->SetScl(sclHousing);

	// 筐体の向きセット
	XMFLOAT3 rotHousing = { 0.0f,3.14f,0.0f };
	pHousing->SetRot(rotHousing);


	// スロットの初期化
	pSlot = new Slot(pHousing, pDrum3DL, pDrum3DC, pDrum3DR);

	// BGM再生
	//PlaySound(SOUND_LABEL_BGM_sample001);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitGame(void)
{
	// ドラムの終了りょり
	UninitDrum();

	// パズルのBGの終了処理
	UninitPuzzleBG();

	// パーティクルの終了処理
	//UninitParticle();

	// スコアの終了処理
	UninitScore();

	// 弾の終了処理
	//UninitBullet();

	// 木の終了処理
	//UninitTree();

	// 壁の終了処理
	//UninitMeshWall();

	// 地面の終了処理
	//UninitMeshField();

	// エネミーの終了処理
	//UninitEnemy();

	// プレイヤーの終了処理
	UninitPlayer();

	// 影の終了処理
	//UninitShadow();

	// オブジェクト関係の終了処理
	delete pRoller;
	for (int i = 0; i < CROWS_MAX; i++)
	{
		if (pFlyingCrow[i]) delete pFlyingCrow[i];
		delete pPrefabFlyingCrow[i];

	}

	delete pDrum3DL;
	delete pDrum3DC;
	delete pDrum3DR;
	delete pPrefabDrum3D;
	delete pHousing;
	delete pPrefabHousing;
	delete pSlot;

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateGame(void)
{
#ifdef _DEBUG
	if (GetKeyboardTrigger(DIK_V))
	{
		g_ViewPortType_Game = (g_ViewPortType_Game + 1) % TYPE_NONE;
		SetViewPort(g_ViewPortType_Game);
	}

	if (GetKeyboardTrigger(DIK_P))
	{
		g_bPause = g_bPause ? FALSE : TRUE;
	}


#endif

	if(g_bPause == FALSE)
		return;

	//// 地面処理の更新
	//UpdateMeshField();

	// プレイヤーの更新処理
	UpdatePlayer();

	// エネミーの更新処理
	//UpdateEnemy();

	// 壁処理の更新
	//UpdateMeshWall();

	// 木の更新処理
	//UpdateTree();

	// 弾の更新処理
	//UpdateBullet();

	// パーティクルの更新処理
	//UpdateParticle();

	// 影の更新処理
	//UpdateShadow();

	// 当たり判定処理
	//CheckHit();

	// スコアの更新処理
	UpdateScore();

	// パズルのBGの更新処理
	UpdatePuzzleBG();

	// ローラーの更新
	pRoller->Update();

	// スカイドームの更新

	// 空飛ぶカラスの更新
	for (int i = 0; i < CROWS_MAX; i++)
	{
		if (pFlyingCrow[i])
		{
			pFlyingCrow[i]->Update();
			if (pFlyingCrow[i]->GetTime() >= 1.0f)
			{
				delete pFlyingCrow[i];
				pFlyingCrow[i] = nullptr;
			}
		}
	}

	// ドラムの更新処理
	UpdateDrum();

	// ドラム3Dの更新処理
	pDrum3DL->Update();
	pDrum3DC->Update();
	pDrum3DR->Update();

	// スロットの更新処理
	pSlot->Update();

	// 色の反映
	SetColorTemp(pSlot->GetColor());
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawGame0(void)
{


	// 3Dの物を描画する処理
	// 地面の描画処理
	//DrawMeshField();

	// 影の描画処理
	//DrawShadow();

	// エネミーの描画処理
	//DrawEnemy();

	// プレイヤーの描画処理
	//DrawPlayer();

	// 弾の描画処理
	//DrawBullet();

	// 壁の描画処理
	//DrawMeshWall();

	// 木の描画処理
	//DrawTree();

	// パーティクルの描画処理
	//DrawParticle();

	// スカイドームの描画処理

	// イベントの建物描画処理

	//pBuilding->Draw();


	// ローラーの描画処理
	//pRoller->Draw();

	// ドラム3Dの描画処理
	pDrum3DL->Draw();
	pDrum3DC->Draw();
	pDrum3DR->Draw();

	// 筐体の描画処理
	pHousing->Draw();



	// 空飛ぶカラスの描画処理
	for (int i = 0; i < CROWS_MAX; i++)
	{
		if (pFlyingCrow[i]) pFlyingCrow[i]->Draw();
	}

	// 2Dの物を描画する処理
	// Z比較なし
	SetDepthEnable(FALSE);

	// ライティングを無効
	SetLightEnable(FALSE);

	// ビューポートの切り換え
	SetViewPort(TYPE_FULL_SCREEN);

	// スコアの描画処理
	DrawScore();

	// パズル画面の描画
	DrawPizzle();


	// ライティングを有効に
	SetLightEnable(TRUE);

	// Z比較あり
	SetDepthEnable(TRUE);
}

void DrawPizzle(void)
{
	DrawPuzzleBG();

	DrawDrum();
}

void DrawGame(void)
{
	XMFLOAT3 pos;


#ifdef _DEBUG
	// デバッグ表示
	PrintDebugProc("ViewPortType:%d\n", g_ViewPortType_Game);

#endif

	// プレイヤー視点
	pos = GetPlayer()->pos;
	pos.y = 0.0f;			// カメラ酔いを防ぐためにクリアしている
	SetCameraAT(pos);
	SetCamera();

	//SetShader(SHADER_MODE_PHONG);
	SetShader(SHADER_MODE_DEFAULT);
	
	switch(g_ViewPortType_Game)
	{
	case TYPE_FULL_SCREEN:
		SetViewPort(TYPE_FULL_SCREEN);
		DrawGame0();
		break;

	case TYPE_LEFT_HALF_SCREEN:
	case TYPE_RIGHT_HALF_SCREEN:
		SetViewPort(TYPE_LEFT_HALF_SCREEN);
		SetCamera();

		DrawGame0();

		// エネミー視点
		pos = GetEnemy()->pos;

		pos.y = 0.0f;
		//SetCameraAT(pos);
		//SetCamera();
		SetViewPort(TYPE_RIGHT_HALF_SCREEN);

		for (int i = 0; i < CROWS_MAX; i++)
		{
			if (pFlyingCrow[i]) pos = pFlyingCrow[i]->GetPos();
		}

		SetCameraAT(pos);
		SetCamera();

		//SetShader(SHADER_MODE_DEFAULT);
		DrawGame0();
		break;

	case TYPE_UP_HALF_SCREEN:
	case TYPE_DOWN_HALF_SCREEN:
		SetViewPort(TYPE_UP_HALF_SCREEN);
		DrawGame0();

		// エネミー視点
		pos = GetEnemy()->pos;
		pos.y = 0.0f;
		SetCameraAT(pos);
		SetCamera();
		SetViewPort(TYPE_DOWN_HALF_SCREEN);
		DrawGame0();
		break;

	}
}


//=============================================================================
// 当たり判定処理
//=============================================================================
void CheckHit(void)
{
	ENEMY *enemy = GetEnemy();		// エネミーのポインターを初期化
	PLAYER *player = GetPlayer();	// プレイヤーのポインターを初期化
	BULLET *bullet = GetBullet();	// 弾のポインターを初期化

	// 敵とプレイヤーキャラ
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		//敵の有効フラグをチェックする
		if (enemy[i].use == FALSE)
			continue;

		//BCの当たり判定
		if (CollisionBC(player->pos, enemy[i].pos, player->size, enemy[i].size))
		{
			// 敵キャラクターは倒される
			enemy[i].use = FALSE;
			ReleaseShadow(enemy[i].shadowIdx);

			// スコアを足す
			AddScore(100);
		}
	}


	// プレイヤーの弾と敵
	for (int i = 0; i < MAX_BULLET; i++)
	{
		//弾の有効フラグをチェックする
		if (bullet[i].use == FALSE)
			continue;

		// 敵と当たってるか調べる
		for (int j = 0; j < MAX_ENEMY; j++)
		{
			//敵の有効フラグをチェックする
			if (enemy[j].use == FALSE)
				continue;

			//BCの当たり判定
			if (CollisionBC(bullet[i].pos, enemy[j].pos, bullet[i].fWidth, enemy[j].size))
			{
				// 当たったから未使用に戻す
				bullet[i].use = FALSE;
				ReleaseShadow(bullet[i].shadowIdx);

				// 敵キャラクターは倒される
				enemy[j].use = FALSE;
				ReleaseShadow(enemy[j].shadowIdx);

				// スコアを足す
				AddScore(10);
			}
		}

	}


	// エネミーが全部死亡したら状態遷移
	int enemy_count = 0;
	for (int i = 0; i < MAX_ENEMY; i++)
	{
		if (enemy[i].use == FALSE) continue;
		enemy_count++;
	}

	// エネミーが０匹？
	if (enemy_count == 0)
	{
		SetFade(FADE_OUT, MODE_RESULT);
	}

}


void SetShotCrows(XMFLOAT4 color)
{
	int a = rand() % (CROWS_MAX - 2) + 2;

	for (int i = 0; i < a; i++)
	{
		XMFLOAT3 targetPos = { -50.0f, 20.0f, -100.0f };
		// 飛んでいくカラスの初期化
		pFlyingCrow[i] = new FlyingCrow(color, targetPos);

		// 飛んでいくカラスの大きさセット
		pFlyingCrow[i]->SetPrefab(pPrefabFlyingCrow[0]);
		XMFLOAT3 scl3 = { 0.3f,0.3f,0.3f };
		pFlyingCrow[i]->SetScl(scl3);
		pPrefabFlyingCrow[0]->SetColor(color);
	}
}
