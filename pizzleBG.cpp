//=============================================================================
//
// パズルのBG処理 [puzzleBG.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "sprite.h"
#include "puzzleBG.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_WIDTH				(R_SCREEN_WIDTH)	// 背景サイズ
#define TEXTURE_HEIGHT				(R_SCREEN_HEIGHT)	// 
#define TEXTURE_MAX					(1)				// テクスチャの数

#define TEXTURE_WIDTH_LOGO			(480)			// ロゴサイズ
#define TEXTURE_HEIGHT_LOGO			(80)			// 

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;		// 頂点情報
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

static char *g_TexturName[TEXTURE_MAX] = {
	"data/TEXTURE/field003.jpg",
};


static float	alpha;
static BOOL	flag_alpha;
static PuzzleBG puzzleBG;


static BOOL						g_Load = FALSE;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPuzzleBG(void)
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


	// 変数の初期化

	alpha = 1.0f;
	flag_alpha = TRUE;

	g_Load = TRUE;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPuzzleBG(void)
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
void UpdatePuzzleBG(void)
{
	if (GetKeyboardTrigger(DIK_L))
	{
		if (puzzleBG.GetUse()) puzzleBG.SetUse(false);
		else puzzleBG.SetUse(true);
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPuzzleBG(void)
{
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
	if(puzzleBG.GetUse())
	{
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[0]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, puzzleBG.m_Pos.x, puzzleBG.m_Pos.y, puzzleBG.m_w, puzzleBG.m_h, 0.0f, 0.0f, 1.0f, 1.0f);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	//// タイトルのロゴを描画
	//{
	//	// テクスチャ設定
	//	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);

	//	// １枚のポリゴンの頂点とテクスチャ座標を設定
	////	SetSprite(g_VertexBuffer, g_Pos.x, g_Pos.y, TEXTURE_WIDTH_LOGO, TEXTURE_HEIGHT_LOGO, 0.0f, 0.0f, 1.0f, 1.0f);
	//	SetSpriteColor(g_VertexBuffer, g_Pos.x, g_Pos.y, TEXTURE_WIDTH_LOGO, TEXTURE_HEIGHT_LOGO, 0.0f, 0.0f, 1.0f, 1.0f,
	//		XMFLOAT4(1.0f, 1.0f, 1.0f, alpha));

	//	// ポリゴン描画
	//	GetDeviceContext()->Draw(4, 0);
	//}

	//	// 加減算のテスト
	//	SetBlendState(BLEND_MODE_ADD);		// 加算合成
	////	SetBlendState(BLEND_MODE_SUBTRACT);	// 減算合成
	//	for(int i=0; i<30; i++)
	//	{
	//		// テクスチャ設定
	//		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[2]);
	//
	//		// １枚のポリゴンの頂点とテクスチャ座標を設定
	//		float dx = 100.0f;
	//		float dy = 100.0f;
	//		float sx = (float)(rand() % 100);
	//		float sy = (float)(rand() % 100);
	//
	//
	//		SetSpriteColor(g_VertexBuffer, dx+sx, dy+sy, 50, 50, 0.0f, 0.0f, 1.0f, 1.0f,
	//			XMFLOAT4(0.3f, 0.3f, 1.0f, 0.5f));
	//
	//		// ポリゴン描画
	//		GetDeviceContext()->Draw(4, 0);
	//	}
	//	SetBlendState(BLEND_MODE_ALPHABLEND);	// 半透明処理を元に戻す

}
