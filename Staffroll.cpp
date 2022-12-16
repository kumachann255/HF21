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

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_MAX				(1)		// テクスチャの数
#define DEBUGPOS_PRESS_ADD		(5.0f)	// デバッグ用POSの加減算用PRESS
#define DEBUGPOS_TRIGGER_ADD	(1.0f)	// デバッグ用POSの加減算用TRIGGER
#define SCROLL_VALUE			(2.5f)	// スクロール用増減値

//*****************************************************************************
// グローバル変数
static ID3D11Buffer				*g_VertexBuffer = NULL;		// 頂点情報
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

static char *g_TexturName[TEXTURE_MAX] = {
	"data/TEXTURE/scroll.png",
};

static BOOL						g_Load = FALSE;

// スタッフロールオブジェクトのインスタンス
s_StaffRoll staffRoll;

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

}

//=============================================================================
// 更新処理
//=============================================================================
void StaffRoll::Update(void)
{
	UpdateStaffRoll();
	Scroll(&staffRoll.g_Pos.y);

#ifdef _DEBUG	// デバッグ情報を表示する


	// 2D画像位置確認
	DebugPrint(staffRoll.g_Pos.y);

	// 2D画像位置変更
	PosCustom(&staffRoll.g_Pos.y); // 配列の要素数にデバック番号を入れる事で（デバック対象==デバック番号）とする

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
	DrawStaffRoll();
}

//=============================================================================
// シーン遷移処理
//=============================================================================
void StaffRoll::NextScene(void)
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

void StaffRoll::Scroll(float *posY)
{
	*posY -= SCROLL_VALUE;
	if (*posY < -1460.0f)
	{
		*posY = -1460.0f;
		SetFade(FADE_OUT);
	}
}

//=============================================================================
// デバック機構全般(始まり)
//=============================================================================

// デバッグの情報の表示
void StaffRoll::DebugPrint(float posY) // 表示したいデバッグ対象の座標の引数を2つ入れる
{
	PrintDebugProc("デバッグ対象の上移動 : ↑キー , デバッグ対象の下移動 : ↓キー\n");
	PrintDebugProc("デバックポジション DebugPosY : %f\n", posY);
}

// デバッグ対象の位置変更
void StaffRoll::PosCustom(float *posY) // 移動したいデバッグ対象の座標の引数を2つ（ポインタ）入れる
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
		break;
	}
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
	staffRoll.g_Use = TRUE;
	staffRoll.g_w = SCREEN_WIDTH;
	staffRoll.g_h = 4000;
	staffRoll.g_Pos = XMFLOAT3(SCREEN_CENTER_X, 2000.0f, 0.0f); // ENDは-1460.0f
	staffRoll.g_TexNo = 0;

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

//=============================================================================
// 更新処理
//=============================================================================
void UpdateStaffRoll(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawStaffRoll(void)
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

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[0]);

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSprite(g_VertexBuffer, staffRoll.g_Pos.x, staffRoll.g_Pos.y, staffRoll.g_w, staffRoll.g_h, 0.0f, 0.0f, 1.0f, 1.0f);

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);

}