//=============================================================================
//
// タイトル画面処理 [Title.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "sprite.h"
#include "Title.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_MAX		(22)		// テクスチャの数
#define DEBUGPOS_ADD	(1.0f)		// デバッグ用POSの加減算用
#define CURTAIN_ADD		(5.0f)		// カーテンの加減算用
#define EGG_ADD			(1.0f)		// 卵の加減算用
#define SWAY_VALUE		(1000)		// 卵バイブレーション用値
#define VARIABLE_RADIUS	(157)		// 可変半径
#define ROT_VALUE		(0.05f)		// 回転値
#define ACCEL_VALUE		(1.01f)		// 加速値
#define ROT_MAX			(1000.0f)	// 最大回転値
#define COUNT_TIMER		(1000)		// 動きだし用ダサくて、ごめんなさいね

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;		// 頂点情報
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

static char *g_TexturName[TEXTURE_MAX] = {
	"data/TEXTURE/TITLE02/title_waku.png",			// 00 大枠（NoMove）
	"data/TEXTURE/TITLE02/title_roleRingBlue.png",	// 01 ロールリング（Move）
	"data/TEXTURE/TITLE02/title_exit01.png",		// 02 Exit（NoMove）
	"data/TEXTURE/TITLE02/title_start01.png",		// 03 Start（NoMove）
	"data/TEXTURE/TITLE02/title_finger.png",		// 04 カーソルフィンガー（Move）
	"data/TEXTURE/TITLE02/title_poleR.png",			// 05 ポール赤
	"data/TEXTURE/TITLE02/title_poleG.png",			// 06 ポール緑
	"data/TEXTURE/TITLE02/title_poleB.png",			// 07 ポール青
	"data/TEXTURE/TITLE02/title_poleY.png",			// 08 ポール黄色
	"data/TEXTURE/TITLE02/title_poleO.png",			// 09 ポールオレンジ
	"data/TEXTURE/TITLE02/title_poleP.png",			// 10 ポール紫
	"data/TEXTURE/TITLE02/title_starL.png",			// 11 星修飾左
	"data/TEXTURE/TITLE02/title_starR.png",			// 12 星修飾右
	"data/TEXTURE/TITLE02/title_starU.png",			// 13 星修飾縦
	"data/TEXTURE/TITLE02/colorse_TITLE_logo.png",	// 14 タイトルロゴ
	"data/TEXTURE/TITLE02/syugou.png",				// 15 集合
	"data/TEXTURE/TITLE02/red.png",					// 16 赤
	"data/TEXTURE/TITLE02/green.png",				// 17 緑
	"data/TEXTURE/TITLE02/blue.png",				// 18 青
	"data/TEXTURE/TITLE02/pink.png",				// 19 ピンク
	"data/TEXTURE/TITLE02/yellow.png",				// 20 黄色
	"data/TEXTURE/TITLE02/title_tex_transition_crow.png",				// 21 トランジション

};

static BOOL	g_Load = FALSE;
static int  transisionCount;

// タイトルオブジェクトのインスタンス
s_Title titleObj[TITLE_MAX];


//=============================================================================
// コンストラクター ※シーンのコンストラクターに渡してあげる
//=============================================================================
Title::Title(God *god) :Scene(god)
{

	ID3D11Device *pDevice = GetDevice();

	//テクスチャ生成
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TexturName[i],
			NULL,
			NULL,
			&g_Texture[i],
			NULL);
	}


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

	// メンバ変数、構造体の初期化
	Init();
}

//=============================================================================
// デストラクター
//=============================================================================
Title::~Title()
{
	UninitTitle();

}

//=============================================================================
// 初期化処理
//=============================================================================
void Title::Init(void)
{
	transisionCount = COUNT_TIMER;
	m_modeSw = CHOICE;

	// 変数の初期化(枠)
	titleObj[0].g_UD_Change = true;
	titleObj[0].g_Use = TRUE;
	titleObj[0].g_w = SCREEN_WIDTH;
	titleObj[0].g_h = SCREEN_HEIGHT;
	titleObj[0].g_Pos = XMFLOAT3(480.0f, 270.0f, 0.0f);
	titleObj[0].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[0].g_TexNo = 0;

	// 変数の初期化(ローリングリング)
	titleObj[1].g_UD_Change = true;
	titleObj[1].g_Use = TRUE;
	titleObj[1].g_w = 860;
	titleObj[1].g_h = 860;
	titleObj[1].g_Pos = XMFLOAT3(480.0f, 830.0f, 0.0f);
	titleObj[1].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[1].g_TexNo = 1;

	// 変数の初期化(タイトルロゴ)
	titleObj[2].g_UD_Change = true;
	titleObj[2].g_Use = TRUE;
	titleObj[2].g_w = 700;
	titleObj[2].g_h = 360;
	titleObj[2].g_Pos = XMFLOAT3(480.0f, 95.0f, 0.0f);
	titleObj[2].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[2].g_TexNo = 14;

	// 変数の初期化(Exit)
	titleObj[3].g_UD_Change = true;
	titleObj[3].g_Use = TRUE;
	titleObj[3].g_w = 300;
	titleObj[3].g_h = 120;
	titleObj[3].g_Pos = XMFLOAT3(250.0f, 360.0f, 0.0f);
	titleObj[3].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[3].g_TexNo = 2;

	// 変数の初期化(Start)
	titleObj[4].g_UD_Change = true;
	titleObj[4].g_Use = TRUE;
	titleObj[4].g_w = 300;
	titleObj[4].g_h = 120;
	titleObj[4].g_Pos = XMFLOAT3(710.0f, 360.0f, 0.0f);
	titleObj[4].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[4].g_TexNo = 3;

	// 変数の初期化(カーソルフィンガー)
	titleObj[5].g_UD_Change = true;
	titleObj[5].g_Use = TRUE;
	titleObj[5].g_w = 140;
	titleObj[5].g_h = 100;
	titleObj[5].g_Pos = XMFLOAT3(730.0f, 400.0f, 0.0f);
	titleObj[5].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[5].g_TexNo = 4;

	// 変数の初期化(StarLeft)
	titleObj[6].g_UD_Change = true;
	titleObj[6].g_Use = TRUE;
	titleObj[6].g_w = 340;
	titleObj[6].g_h = 120;
	titleObj[6].g_Pos = XMFLOAT3(125.0f, 55.0f, 0.0f);
	titleObj[6].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[6].g_TexNo = 11;

	// 変数の初期化(StarRight)
	titleObj[7].g_UD_Change = true;
	titleObj[7].g_Use = TRUE;
	titleObj[7].g_w = 340;
	titleObj[7].g_h = 120;
	titleObj[7].g_Pos = XMFLOAT3(860.0f, 40.0f, 0.0f);
	titleObj[7].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[7].g_TexNo = 12;

	// 変数の初期化(StarHeightL)
	titleObj[8].g_UD_Change = true;
	titleObj[8].g_Use = TRUE;
	titleObj[8].g_w = 110;
	titleObj[8].g_h = 450;
	titleObj[8].g_Pos = XMFLOAT3(45.0f, 310.0f, 0.0f);
	titleObj[8].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[8].g_TexNo = 13;

	// 変数の初期化(StarHeightR)
	titleObj[9].g_UD_Change = true;
	titleObj[9].g_Use = TRUE;
	titleObj[9].g_w = 110;
	titleObj[9].g_h = 450;
	titleObj[9].g_Pos = XMFLOAT3(910.0f, 310.0f, 0.0f);
	titleObj[9].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[9].g_TexNo = 13;

	// 変数の初期化(集合)
	titleObj[10].g_UD_Change = true;
	titleObj[10].g_Use = FALSE;
	titleObj[10].g_w = 470;
	titleObj[10].g_h = 340;
	titleObj[10].g_Pos = XMFLOAT3(490.0f, 260.0f, 0.0f);
	titleObj[10].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[10].g_TexNo = 15;

	// 変数の初期化(赤)
	titleObj[11].g_UD_Change = true;
	titleObj[11].g_Use = TRUE;
	titleObj[11].g_w = 360;
	titleObj[11].g_h = 380;
	titleObj[11].g_Pos = XMFLOAT3(490.0f, 200.0f, 0.0f);
	titleObj[11].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[11].g_TexNo = 16;

	// 変数の初期化(緑)
	titleObj[12].g_UD_Change = true;
	titleObj[12].g_Use = TRUE;
	titleObj[12].g_w = 250;
	titleObj[12].g_h = 260;
	titleObj[12].g_Pos = XMFLOAT3(600.0f, 220.0f, 0.0f);
	titleObj[12].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[12].g_TexNo = 17;

	// 変数の初期化(青)
	titleObj[13].g_UD_Change = true;
	titleObj[13].g_Use = TRUE;
	titleObj[13].g_w = 230;
	titleObj[13].g_h = 230;
	titleObj[13].g_Pos = XMFLOAT3(280.0f, 250.0f, 0.0f);
	titleObj[13].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[13].g_TexNo = 18;

	// 変数の初期化(ピンク)
	titleObj[14].g_UD_Change = true;
	titleObj[14].g_Use = TRUE;
	titleObj[14].g_w = 270;
	titleObj[14].g_h = 270;
	titleObj[14].g_Pos = XMFLOAT3(700.0f, 240.0f, 0.0f);
	titleObj[14].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[14].g_TexNo = 19;

	// 変数の初期化(黄色)
	titleObj[15].g_UD_Change = true;
	titleObj[15].g_Use = TRUE;
	titleObj[15].g_w = 250;
	titleObj[15].g_h = 250;
	titleObj[15].g_Pos = XMFLOAT3(390.0f, 220.0f, 0.0f);
	titleObj[15].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[15].g_TexNo = 20;

	// 変数の初期化(ポール赤)
	titleObj[16].g_UD_Change = true;
	titleObj[16].g_Use = TRUE;
	titleObj[16].g_w = 75;
	titleObj[16].g_h = 250;
	titleObj[16].g_Pos = XMFLOAT3(120.0f, 70.0f, 0.0f);
	titleObj[16].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[16].g_TexNo = 5;

	// 変数の初期化(ポール緑)
	titleObj[17].g_UD_Change = false;
	titleObj[17].g_Use = TRUE;
	titleObj[17].g_w = 75;
	titleObj[17].g_h = 250;
	titleObj[17].g_Pos = XMFLOAT3(160.0f, 180.0f, 0.0f);
	titleObj[17].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[17].g_TexNo = 6;

	// 変数の初期化(ポール青)
	titleObj[18].g_UD_Change = true;
	titleObj[18].g_Use = TRUE;
	titleObj[18].g_w = 75;
	titleObj[18].g_h = 250;
	titleObj[18].g_Pos = XMFLOAT3(200.0f, 70.0f, 0.0f);
	titleObj[18].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[18].g_TexNo = 7;

	// 変数の初期化(ポール黄色)
	titleObj[19].g_UD_Change = false;
	titleObj[19].g_Use = TRUE;
	titleObj[19].g_w = 75;
	titleObj[19].g_h = 250;
	titleObj[19].g_Pos = XMFLOAT3(760.0f, 80.0f, 0.0f);
	titleObj[19].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[19].g_TexNo = 8;

	// 変数の初期化(ポールオレンジ)
	titleObj[20].g_UD_Change = true;
	titleObj[20].g_Use = TRUE;
	titleObj[20].g_w = 75;
	titleObj[20].g_h = 250;
	titleObj[20].g_Pos = XMFLOAT3(800.0f, 180.0f, 0.0f);
	titleObj[20].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[20].g_TexNo = 9;

	// 変数の初期化(ポール紫)
	titleObj[21].g_UD_Change = false;
	titleObj[21].g_Use = TRUE;
	titleObj[21].g_w = 75;
	titleObj[21].g_h = 250;
	titleObj[21].g_Pos = XMFLOAT3(840.0f, 80.0f, 0.0f);
	titleObj[21].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[21].g_TexNo = 10;

	// 変数の初期化(トランジション)
	titleObj[22].g_UD_Change = true;
	titleObj[22].g_Use = TRUE;
	titleObj[22].g_w = 8500;
	titleObj[22].g_h = SCREEN_HEIGHT;
	titleObj[22].g_Pos = XMFLOAT3(5250.0f, SCREEN_CENTER_Y, 0.0f);
	titleObj[22].g_Rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	titleObj[22].g_TexNo = 21;

	PlaySound(SOUND_LABEL_BGM_title);
}

//=============================================================================
// 更新処理
//=============================================================================
void Title::Update(void)
{
	PrintDebugProc("titleObj[22].g_Pos : %f\n", titleObj[22].g_Pos.x);



	switch (m_modeSw)
	{
	case CHOICE:

		Choice(&titleObj[3].g_Pos.x, &titleObj[4].g_Pos.x, &titleObj[5].g_Pos.x);
		Rot(&titleObj[1].g_Rot.z, -0.001f);
		UpDown(&titleObj[16].g_UD_Change, &titleObj[16].g_Pos.y, 1.3f);
		UpDown(&titleObj[17].g_UD_Change, &titleObj[17].g_Pos.y, 1.1f);
		UpDown(&titleObj[18].g_UD_Change, &titleObj[18].g_Pos.y, 1.4f);
		UpDown(&titleObj[19].g_UD_Change, &titleObj[19].g_Pos.y, 1.2f);
		UpDown(&titleObj[20].g_UD_Change, &titleObj[20].g_Pos.y, 1.5f);
		UpDown(&titleObj[21].g_UD_Change, &titleObj[21].g_Pos.y, 1.1f);

		break;

	case GAME_START:

		UpDown(&titleObj[16].g_UD_Change, &titleObj[16].g_Pos.y, 1.3f);
		UpDown(&titleObj[17].g_UD_Change, &titleObj[17].g_Pos.y, 1.1f);
		UpDown(&titleObj[18].g_UD_Change, &titleObj[18].g_Pos.y, 1.4f);
		UpDown(&titleObj[19].g_UD_Change, &titleObj[19].g_Pos.y, 1.2f);
		UpDown(&titleObj[20].g_UD_Change, &titleObj[20].g_Pos.y, 1.5f);
		UpDown(&titleObj[21].g_UD_Change, &titleObj[21].g_Pos.y, 1.1f);
		Swaying(2, &titleObj[4].g_Rot.z);
		RotAccel(&titleObj[1].g_Rot.z, -0.0001f);
		RotRocket(&titleObj[11].g_Pos.x, &titleObj[11].g_Pos.y, 0.0f, -1.0f, &titleObj[11].g_Rot.z, -0.1f, 1);
		RotRocket(&titleObj[12].g_Pos.x, &titleObj[12].g_Pos.y, 1.0f, 1.0f, &titleObj[12].g_Rot.z, -0.1f, 1);
		RotRocket(&titleObj[13].g_Pos.x, &titleObj[13].g_Pos.y, -1.0f, 0.0f, &titleObj[13].g_Rot.z, -0.1f, 1);
		RotRocket(&titleObj[14].g_Pos.x, &titleObj[14].g_Pos.y, 1.0f, 0.0f, &titleObj[14].g_Rot.z, -0.1f, 1);
		RotRocket(&titleObj[15].g_Pos.x, &titleObj[15].g_Pos.y, -1.0f, 1.0f, &titleObj[15].g_Rot.z, -0.1f, 1);
		Transition(&titleObj[22].g_Pos.x, 17.0f, 3);
		break;

	case EXIT:

		SetFade(FADE_OUT, TITLE_ID);
		m_modeSw = CHOICE;

		break;
	}


#ifdef _DEBUG	// デバッグ情報を表示する

	//// ①デバッグ対象の切り替え
	//ChangeNum(&m_DebugNum);

	//// ②2D画像位置確認
	//DebugPrint(titleObj[m_DebugNum].g_Pos.x, titleObj[m_DebugNum].g_Pos.y, titleObj[m_DebugNum].g_w, titleObj[m_DebugNum].g_h);

	//// ③2D画像位置変更
	//PosCustom(&titleObj[m_DebugNum].g_Pos.x, &titleObj[m_DebugNum].g_Pos.y); // 配列の要素数にデバック番号を入れる事で（デバック対象==デバック番号）とする

	//// ④2D画像サイズ変更
	//SizeCustom(&titleObj[m_DebugNum].g_w, &titleObj[m_DebugNum].g_h); // 配列の要素数にデバック番号を入れる事で（デバック対象==デバック番号）とする

	/* ①、②、③以降の流れが重要！ChangeNum()関数でメンバ変数のm_DebugNumにアクセスしてデバック対象を決めて、それを反映させてから位置確認、位置確認をしている*/


#endif

}

//=============================================================================
// 描画処理
//=============================================================================
void Title::Draw(void)
{
	DrawTitle();

}

//=============================================================================
// シーン遷移処理
//=============================================================================
void Title::NextScene(void)
{
	// シーンを切り替える
	SetFade(FADE_OUT, MODESELECT_ID);

}

//=============================================================================
// アニメーション切り替え処理（始まり）
//=============================================================================

int Title::SetMode(int mode) // 引数に列挙演算子を入れる
{
	m_modeSw = mode;

	return m_modeSw;
}

void Title::SetBOOL(BOOL *use)
{
	if (*use) *use = FALSE;
	else if (*use == FALSE) *use = TRUE;
}


void Title::Choice(float *posExitX, float *posGameX, float *posChoiceX)
{
	if (*posChoiceX == *posExitX + 20.0f)
	{
		if (GetKeyboardTrigger(DIK_RIGHT))
		{
			PlaySound(SOUND_LABEL_SE_se_modeSelect_trance); // モードセレクト時のカーソル移動
			*posChoiceX = *posGameX + 20.0f;
		}
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			PlaySound(SOUND_LABEL_SE_se_title_quit); // タイトルゲーム終了
			m_modeSw = SetMode(EXIT); // 2 == EXIT
		}
	}

	if (*posChoiceX == *posGameX + 20.0f)
	{
		if (GetKeyboardTrigger(DIK_LEFT))
		{
			PlaySound(SOUND_LABEL_SE_se_modeSelect_trance); // モードセレクト時のカーソル移動
			*posChoiceX = *posExitX + 20.0f;
		}
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			PlaySound(SOUND_LABEL_SE_se_title_start); // タイトルゲームスタート
			PlaySound(SOUND_LABEL_SE_se_title_rot);			// カラースの回転音
			m_modeSw = SetMode(GAME_START); // 1 == GAME_START
		}
	}
}


void Title::RotRocket(float *posX, float *posY, float addX, float addY, float *RotZ, float valueRot, int time)
{
	static int rocketCount = COUNT_TIMER;

	// ロケットカウントを削っていく
	rocketCount = (int)(rocketCount - time);

	*RotZ += valueRot;
	*RotZ = *RotZ * ACCEL_VALUE;
	if (*RotZ > ROT_MAX) *RotZ = ROT_MAX * 0.5;
	else if (*RotZ < -ROT_MAX) *RotZ = -ROT_MAX * 0.5;

	if (rocketCount <= 0)
	{
		rocketCount = 0;
		*posX += addX;
		if (*posX > 1500.0f) *posX = 1500.0f;
		else if (*posX < -1500.0f) *posX = -1500.0f;

		*posY += addY;
		if (*posY > 1500.0f) *posY = 1500.0f;
		else if (*posY < -1500.0f) *posY = -1500.0f;
	}

	PrintDebugProc("残りロケットカウント%d : \n", rocketCount);

}

void Title::Swaying(int i, float *RotZ)
{
	static int swayCount = 0;
	if (i >= SWAY_VALUE) i = SWAY_VALUE;
	if (i < 2) i = 2;

	// 高速バイブレーション
	if (0 == swayCount % i)
	{
		*RotZ = 0.1314f;
	}
	if (0 != swayCount % i)
	{
		*RotZ = -0.1314f;
	}

	// ここにカウントアップを入れないと下の条件式が破綻する
	swayCount++;

	// カウントアップ条件のリセット
	if (swayCount >= SWAY_VALUE)
	{
		swayCount = 0;
	}
}

void Title::Rot(float *RotZ, float valueRot)
{
	*RotZ += valueRot;

	//PrintDebugProc("回転数%f : \n", *RotZ);
}

void Title::RotAccel(float *RotZ, float valueRot)
{
	*RotZ += valueRot;
	*RotZ = *RotZ * ACCEL_VALUE;
	if (*RotZ > ROT_MAX) *RotZ = ROT_MAX * 0.5;
	else if (*RotZ < -ROT_MAX) *RotZ = -ROT_MAX * 0.5;

	//PrintDebugProc("回転数%f : \n", *RotZ);
}

void Title::UpDown(bool *udFlug, float *posY, float addY)
{

	switch (*udFlug)
	{
	case true:
		*posY -= addY;
		if (*posY < 0.0f)
		{
			*udFlug = false;
		}
		break;

	case false:
		*posY += addY;
		if (*posY > SCREEN_CENTER_Y * 0.5f)
		{
			*udFlug = true;
		}
		break;
	}
}

void Title::Transition(float *posX, float moveValue, float timeSub)
{

	// ロケットカウントを削っていく
	transisionCount = (int)(transisionCount - timeSub);

	if (transisionCount <= 0)
	{
		transisionCount = 0;

		*posX -= moveValue;
		if (*posX <= SCREEN_WIDTH)
		{
			NextScene();

			if (GetFadeOut_EndFlag())
			{
				Init();
			}
		}
	}

	PrintDebugProc("残りトランジションカウント%d : \n", transisionCount);

}

//=============================================================================
// アニメーション切り替え処理（終わり）
//=============================================================================

//=============================================================================
// デバック機構全般(始まり)
//=============================================================================

// デバッグの情報の表示
void Title::DebugPrint(float posX, float posY, float w, float h) // 表示したいデバッグ対象の座標の引数を2つ入れる
{
	PrintDebugProc("デバッグ対象の切り替え : SPACEキー\n");
	PrintDebugProc("デバッグ対象の上移動 : ↑キー , デバッグ対象の下移動 : ↓キー\n");
	PrintDebugProc("デバッグ対象の右移動 : →キー , デバッグ対象の左移動 : ←キー\n");
	PrintDebugProc("デバッグ対象のX方向拡大 : Dキー , デバッグ対象のX方向収縮 : Aキー\n");
	PrintDebugProc("デバッグ対象のY方向拡大 : Wキー , デバッグ対象のY方向収縮 : Sキー\n");
	PrintDebugProc("デバッグ対象の移動量変更ボタン : Cキー\n");
	PrintDebugProc("デバック対象 : title[%d] \n", m_DebugNum);
	PrintDebugProc("デバックポジション : PosX : %f, DebugPosY : %f\n", posX, posY);
	PrintDebugProc("デバックサイズ : SizeWidth : %f, SizeHeight : %f\n", w, h);

}

// デバッグ対象の位置変更
void Title::PosCustom(float *posX, float *posY) // 移動したいデバッグ対象の座標の引数を2つ（ポインタ）入れる
{
	if (GetKeyboardTrigger(DIK_C))
	{
		if (m_DebugSwich)
		{
			m_DebugSwich = false;
		}
		else
		{
			m_DebugSwich = true;
		}
	}

	switch (m_DebugSwich)
	{
	case true:
		// 押されている間、Y上方向に移動
		if (GetKeyboardTrigger(DIK_UP))
		{
			*posY -= DEBUGPOS_ADD;
		}
		// 押されている間、Y下方向に移動
		if (GetKeyboardTrigger(DIK_DOWN))
		{
			*posY += DEBUGPOS_ADD;
		}
		// 押されている間、X右方向に加算
		if (GetKeyboardTrigger(DIK_RIGHT))
		{
			*posX += DEBUGPOS_ADD;
		}
		// 押されている間、X左方向に加算
		if (GetKeyboardTrigger(DIK_LEFT))
		{
			*posX -= DEBUGPOS_ADD;
		}
		break;

	case false:
		// 押されている間、Y上方向に移動
		if (GetKeyboardPress(DIK_UP))
		{
			*posY -= DEBUGPOS_ADD;
		}
		// 押されている間、Y下方向に移動
		if (GetKeyboardPress(DIK_DOWN))
		{
			*posY += DEBUGPOS_ADD;
		}
		// 押されている間、X右方向に加算
		if (GetKeyboardPress(DIK_RIGHT))
		{
			*posX += DEBUGPOS_ADD;
		}
		// 押されている間、X左方向に加算
		if (GetKeyboardPress(DIK_LEFT))
		{
			*posX -= DEBUGPOS_ADD;
		}
	}
}


// デバッグ対象のサイズ変更
void Title::SizeCustom(float *width, float *height) // 移動したいデバッグ対象の座標の引数を2つ（ポインタ）入れる
{

	//if (GetKeyboardTrigger(DIK_C))
	//{
	//	if (m_DebugSwich)
	//	{
	//		m_DebugSwich = false;
	//	}
	//	else
	//	{
	//		m_DebugSwich = true;
	//	}
	//}

	switch (m_DebugSwich)
	{
	case true:
		// 押されている間、Y方向に収縮
		if (GetKeyboardTrigger(DIK_S))
		{
			*height -= DEBUGPOS_ADD;
		}
		// 押されている間、Y方向に拡大
		if (GetKeyboardTrigger(DIK_W))
		{
			*height += DEBUGPOS_ADD;
		}
		// 押されている間、X方向に拡大
		if (GetKeyboardTrigger(DIK_D))
		{
			*width += DEBUGPOS_ADD;
		}
		// 押されている間、X方向に収縮
		if (GetKeyboardTrigger(DIK_A))
		{
			*width -= DEBUGPOS_ADD;
		}
		break;

	case false:
		// 押されている間、Y方向に収縮
		if (GetKeyboardPress(DIK_S))
		{
			*height -= DEBUGPOS_ADD;
		}
		// 押されている間、Y方向に拡大
		if (GetKeyboardPress(DIK_W))
		{
			*height += DEBUGPOS_ADD;
		}
		// 押されている間、X方向に拡大
		if (GetKeyboardPress(DIK_D))
		{
			*width += DEBUGPOS_ADD;
		}
		// 押されている間、X方向に収縮
		if (GetKeyboardPress(DIK_A))
		{
			*width -= DEBUGPOS_ADD;
		}
	}
}

// デバッグ対象の切り替え
int Title::ChangeNum(int *Num) // デバッグ対象の切り替え（デバック番号を対象オブジェクトの配列の引数に入れる事で切り替えを行えるようにする）
{
	int r;

	r = *Num;

	if (GetKeyboardTrigger(DIK_SPACE))
	{
		r += 1;

		if (r > TITLE_MAX - 1)
		{
			r = 0;
		}
	}

	*Num = r;

	return *Num;
}

//=============================================================================
// デバック機構全般(終わり)
//=============================================================================

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitTitle(void)
{

	// BGM再生
	//PlaySound(SOUND_LABEL_BGM_sample000);

	g_Load = TRUE;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitTitle(void)
{
	if (g_Load == FALSE) return;

	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Texture[i])
		{
			g_Texture[i]->Release();
			g_Texture[i] = NULL;
		}
	}

	for (int i = 0; i < TITLE_MAX; i++)
	{
		titleObj[i] = { NULL };
	}


	g_Load = FALSE;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateTitle(void)
{

}


//=============================================================================
// 描画処理
//=============================================================================
void DrawTitle(void)
{
	SetViewPort(TYPE_FULL_SCREEN);

	// ライトを有効化
	SetLightEnable(FALSE);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// マトリクス設定
	SetWorldViewProjection2D();

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	/* ここの順番は自由に入れ替える */

	/* ポール緑を描画 */
	if (titleObj[17].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[6]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColorRotation(g_VertexBuffer, titleObj[17].g_Pos.x, titleObj[17].g_Pos.y, titleObj[17].g_w, titleObj[17].g_h,
			0.0f, 0.0f, 1.0f, 1.0f,
			material.Diffuse, titleObj[17].g_Rot.z);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	/* ポール青を描画 */
	if (titleObj[18].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[7]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColorRotation(g_VertexBuffer, titleObj[18].g_Pos.x, titleObj[18].g_Pos.y, titleObj[18].g_w, titleObj[18].g_h,
			0.0f, 0.0f, 1.0f, 1.0f,
			material.Diffuse, titleObj[18].g_Rot.z);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	/* ポール黄色を描画 */
	if (titleObj[19].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[8]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColorRotation(g_VertexBuffer, titleObj[19].g_Pos.x, titleObj[19].g_Pos.y, titleObj[19].g_w, titleObj[19].g_h,
			0.0f, 0.0f, 1.0f, 1.0f,
			material.Diffuse, titleObj[19].g_Rot.z);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	/* ポールオレンジを描画 */
	if (titleObj[20].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[9]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColorRotation(g_VertexBuffer, titleObj[20].g_Pos.x, titleObj[20].g_Pos.y, titleObj[20].g_w, titleObj[20].g_h,
			0.0f, 0.0f, 1.0f, 1.0f,
			material.Diffuse, titleObj[20].g_Rot.z);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	/* ポール紫を描画 */
	if (titleObj[21].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[10]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColorRotation(g_VertexBuffer, titleObj[21].g_Pos.x, titleObj[21].g_Pos.y, titleObj[21].g_w, titleObj[21].g_h,
			0.0f, 0.0f, 1.0f, 1.0f,
			material.Diffuse, titleObj[21].g_Rot.z);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}


	/* タイトルの枠を描画 */
	if (titleObj[0].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[0]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, titleObj[0].g_Pos.x, titleObj[0].g_Pos.y, titleObj[0].g_w, titleObj[0].g_h, 0.0f, 0.0f, 1.0f, 1.0f);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	// ロールリングを描画
	if (titleObj[1].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColorRotation(g_VertexBuffer, titleObj[1].g_Pos.x, titleObj[1].g_Pos.y, titleObj[1].g_w, titleObj[1].g_h,
			0.0f, 0.0f, 1.0f, 1.0f,
			material.Diffuse, titleObj[1].g_Rot.z);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	/* Exitを描画 */
	if (titleObj[3].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[2]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, titleObj[3].g_Pos.x, titleObj[3].g_Pos.y, titleObj[3].g_w, titleObj[3].g_h, 0.0f, 0.0f, 1.0f, 1.0f);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	// Startを描画
	if (titleObj[4].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[3]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColorRotation(g_VertexBuffer, titleObj[4].g_Pos.x, titleObj[4].g_Pos.y, titleObj[4].g_w, titleObj[4].g_h,
			0.0f, 0.0f, 1.0f, 1.0f,
			material.Diffuse, titleObj[4].g_Rot.z);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	/* カーソルフィンガーを描画 */
	if (titleObj[5].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[4]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, titleObj[5].g_Pos.x, titleObj[5].g_Pos.y, titleObj[5].g_w, titleObj[5].g_h, 0.0f, 0.0f, 1.0f, 1.0f);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	/* StarLeftを描画 */
	if (titleObj[6].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[11]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, titleObj[6].g_Pos.x, titleObj[6].g_Pos.y, titleObj[6].g_w, titleObj[6].g_h, 0.0f, 0.0f, 1.0f, 1.0f);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	/* StarRightを描画 */
	if (titleObj[7].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[12]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, titleObj[7].g_Pos.x, titleObj[7].g_Pos.y, titleObj[7].g_w, titleObj[7].g_h, 0.0f, 0.0f, 1.0f, 1.0f);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	/* StarHeightLを描画 */
	if (titleObj[8].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[13]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, titleObj[8].g_Pos.x, titleObj[8].g_Pos.y, titleObj[8].g_w, titleObj[8].g_h, 0.0f, 0.0f, 1.0f, 1.0f);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	/* StarHeightRを描画 */
	if (titleObj[9].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[13]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, titleObj[9].g_Pos.x, titleObj[9].g_Pos.y, titleObj[9].g_w, titleObj[9].g_h, 0.0f, 0.0f, 1.0f, 1.0f);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	/* 集合を描画 */
	if (titleObj[10].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[15]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColorRotation(g_VertexBuffer, titleObj[10].g_Pos.x, titleObj[10].g_Pos.y, titleObj[10].g_w, titleObj[10].g_h,
			0.0f, 0.0f, 1.0f, 1.0f,
			material.Diffuse, titleObj[10].g_Rot.z);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	/* 赤を描画 */
	if (titleObj[11].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[16]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColorRotation(g_VertexBuffer, titleObj[11].g_Pos.x, titleObj[11].g_Pos.y, titleObj[11].g_w, titleObj[11].g_h,
			0.0f, 0.0f, 1.0f, 1.0f,
			material.Diffuse, titleObj[11].g_Rot.z);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	/* 緑を描画 */
	if (titleObj[12].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[17]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColorRotation(g_VertexBuffer, titleObj[12].g_Pos.x, titleObj[12].g_Pos.y, titleObj[12].g_w, titleObj[12].g_h,
			0.0f, 0.0f, 1.0f, 1.0f,
			material.Diffuse, titleObj[12].g_Rot.z);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	/* 青を描画 */
	if (titleObj[13].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[18]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColorRotation(g_VertexBuffer, titleObj[13].g_Pos.x, titleObj[13].g_Pos.y, titleObj[13].g_w, titleObj[13].g_h,
			0.0f, 0.0f, 1.0f, 1.0f,
			material.Diffuse, titleObj[13].g_Rot.z);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	/* ピンクを描画 */
	if (titleObj[14].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[19]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColorRotation(g_VertexBuffer, titleObj[14].g_Pos.x, titleObj[14].g_Pos.y, titleObj[14].g_w, titleObj[14].g_h,
			0.0f, 0.0f, 1.0f, 1.0f,
			material.Diffuse, titleObj[14].g_Rot.z);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	/* 黄色を描画 */
	if (titleObj[15].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[20]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColorRotation(g_VertexBuffer, titleObj[15].g_Pos.x, titleObj[15].g_Pos.y, titleObj[15].g_w, titleObj[15].g_h,
			0.0f, 0.0f, 1.0f, 1.0f,
			material.Diffuse, titleObj[15].g_Rot.z);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	/* ポール赤を描画 */
	if (titleObj[16].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[5]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColorRotation(g_VertexBuffer, titleObj[16].g_Pos.x, titleObj[16].g_Pos.y, titleObj[16].g_w, titleObj[16].g_h,
			0.0f, 0.0f, 1.0f, 1.0f,
			material.Diffuse, titleObj[16].g_Rot.z);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}


	/* タイトルロゴを描画 */
	if (titleObj[2].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[14]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, titleObj[2].g_Pos.x, titleObj[2].g_Pos.y, titleObj[2].g_w, titleObj[2].g_h, 0.0f, 0.0f, 1.0f, 1.0f);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	/* トランジションを描画 */
	if (titleObj[22].g_Use == TRUE)
	{
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[21]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, titleObj[22].g_Pos.x, titleObj[22].g_Pos.y, titleObj[22].g_w, titleObj[22].g_h, 0.0f, 0.0f, 1.0f, 1.0f);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

}
