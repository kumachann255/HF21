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
#define TEXTURE_MAX		(6)		// テクスチャの数
#define DEBUGPOS_ADD	(1.0f)	// デバッグ用POSの加減算用

//*****************************************************************************
// グローバル変数
static ID3D11Buffer				*g_VertexBuffer = NULL;		// 頂点情報
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

static char *g_TexturName[TEXTURE_MAX] = {
	"data/TEXTURE/title_exit02.png",
	"data/TEXTURE/title_gamestart02.png",
	"data/TEXTURE/title_curtainR01.png",
	"data/TEXTURE/title_curtainL01.png",
	"data/TEXTURE/title_tent.png",
	"data/TEXTURE/title_finger.png",
};

static BOOL						g_Load = FALSE;

// タイトルオブジェクトのインスタンス
s_Title title[TEXTURE_MAX];

/*

title[0] == 上幕
title[1] == EXITバー
title[2] == GAME_STARTバー

*/

//=============================================================================
// コンストラクター ※シーンのコンストラクターに渡してあげる
//=============================================================================
Title::Title(God *god) : Scene(god)
{
	InitTitle();
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

}

//=============================================================================
// 更新処理
//=============================================================================
void Title::Update(void)
{
	UpdateTitle();

	switch (m_modeSw)
	{
	case FIRST_CLOSE:
		FirstClose();
		break;

	case OPEN_CURTAIN:
		OpenCurtain(&title[2].g_Pos.x, &title[3].g_Pos.x);
		break;

	case CHOICE:
		Choice(&title[0].g_Pos.x, &title[1].g_Pos.x, &title[5].g_Pos.x);
		break;

	case GAME_START:
		break;

	case CLOSE_CURTAIN:
		CloseCurtain(&title[2].g_Pos.x, &title[3].g_Pos.x);
		break;

	case EXIT_CLOSE:
		break;
	}


#ifdef _DEBUG	// デバッグ情報を表示する

	// ①デバッグ対象の切り替え
	ChangeNum(&m_DebugNum);

	// ②2D画像位置確認
	DebugPrint(title[m_DebugNum].g_Pos.x, title[m_DebugNum].g_Pos.y);

	// ③2D画像位置変更
	PosCustom(&title[m_DebugNum].g_Pos.x, &title[m_DebugNum].g_Pos.y); // 配列の要素数にデバック番号を入れる事で（デバック対象==デバック番号）とする

	/* ①、②、③の流れが重要！ChangeNum()関数でメンバ変数のm_DebugNumにアクセスしてデバック対象を決めて、それを反映させてから位置確認、位置確認をしている*/

	// シーン切り替えチェック
	NextScene();

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
	// フェードアウトを開始させる
	if (GetKeyboardTrigger(DIK_1))
	{
		SetFade(FADE_OUT);
	}


	// フェードアウトが終わったらシーンを切り替える
	if (GetFadeOut_EndFlag())
	{
		GetGod()->ChangeScene(STAGE_01ID);
	}

}

//=============================================================================
// アニメーション切り替え処理（始まり）
//=============================================================================
int Title::SetMode(int mode)
{
	m_modeSw = mode;

	return m_modeSw;
}

void Title::FirstClose(void)
{
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		m_modeSw = SetMode(OPEN_CURTAIN); // 1 == OPEN_CURTAIN
	}
}

void Title::OpenCurtain(float *curtainR, float *curtainL)
{
	*curtainR += 1.0f;
	if (*curtainR > 1200.0f)
	{
		*curtainR = 1200.0f;
		m_modeSw = SetMode(CHOICE); // 2 == CHOICE
	}

	*curtainL -= 1.0f;
	if (*curtainL < -240.0f)
	{
		*curtainL = -240.0f;
	}
}


void Title::Choice(float *posExitX, float *posGameX, float *posChoiceX)
{
	if (*posChoiceX == *posExitX + 13.0f)
	{
		if (GetKeyboardTrigger(DIK_RIGHT))
		{
			*posChoiceX = *posGameX + 12.0f;
		}
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			m_modeSw = SetMode(CLOSE_CURTAIN); // 4 == CLOSE_CURTAIN
		}
	}

	if (*posChoiceX == *posGameX + 12.0f)
	{
		if (GetKeyboardTrigger(DIK_LEFT))
		{
			*posChoiceX = *posExitX + 13.0f;
		}
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			m_modeSw = SetMode(GAME_START); // 3 == GAME_START
		}
	}
}

void Title::CloseCurtain(float * curtainR, float * curtainL)
{
	*curtainR -= 1.0f;
	if (*curtainR < 720.0f)
	{ // 閉まり切ったらFADEOUT処理
		*curtainR = 720.0f;
		SetFade(FADE_OUT);
	}

	*curtainL += 1.0f;
	if (*curtainL > 240.0f)
	{
		*curtainL = 240.0f;
	}
}

//=============================================================================
// アニメーション切り替え処理（終わり）
//=============================================================================

//=============================================================================
// デバック機構全般(始まり)
//=============================================================================

// デバッグの情報の表示
void Title::DebugPrint(float posX, float posY) // 表示したいデバッグ対象の座標の引数を2つ入れる
{
	PrintDebugProc("デバッグ対象の切り替え : SPACEキー\n");
	PrintDebugProc("デバッグ対象の上移動 : ↑キー , デバッグ対象の下移動 : ↓キー\n");
	PrintDebugProc("デバッグ対象の右移動 : →キー , デバッグ対象の左移動 : ←キー\n");
	PrintDebugProc("デバッグ対象の移動量変更ボタン : Cキー\n");
	PrintDebugProc("デバック対象 : title[%d] \n", m_DebugNum);
	PrintDebugProc("デバックポジション : PosX : %f, DebugPosY : %f\n", posX, posY);
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

// デバッグ対象の切り替え
int Title::ChangeNum(int *Num) // デバッグ対象の切り替え（デバック番号を対象オブジェクトの配列の引数に入れる事で切り替えを行えるようにする）
{
	int r;

	r = *Num;

	if (GetKeyboardTrigger(DIK_SPACE))
	{
		r += 1;

		if (r > TEXTURE_MAX - 1)
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

	// 変数の初期化(EXITバー)
	title[0].g_Use = TRUE;
	title[0].g_w = 128;
	title[0].g_h = 44;
	title[0].g_Pos = XMFLOAT3(220.0f, 330.0f, 0.0f);
	title[0].g_TexNo = 3;
	title[0].alpha = 1.0f;
	title[0].flag_alpha = TRUE;

	// 変数の初期化(GAME_STARTバー)
	title[1].g_Use = TRUE;
	title[1].g_w = 182;
	title[1].g_h = 44;
	title[1].g_Pos = XMFLOAT3(740.0f, 330.0f, 0.0f);
	title[1].g_TexNo = 4;
	title[1].alpha = 1.0f;
	title[1].flag_alpha = TRUE;

	// 変数の初期化(右カーテン)
	title[2].g_Use = TRUE;
	title[2].g_w = 480;
	title[2].g_h = 540;
	title[2].g_Pos = XMFLOAT3(720.0f, SCREEN_CENTER_Y, 0.0f); // 開き止めは1200.0f
	title[2].g_TexNo = 1;
	title[2].alpha = 1.0f;
	title[2].flag_alpha = TRUE;

	// 変数の初期化(左カーテン)
	title[3].g_Use = TRUE;
	title[3].g_w = 480;
	title[3].g_h = 540;
	title[3].g_Pos = XMFLOAT3(240.0f, SCREEN_CENTER_Y, 0.0f); // 開き止めは-240.0f
	title[3].g_TexNo = 2;
	title[3].alpha = 1.0f;
	title[3].flag_alpha = TRUE;

	// 変数の初期化(幕)
	title[4].g_Use = TRUE;
	title[4].g_w = 1024;
	title[4].g_h = 540;
	title[4].g_Pos = XMFLOAT3(480.0f, 260.0f, 0.0f);
	title[4].g_TexNo = 0;
	title[4].alpha = 1.0f;
	title[4].flag_alpha = TRUE;

	// 変数の初期化(カーソル)
	title[5].g_Use = TRUE;
	title[5].g_w = 110;
	title[5].g_h = 90;
	title[5].g_Pos = title[0].g_Pos;
	title[5].g_Pos.x += 13.0f; // 微調整EXITPos.X
	title[5].g_Pos.y += 40.0f; // 微調整EXITPos.Y
	//title[5].g_Pos.x += 12.0f; // 微調整GAME_STARTPos.X
	//title[5].g_Pos.y += 40.0f; // 微調整GAME_STARTPos.Y
	title[5].g_TexNo = 5;
	title[5].alpha = 1.0f;
	title[5].flag_alpha = TRUE;


	//// 変数の初期化(EXITバー)
	//maku.g_Use = TRUE;
	//maku.g_w = 960;
	//maku.g_h = 128;
	//maku.g_Pos = XMFLOAT3(480.0f, 64.0f, 0.0f);
	//maku.g_TexNo = 0;

	//maku.alpha = 1.0f;
	//maku.flag_alpha = TRUE;

	//// 変数の初期化(GAME_STARTバー)
	//maku.g_Use = TRUE;
	//maku.g_w = 960;
	//maku.g_h = 128;
	//maku.g_Pos = XMFLOAT3(480.0f, 64.0f, 0.0f);
	//maku.g_TexNo = 0;

	//maku.alpha = 1.0f;
	//maku.flag_alpha = TRUE;

	//// 変数の初期化(カーソル)
	//maku.g_Use = TRUE;
	//maku.g_w = 960;
	//maku.g_h = 128;
	//maku.g_Pos = XMFLOAT3(480.0f, 64.0f, 0.0f);
	//maku.g_TexNo = 0;

	//maku.alpha = 1.0f;
	//maku.flag_alpha = TRUE;


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

	// タイトルの背景を描画
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[i]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, title[i].g_Pos.x, title[i].g_Pos.y, title[i].g_w, title[i].g_h, 0.0f, 0.0f, 1.0f, 1.0f);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

}


