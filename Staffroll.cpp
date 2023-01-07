//=============================================================================
//
// スタッフロール画面処理 [Staffroll.cpp]
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
#include "Staffroll.h"
#include "debugproc.h"
#include "texManager.h"
#include "QuestBoardManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_MAX				(14)		// テクスチャの数
#define DEBUGPOS_PRESS_ADD		(5.0f)	// デバッグ用POSの加減算用PRESS
#define DEBUGPOS_TRIGGER_ADD	(1.0f)	// デバッグ用POSの加減算用TRIGGER
#define SCROLL_VALUE			(2.0f)	// スクロール用増減値

//*****************************************************************************
// グローバル変数
static ID3D11Buffer				*g_VertexBuffer = NULL;		// 頂点情報
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

static char *g_TexturName2[TEXTURE_MAX] = {
	"data/TEXTURE/STAFFROLL/endScroll.png",
	"data/TEXTURE/STAFFROLL/resultBG.png",
	"data/TEXTURE/STAFFROLL/seika.png",
	"data/TEXTURE/STAFFROLL/goldBar.png",
	"data/TEXTURE/STAFFROLL/silverBar.png",
	"data/TEXTURE/STAFFROLL/bronzeBar.png",
	"data/TEXTURE/STAFFROLL/blueBar.png",
	"data/TEXTURE/STAFFROLL/greenBar.png",
	"data/TEXTURE/STAFFROLL/goldRunk.png",
	"data/TEXTURE/STAFFROLL/silverRunk.png",
	"data/TEXTURE/STAFFROLL/bronzeRunk.png",
	"data/TEXTURE/STAFFROLL/blueRunk.png",
	"data/TEXTURE/STAFFROLL/greenRunk.png",
	"data/TEXTURE/STAFFROLL/factcheck_mark.png"

};

static BOOL						g_Load = FALSE;

// スタッフロールオブジェクトのインスタンス
s_StaffRoll staffRoll[STAFFROLL_MAX];
// チェックマークオブジェクトのインスタンス
s_Check check[CHECK_MAX];


//=============================================================================
// コンストラクター ※シーンのコンストラクターに渡してあげる
//=============================================================================
StaffRoll::StaffRoll(God *god) : Scene(god)
{
	InitStaffRoll();
}

//=============================================================================
// デストラクター
//=============================================================================
StaffRoll::~StaffRoll()
{
	UninitStaffRoll();
}

//=============================================================================
// 初期化処理
//=============================================================================
void StaffRoll::Init(void)
{
	m_Mode = RESULT;
	m_ScrollSw = false;	// スクロール開始用SW
	m_DebugSwich = true;	// デバッグモード切り替え用SW
	m_DebugNum = 0;			// デバッグ用変数
	m_StopTime = 0;
	m_isTelop = false;		// テロップを出したかどうか
	m_isWait = 0;
}

//=============================================================================
// 更新処理
//=============================================================================
void StaffRoll::Update(void)
{
	if (GetKeyboardTrigger(DIK_1))
	{
		SetFade(FADE_OUT, TITLE_ID);
	}


	// ノルマのテロップ表示
	if (!m_isTelop)
	{
		m_isTelop = true;
		GetGod()->GetTexManager()->GetUIManager()->SetTexture(
			result_clear, texType_cutIn_left, XMFLOAT3(600.0f, 400.0f, 0.0f), 4);

		GetGod()->GetTexManager()->GetUIManager()->SetTexture(
			result_false, texType_cutIn_left, XMFLOAT3(600.0f, 400.0f, 0.0f), 4);
	}

	switch (m_Mode)
	{
	case RESULT:
		// 引数部分(本来は最終的なm_IconNumを入れたい)
		int sample_iconNum;
		sample_iconNum = GetPoint();

		if (sample_iconNum >= 15)
		{
			sample_iconNum = 15;
		}

		CheckIcon(&sample_iconNum);
		break;

	case GREEN:
		CheckMark(&check[0].checkTime, &check[0].g_Use);


		if (check[0].checkTime == 0)
		{
			//開始
			Slide(&staffRoll[7].g_Pos.x);
		}
		break;

	case BLUE:
		for (int i = 0; i < 2; i++)
		{
			CheckMark(&check[i].checkTime, &check[i].g_Use);
			// ケツのチェックに合わせる
			if (check[1].checkTime == 0)
			{
				Slide(&staffRoll[6].g_Pos.x);
			}
		}
		break;

	case BRONSE:
		for (int i = 0; i < 3; i++)
		{
			CheckMark(&check[i].checkTime, &check[i].g_Use);
			// ケツのチェックに合わせる
			if (check[2].checkTime == 0)
			{
				Slide(&staffRoll[5].g_Pos.x);
			}
		}

		break;

	case SILVER:
		for (int i = 0; i < 4; i++)
		{
			CheckMark(&check[i].checkTime, &check[i].g_Use);
			// ケツのチェックに合わせる
			if (check[3].checkTime == 0)
			{
				Slide(&staffRoll[4].g_Pos.x);
			}
		}

		break;

	case GOLD:
		for (int i = 0; i < 5; i++)
		{
			CheckMark(&check[i].checkTime, &check[i].g_Use);
			// ケツのチェックに合わせる
			if (check[4].checkTime == 0)
			{
				Slide(&staffRoll[3].g_Pos.x);
			}
		}

		break;

	case ENDROLL:
		switch (m_ScrollSw)
		{
		case true:
			Scroll(&staffRoll[0].g_Pos.y);
			break;

		case false:
			Stop();
		}
		break;
	}

	GetGod()->GetTexManager()->Update();

#ifdef _DEBUG	// デバッグ情報を表示する


	// ①デバッグ対象の切り替え
	ChangeNum(&m_DebugNum);

	// ②2D画像位置確認
	DebugPrint(staffRoll[m_DebugNum].g_Pos.x, staffRoll[m_DebugNum].g_Pos.y, staffRoll[m_DebugNum].g_w, staffRoll[m_DebugNum].g_h);

	// ③2D画像位置変更
	PosCustom(&staffRoll[m_DebugNum].g_Pos.x, &staffRoll[m_DebugNum].g_Pos.y); // 配列の要素数にデバック番号を入れる事で（デバック対象==デバック番号）とする

	// ④2D画像サイズ変更
	SizeCustom(&staffRoll[m_DebugNum].g_w, &staffRoll[m_DebugNum].g_h); // 配列の要素数にデバック番号を入れる事で（デバック対象==デバック番号）とする

	/* この流れが重要！ChangeNum()関数でメンバ変数のm_DebugNumにアクセスしてデバック対象を決めて、それを反映させてから位置確認、位置確認をしている*/

	// シーン切り替えチェック
	NextScene();

#endif


}

//=============================================================================
// 描画処理
//=============================================================================
void StaffRoll::Draw(void)
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

	switch (m_Mode)
	{
	case RESULT:
		/* 背景 */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[1].g_Pos.x, staffRoll[1].g_Pos.y, staffRoll[1].g_w, staffRoll[1].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* 成果Bar */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[2]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[2].g_Pos.x, staffRoll[2].g_Pos.y, staffRoll[2].g_w, staffRoll[2].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクGold */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[8]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[8].g_Pos.x, staffRoll[8].g_Pos.y, staffRoll[8].g_w, staffRoll[8].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクSilver */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[9]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[9].g_Pos.x, staffRoll[9].g_Pos.y, staffRoll[9].g_w, staffRoll[9].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクBlonze */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[10]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[10].g_Pos.x, staffRoll[10].g_Pos.y, staffRoll[10].g_w, staffRoll[10].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクBlue */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[11]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[11].g_Pos.x, staffRoll[11].g_Pos.y, staffRoll[11].g_w, staffRoll[11].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクGreen */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[12]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[12].g_Pos.x, staffRoll[12].g_Pos.y, staffRoll[12].g_w, staffRoll[12].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		break;

	case GREEN:
		/* 背景 */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[1].g_Pos.x, staffRoll[1].g_Pos.y, staffRoll[1].g_w, staffRoll[1].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* 成果Bar */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[2]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[2].g_Pos.x, staffRoll[2].g_Pos.y, staffRoll[2].g_w, staffRoll[2].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクGold */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[8]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[8].g_Pos.x, staffRoll[8].g_Pos.y, staffRoll[8].g_w, staffRoll[8].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクSilver */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[9]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[9].g_Pos.x, staffRoll[9].g_Pos.y, staffRoll[9].g_w, staffRoll[9].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクBlonze */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[10]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[10].g_Pos.x, staffRoll[10].g_Pos.y, staffRoll[10].g_w, staffRoll[10].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクBlue */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[11]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[11].g_Pos.x, staffRoll[11].g_Pos.y, staffRoll[11].g_w, staffRoll[11].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクGreen */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[12]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[12].g_Pos.x, staffRoll[12].g_Pos.y, staffRoll[12].g_w, staffRoll[12].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		if (check[0].g_Use == TRUE)
		{
			/* チェックマーク */
			// テクスチャ設定
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[13]);
			// １枚のポリゴンの頂点とテクスチャ座標を設定
			SetSprite(g_VertexBuffer, check[0].g_Pos.x, check[0].g_Pos.y, check[0].g_w, check[0].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
			// ポリゴン描画
			GetDeviceContext()->Draw(4, 0);
		}

		/* ランクBar */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[7]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[7].g_Pos.x, staffRoll[7].g_Pos.y, staffRoll[7].g_w, staffRoll[7].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		break;

	case BLUE:
		/* 背景 */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[1].g_Pos.x, staffRoll[1].g_Pos.y, staffRoll[1].g_w, staffRoll[1].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* 成果Bar */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[2]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[2].g_Pos.x, staffRoll[2].g_Pos.y, staffRoll[2].g_w, staffRoll[2].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクGold */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[8]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[8].g_Pos.x, staffRoll[8].g_Pos.y, staffRoll[8].g_w, staffRoll[8].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクSilver */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[9]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[9].g_Pos.x, staffRoll[9].g_Pos.y, staffRoll[9].g_w, staffRoll[9].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクBlonze */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[10]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[10].g_Pos.x, staffRoll[10].g_Pos.y, staffRoll[10].g_w, staffRoll[10].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクBlue */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[11]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[11].g_Pos.x, staffRoll[11].g_Pos.y, staffRoll[11].g_w, staffRoll[11].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクGreen */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[12]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[12].g_Pos.x, staffRoll[12].g_Pos.y, staffRoll[12].g_w, staffRoll[12].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		for (int i = 0; i < 2; i++)
		{
			if (check[i].g_Use == TRUE)
			{
				/* チェックマーク */
				// テクスチャ設定
				GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[13]);
				// １枚のポリゴンの頂点とテクスチャ座標を設定
				SetSprite(g_VertexBuffer, check[i].g_Pos.x, check[i].g_Pos.y, check[i].g_w, check[i].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
				// ポリゴン描画
				GetDeviceContext()->Draw(4, 0);
			}
		}

		/* ランクBar */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[6]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[6].g_Pos.x, staffRoll[6].g_Pos.y, staffRoll[6].g_w, staffRoll[6].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		break;

	case BRONSE:
		/* 背景 */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[1].g_Pos.x, staffRoll[1].g_Pos.y, staffRoll[1].g_w, staffRoll[1].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* 成果Bar */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[2]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[2].g_Pos.x, staffRoll[2].g_Pos.y, staffRoll[2].g_w, staffRoll[2].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクGold */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[8]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[8].g_Pos.x, staffRoll[8].g_Pos.y, staffRoll[8].g_w, staffRoll[8].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクSilver */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[9]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[9].g_Pos.x, staffRoll[9].g_Pos.y, staffRoll[9].g_w, staffRoll[9].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクBlonze */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[10]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[10].g_Pos.x, staffRoll[10].g_Pos.y, staffRoll[10].g_w, staffRoll[10].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクBlue */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[11]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[11].g_Pos.x, staffRoll[11].g_Pos.y, staffRoll[11].g_w, staffRoll[11].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクGreen */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[12]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[12].g_Pos.x, staffRoll[12].g_Pos.y, staffRoll[12].g_w, staffRoll[12].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		for (int i = 0; i < 3; i++)
		{
			if (check[i].g_Use == TRUE)
			{
				/* チェックマーク */
				// テクスチャ設定
				GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[13]);
				// １枚のポリゴンの頂点とテクスチャ座標を設定
				SetSprite(g_VertexBuffer, check[i].g_Pos.x, check[i].g_Pos.y, check[i].g_w, check[i].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
				// ポリゴン描画
				GetDeviceContext()->Draw(4, 0);
			}
		}

		/* ランクBar */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[5]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[5].g_Pos.x, staffRoll[5].g_Pos.y, staffRoll[5].g_w, staffRoll[5].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);


		break;

	case SILVER:
		/* 背景 */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[1].g_Pos.x, staffRoll[1].g_Pos.y, staffRoll[1].g_w, staffRoll[1].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* 成果Bar */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[2]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[2].g_Pos.x, staffRoll[2].g_Pos.y, staffRoll[2].g_w, staffRoll[2].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクGold */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[8]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[8].g_Pos.x, staffRoll[8].g_Pos.y, staffRoll[8].g_w, staffRoll[8].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクSilver */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[9]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[9].g_Pos.x, staffRoll[9].g_Pos.y, staffRoll[9].g_w, staffRoll[9].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクBlonze */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[10]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[10].g_Pos.x, staffRoll[10].g_Pos.y, staffRoll[10].g_w, staffRoll[10].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクBlue */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[11]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[11].g_Pos.x, staffRoll[11].g_Pos.y, staffRoll[11].g_w, staffRoll[11].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクGreen */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[12]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[12].g_Pos.x, staffRoll[12].g_Pos.y, staffRoll[12].g_w, staffRoll[12].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		for (int i = 0; i < 4; i++)
		{
			if (check[i].g_Use == TRUE)
			{
				/* チェックマーク */
				// テクスチャ設定
				GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[13]);
				// １枚のポリゴンの頂点とテクスチャ座標を設定
				SetSprite(g_VertexBuffer, check[i].g_Pos.x, check[i].g_Pos.y, check[i].g_w, check[i].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
				// ポリゴン描画
				GetDeviceContext()->Draw(4, 0);
			}
		}

		/* ランクBar */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[4]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[4].g_Pos.x, staffRoll[4].g_Pos.y, staffRoll[4].g_w, staffRoll[4].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		break;

	case GOLD:
		/* 背景 */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[1].g_Pos.x, staffRoll[1].g_Pos.y, staffRoll[1].g_w, staffRoll[1].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* 成果Bar */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[2]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[2].g_Pos.x, staffRoll[2].g_Pos.y, staffRoll[2].g_w, staffRoll[2].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクGold */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[8]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[8].g_Pos.x, staffRoll[8].g_Pos.y, staffRoll[8].g_w, staffRoll[8].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクSilver */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[9]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[9].g_Pos.x, staffRoll[9].g_Pos.y, staffRoll[9].g_w, staffRoll[9].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクBlonze */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[10]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[10].g_Pos.x, staffRoll[10].g_Pos.y, staffRoll[10].g_w, staffRoll[10].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクBlue */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[11]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[11].g_Pos.x, staffRoll[11].g_Pos.y, staffRoll[11].g_w, staffRoll[11].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		/* ランクGreen */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[12]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[12].g_Pos.x, staffRoll[12].g_Pos.y, staffRoll[12].g_w, staffRoll[12].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		for (int i = 0; i < 5; i++)
		{
			if (check[i].g_Use == TRUE)
			{
				/* チェックマーク */
				// テクスチャ設定
				GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[13]);
				// １枚のポリゴンの頂点とテクスチャ座標を設定
				SetSprite(g_VertexBuffer, check[i].g_Pos.x, check[i].g_Pos.y, check[i].g_w, check[i].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
				// ポリゴン描画
				GetDeviceContext()->Draw(4, 0);
			}
		}

		/* ランクBar */
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[3]);
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[3].g_Pos.x, staffRoll[3].g_Pos.y, staffRoll[3].g_w, staffRoll[3].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		GetGod()->GetTexManager()->Draw();

		break;

	case ENDROLL:
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[0]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, staffRoll[0].g_Pos.x, staffRoll[0].g_Pos.y, staffRoll[0].g_w, staffRoll[0].g_h, 0.0f, 0.0f, 1.0f, 1.0f);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
		break;
	}
}

//=============================================================================
// シーン遷移処理
//=============================================================================
void StaffRoll::NextScene(void)
{
	// プレゼン発表用
	// #ifdef _DEBUG	// デバッグ情報を表示する
		// フェードアウトを開始させる
	if (GetKeyboardTrigger(DIK_1) || IsButtonTriggered(0, BUTTON_START))
	{
		SetFade(FADE_OUT, TITLE_ID);
	}
	// #endif
		
	//// フェードアウトが終わったら
	//if (GetFadeOut_EndFlag())
	//{

	//}
}

void StaffRoll::Stop(void)
{
	m_StopTime++;
	if (m_StopTime == MAX_STOPTIME)
	{
		m_ScrollSw = true;
		m_StopTime = 0;
	}
}

void StaffRoll::Scroll(float *posY)
{
	*posY -= SCROLL_VALUE;
	if (*posY < -1460.0f)
	{
		*posY = -1460.0f;
		SetFade(FADE_OUT, TITLE_ID);
	}
}

//=============================================================================
// デバック機構全般(始まり)
//=============================================================================

int StaffRoll::ChangeNum(int * Num)
{
	int r;

	r = *Num;

	if (GetKeyboardTrigger(DIK_SPACE))
	{
		r += 1;

		if (r > STAFFROLL_MAX - 1)
		{
			r = 0;
		}
	}

	*Num = r;

	return *Num;
}

// デバッグの情報の表示
void StaffRoll::DebugPrint(float posX, float posY, float w, float h) // 表示したいデバッグ対象の座標の引数を2つ入れる
{
	PrintDebugProc("checkTime : %d\n", check[0].checkTime);
	PrintDebugProc("m_Mode : %d\n", m_Mode);
	PrintDebugProc("デバッグ対象の切り替え : SPACEキー\n");
	PrintDebugProc("デバッグ対象の上移動 : ↑キー , デバッグ対象の下移動 : ↓キー\n");
	PrintDebugProc("デバッグ対象の右移動 : →キー , デバッグ対象の左移動 : ←キー\n");
	PrintDebugProc("デバッグ対象のX方向拡大 : Dキー , デバッグ対象のX方向収縮 : Aキー\n");
	PrintDebugProc("デバッグ対象のY方向拡大 : Wキー , デバッグ対象のY方向収縮 : Sキー\n");
	PrintDebugProc("デバッグ対象の移動量変更ボタン : Cキー\n");
	PrintDebugProc("デバック対象 : staffRoll[%d] \n", m_DebugNum);
	PrintDebugProc("デバックポジション : PosX : %f, DebugPosY : %f\n", posX, posY);
	PrintDebugProc("デバックサイズ : SizeWidth : %f, SizeHeight : %f\n", w, h);
}

// デバッグ対象の位置変更
void StaffRoll::PosCustom(float *posX, float *posY) // 移動したいデバッグ対象の座標の引数を2つ（ポインタ）入れる
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
			*posY -= DEBUGPOS_TRIGGER_ADD;
		}
		// 押されている間、Y下方向に移動
		if (GetKeyboardTrigger(DIK_DOWN))
		{
			*posY += DEBUGPOS_TRIGGER_ADD;
		}
		// 押されている間、X右方向に加算
		if (GetKeyboardTrigger(DIK_RIGHT))
		{
			*posX += DEBUGPOS_TRIGGER_ADD;
		}
		// 押されている間、X左方向に加算
		if (GetKeyboardTrigger(DIK_LEFT))
		{
			*posX -= DEBUGPOS_TRIGGER_ADD;
		}
		break;

	case false:
		// 押されている間、Y上方向に移動
		if (GetKeyboardPress(DIK_UP))
		{
			*posY -= DEBUGPOS_PRESS_ADD;
		}
		// 押されている間、Y下方向に移動
		if (GetKeyboardPress(DIK_DOWN))
		{
			*posY += DEBUGPOS_PRESS_ADD;
		}
		// 押されている間、X右方向に加算
		if (GetKeyboardPress(DIK_RIGHT))
		{
			*posX += DEBUGPOS_PRESS_ADD;
		}
		// 押されている間、X左方向に加算
		if (GetKeyboardPress(DIK_LEFT))
		{
			*posX -= DEBUGPOS_TRIGGER_ADD;
		}
	}
}

void StaffRoll::SizeCustom(float *width, float *height)
{
	switch (m_DebugSwich)
	{
	case true:
		// 押されている間、Y方向に収縮
		if (GetKeyboardTrigger(DIK_S))
		{
			*height -= DEBUGPOS_TRIGGER_ADD;
		}
		// 押されている間、Y方向に拡大
		if (GetKeyboardTrigger(DIK_W))
		{
			*height += DEBUGPOS_TRIGGER_ADD;
		}
		// 押されている間、X方向に拡大
		if (GetKeyboardTrigger(DIK_D))
		{
			*width += DEBUGPOS_TRIGGER_ADD;
		}
		// 押されている間、X方向に収縮
		if (GetKeyboardTrigger(DIK_A))
		{
			*width -= DEBUGPOS_TRIGGER_ADD;
		}
		break;

	case false:
		// 押されている間、Y方向に収縮
		if (GetKeyboardPress(DIK_S))
		{
			*height -= DEBUGPOS_PRESS_ADD;
		}
		// 押されている間、Y方向に拡大
		if (GetKeyboardPress(DIK_W))
		{
			*height += DEBUGPOS_PRESS_ADD;
		}
		// 押されている間、X方向に拡大
		if (GetKeyboardPress(DIK_D))
		{
			*width += DEBUGPOS_PRESS_ADD;
		}
		// 押されている間、X方向に収縮
		if (GetKeyboardPress(DIK_A))
		{
			*width -= DEBUGPOS_PRESS_ADD;
		}
	}

}

void StaffRoll::CheckIcon(int *m_icon)
{
	switch (*m_icon)
	{
	case 0:
		SetRank(GREEN);
		break;
	case 1:
		SetRank(GREEN);
		break;
	case 2:
		SetRank(GREEN);
		break;
	case 3:
		SetRank(GREEN);
		break;
	case 4:
		SetRank(GREEN);
		break;
	case 5:
		SetRank(GREEN);
		break;
	case 6:
		SetRank(BLUE);
		break;
	case 7:
		SetRank(BLUE);
		break;
	case 8:
		SetRank(BLUE);
		break;
	case 9:
		SetRank(BLUE);
		break;
	case 10:
		SetRank(BRONSE);
		break;
	case 11:
		SetRank(BRONSE);
		break;
	case 12:
		SetRank(BRONSE);
		break;
	case 13:
		SetRank(SILVER);
		break;
	case 14:
		SetRank(SILVER);
		break;
	case 15:
		SetRank(GOLD);
		break;
	}
}

void StaffRoll::CheckMark(int *time, BOOL *use)
{
	if (*time > 0)
	{
		*time = *time - 1;
		if (*time == 0)
		{
			*use = TRUE;
			*time = 0;
		}
	}
}

void StaffRoll::Slide(float *posX)
{
	*posX -= SCROLL_VALUE;
	if (*posX < SCREEN_CENTER_X)
	{
		*posX = SCREEN_CENTER_X;
		m_isWait++;
		
		if (m_isWait > 180)
		{
			m_Mode = ENDROLL;
		}
	}
}

void StaffRoll::SetRank(int mode)
{
	m_Mode = mode;
}


//=============================================================================
// デバック機構全般(終わり)
//=============================================================================

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitStaffRoll(void)
{
	ID3D11Device *pDevice = GetDevice();

	//テクスチャ生成
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TexturName2[i],
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

	// 変数の初期化(SCROLL)
	staffRoll[0].g_Use = TRUE;
	staffRoll[0].g_w = SCREEN_WIDTH;
	staffRoll[0].g_h = 4000;
	staffRoll[0].g_Pos = XMFLOAT3(SCREEN_CENTER_X, 2000.0f, 0.0f); // ENDは-1460.0f
	staffRoll[0].g_TexNo = 0;

	// 変数の初期化（背景）
	staffRoll[1].g_Use = TRUE;
	staffRoll[1].g_w = 980;
	staffRoll[1].g_h = 555;
	staffRoll[1].g_Pos = XMFLOAT3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	staffRoll[1].g_TexNo = 1;

	// 変数の初期化（成果Bar）
	staffRoll[2].g_Use = TRUE;
	staffRoll[2].g_w = 310;
	staffRoll[2].g_h = 125;
	staffRoll[2].g_Pos = XMFLOAT3(770.0f, 90.0f, 0.0f);
	staffRoll[2].g_TexNo = 2;

	// 変数の初期化（ランクBarゴールド）
	staffRoll[3].g_Use = TRUE;
	staffRoll[3].g_w = 510;
	staffRoll[3].g_h = 130;
	staffRoll[3].g_Pos = XMFLOAT3(1500.0f, 235.0f, 0.0f);
	staffRoll[3].g_TexNo = 3;

	// 変数の初期化（ランクBarシルバー）
	staffRoll[4].g_Use = TRUE;
	staffRoll[4].g_w = 510;
	staffRoll[4].g_h = 130;
	staffRoll[4].g_Pos = XMFLOAT3(1500.0f, 235.0f, 0.0f);
	staffRoll[4].g_TexNo = 4;

	// 変数の初期化（ランクBarブロンズ）
	staffRoll[5].g_Use = TRUE;
	staffRoll[5].g_w = 510;
	staffRoll[5].g_h = 130;
	staffRoll[5].g_Pos = XMFLOAT3(1500.0f, 235.0f, 0.0f);
	staffRoll[5].g_TexNo = 5;

	// 変数の初期化（ランクBarブルー）
	staffRoll[6].g_Use = TRUE;
	staffRoll[6].g_w = 510;
	staffRoll[6].g_h = 130;
	staffRoll[6].g_Pos = XMFLOAT3(1500.0f, 235.0f, 0.0f);
	staffRoll[6].g_TexNo = 6;

	// 変数の初期化（ランクBarグリーン）
	staffRoll[7].g_Use = TRUE;
	staffRoll[7].g_w = 510;
	staffRoll[7].g_h = 130;
	staffRoll[7].g_Pos = XMFLOAT3(1500.0f, 235.0f, 0.0f);
	staffRoll[7].g_TexNo = 7;

	// 変数の初期化（ゴールドRunk）
	staffRoll[8].g_Use = TRUE;
	staffRoll[8].g_w = 180;
	staffRoll[8].g_h = 130;
	staffRoll[8].g_Pos = XMFLOAT3(810.0f, 445.0f, 0.0f);
	staffRoll[8].g_TexNo = 8;

	// 変数の初期化（シルバーRunk）
	staffRoll[9].g_Use = TRUE;
	staffRoll[9].g_w = 180;
	staffRoll[9].g_h = 130;
	staffRoll[9].g_Pos = XMFLOAT3(630.0f, 385.0f, 0.0f);
	staffRoll[9].g_TexNo = 9;

	// 変数の初期化（ブロンズRunk）
	staffRoll[10].g_Use = TRUE;
	staffRoll[10].g_w = 180;
	staffRoll[10].g_h = 130;
	staffRoll[10].g_Pos = XMFLOAT3(SCREEN_CENTER_X, 465.0f, 0.0f);
	staffRoll[10].g_TexNo = 10;

	// 変数の初期化（ブルーRunk）
	staffRoll[11].g_Use = TRUE;
	staffRoll[11].g_w = 180;
	staffRoll[11].g_h = 130;
	staffRoll[11].g_Pos = XMFLOAT3(330.0f, 385.0f, 0.0f);
	staffRoll[11].g_TexNo = 11;

	// 変数の初期化（グリーンRunk）
	staffRoll[12].g_Use = TRUE;
	staffRoll[12].g_w = 180;
	staffRoll[12].g_h = 130;
	staffRoll[12].g_Pos = XMFLOAT3(150.0f, 445.0f, 0.0f);
	staffRoll[12].g_TexNo = 12;

	// 変数の初期化（チェックマーク）
	for (int i = 0; i < CHECK_MAX; i++)
	{
		check[i].g_Use = FALSE;
		check[i].g_w = 180;
		check[i].g_h = 130;
		check[i].g_TexNo = 13;
	}

	check[0].g_Pos = XMFLOAT3(150.0f, 445.0f, 0.0f);
	check[1].g_Pos = XMFLOAT3(330.0f, 385.0f, 0.0f);
	check[2].g_Pos = XMFLOAT3(SCREEN_CENTER_X, 465.0f, 0.0f);
	check[3].g_Pos = XMFLOAT3(630.0f, 385.0f, 0.0f);
	check[4].g_Pos = XMFLOAT3(810.0f, 445.0f, 0.0f);

	check[0].checkTime = 75;
	check[1].checkTime = 150;
	check[2].checkTime = 225;
	check[3].checkTime = 300;
	check[4].checkTime = 375;

	// BGM再生
	//PlaySound(SOUND_LABEL_BGM_sample000);

	g_Load = TRUE;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitStaffRoll(void)
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