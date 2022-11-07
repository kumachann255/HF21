//=============================================================================
//
// パズルのBG処理 [drum.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "sprite.h"
#include "drum.h"
#include "game.h"
#include "slot.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_WIDTH				(R_SCREEN_WIDTH)	// 背景サイズ
#define TEXTURE_HEIGHT				(R_SCREEN_HEIGHT)	// 
#define FLAM_TEXTURE_WIDTH			(430.0f)	// 背景サイズ
#define FLAM_TEXTURE_HEIGHT			(470.0f)	// 
#define FLAM_OFFSET_Y				(80.0f)
#define FLAM_OFFSET_X				(-4.0f)

#define TEST_POS_X					(800.0f)
#define TEST_POS_Y					(250.0f)


#define TEXTURE_MAX					(8)				// テクスチャの数
#define TEXTURE_POS_X_BASE			(850.0f)
#define DRUM_SPEED					(2.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void SetColor(int i);




//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer = NULL;		// 頂点情報
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報

static char *g_TexturName[TEXTURE_MAX] = {
	"data/TEXTURE/tex_penki_red.png",
	"data/TEXTURE/tex_penki_blue.png",
	"data/TEXTURE/tex_penki_yellow.png",
	"data/TEXTURE/tree000.png",
	"data/TEXTURE/tree000.png",
	"data/TEXTURE/tree000.png",
	"data/TEXTURE/flamTest.png",
	"data/TEXTURE/field003.jpg",
};


static float	alpha;
static BOOL	flag_alpha;
static Drum g_Drum[3][3];
static int g_count;
static bool drumMove[3];
static XMFLOAT4 g_Color;


static BOOL						g_Load = FALSE;


//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitDrum(void)
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
	for (int i = 0; i < 3; i++)
	{
		for (int p = 0; p < 3; p++)
		{
			if (i == 2)
			{
				g_Drum[i][p].SetType(p + 3);
			}
			else
			{
				g_Drum[i][p].SetType(p);
			}

			g_Drum[i][p].m_Pos.x = TEXTURE_POS_X_BASE - (TEXTURE_WIDTH_COLOR * i);
			g_Drum[i][p].m_Pos.y += TEXTURE_HEIGHT_COLOR * p;

		}
	}

	alpha = 1.0f;
	flag_alpha = TRUE;
	g_count = 0;
	drumMove[0] = false;
	drumMove[1] = false;
	drumMove[2] = false;

	g_Color = { 0.2f,0.2f,0.2f,1.0f };

	g_Load = TRUE;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitDrum(void)
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
void UpdateDrum(void)
{
	for (int i = 0; i < 3; i++)
	{
		for (int p = 0; p < 3; p++)
		{
			if(g_Drum[i][p].GetMove()) g_Drum[i][p].Action();
			else g_Drum[i][p].SetStopDrum();
		}
	}

	// 止める
	//if ((GetKeyboardTrigger(DIK_J)) && (g_count > 60))
	if ((GetKeyboardTrigger(DIK_J)))
		{
		for (int i = 0; i < 3; i++)
		{
			if (g_Drum[i][0].GetMove())
			{
				drumMove[i] = false;

				for (int p = 0; p < 3; p++)
				{
					g_Drum[i][p].SetMove(false);
					g_Drum[i][p].SetStopDrum();
				}

				PlaySound(SOUND_LABEL_SE_se_slot_button_01);	// スロットを止める

				if (i == 2)
				{
					SetShotCrows(g_Color);

					PlaySound(SOUND_LABEL_SE_se_crow_cry_01);	// カラースの鳴き声
					PlaySound(SOUND_LABEL_SE_se_crow_flap_04);	// カラース発射

				}
				break;
			}
		}
	}

	// 動かす
	if (GetKeyboardTrigger(DIK_K))
	{

		PlaySound(SOUND_LABEL_SE_se_slot_lever_01);				// スロットを動かす

		for (int i = 0; i < 3; i++)
		{
			drumMove[i] = true;
		}

		//g_Color = { 0.2f,0.2f,0.2f,1.0f };
	}

	if (drumMove[0]) g_count++;
	else g_count = 0;

	if (g_count == 1)
	{
		for (int p = 0; p < 3; p++)
		{
			g_Drum[0][p].SetMove(true);
		}
	}
	if (g_count == 20)
	{
		for (int p = 0; p < 3; p++)
		{
			g_Drum[1][p].SetMove(true);
		}
	}
	if (g_count == 40)
	{
		for (int p = 0; p < 3; p++)
		{
			g_Drum[2][p].SetMove(true);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawDrum(void)
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
	for (int i = 0; i < 3; i++)
	{
		for (int p = 0; p < 3; p++)
		{
			// テクスチャ設定
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[g_Drum[i][p].GetType()]);

			// １枚のポリゴンの頂点とテクスチャ座標を設定
			SetSprite(g_VertexBuffer, g_Drum[i][p].m_Pos.x, g_Drum[i][p].m_Pos.y, TEXTURE_WIDTH_COLOR, TEXTURE_HEIGHT_COLOR, 0.0f, 0.0f, 1.0f, 1.0f);

			// ポリゴン描画
			GetDeviceContext()->Draw(4, 0);
		}
	}

	// ドラムの枠を描画
	{
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[6]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSprite(g_VertexBuffer, TEXTURE_POS_X_BASE - TEXTURE_WIDTH_COLOR + FLAM_OFFSET_X, START_POS_Y + TEXTURE_HEIGHT_COLOR * 2.0f - FLAM_OFFSET_Y, FLAM_TEXTURE_WIDTH, FLAM_TEXTURE_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
		//SetSpriteColor(g_VertexBuffer, g_Pos.x, g_Pos.y, TEXTURE_WIDTH_LOGO, TEXTURE_HEIGHT_LOGO, 0.0f, 0.0f, 1.0f, 1.0f,
		//	XMFLOAT4(1.0f, 1.0f, 1.0f, alpha));

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	// 試しの色を描画
	{
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[7]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		//SetSprite(g_VertexBuffer, TEXTURE_POS_X_BASE - TEXTURE_WIDTH_COLOR, START_POS_Y + TEXTURE_HEIGHT_COLOR * 2.0f - FLAM_OFFSET_Y, FLAM_TEXTURE_WIDTH, FLAM_TEXTURE_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
		SetSpriteColor(g_VertexBuffer, TEST_POS_X, TEST_POS_Y, TEXTURE_WIDTH_COLOR, TEXTURE_HEIGHT_COLOR, 0.0f, 0.0f, 1.0f, 1.0f,
			g_Color);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

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


void SetColor(int i)
{
	if (i == 2) return;

	for (int p = 0; p < 3; p++)
	{
		if (g_Drum[i][p].GetCenter())
		{
			switch (p)
			{
			case drum_red:
				g_Color.x += 0.7f;
				break;

			case drum_blue:
				g_Color.z += 0.7f;
				break;

			case drum_yellow:
				g_Color.x += 0.35f;
				g_Color.y += 0.35f;
				break;
			}
		}
	}
}



XMFLOAT4 GetColor(void)
{
	return g_Color;
}

void SetColorTemp(XMFLOAT4 color)
{
	g_Color = color;
}