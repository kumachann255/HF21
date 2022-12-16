//=============================================================================
//
// パーティクル処理 [particle.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "particle.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_MAX			(5)			// テクスチャの数

#define	PARTICLE_SIZE_X		(30.0f)		// 頂点サイズ
#define	PARTICLE_SIZE_Y		(30.0f)		// 頂点サイズ
#define	VALUE_MOVE_PARTICLE	(10.0f)		// 移動速度


#define TEXTURE_PATTERN_DIVIDE_X	    (10)		                                            // アニメパターンのテクスチャ内分割数（X)
#define TEXTURE_PATTERN_DIVIDE_Y	    (1)		                                                // アニメパターンのテクスチャ内分割数（Y)
#define ANIM_PATTERN_NUM			    (TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y) 	// アニメーションパターン数
#define ANIM_WAIT					    (5)													   // アニメーションの切り替わるWait値


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexParticle(void);


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static ID3D11Buffer					*g_VertexBuffer = NULL;		// 頂点バッファ

static ID3D11ShaderResourceView		*g_Texture[TEXTURE_MAX] = { NULL };	// テクスチャ情報
static int							g_TexNo;					// テクスチャ番号

static PARTICLE						*g_pParticle[PARTICLE_BUFFER];			//画面上に発生できるエフェクトの上限			

static XMFLOAT3					g_posBase;						// ビルボード発生位置
static float					g_fWidthBase = 10.0f;			// 基準の幅
static float					g_fHeightBase = 1.0f;			// 基準の高さ

static char *g_TextureName[TEXTURE_MAX] =
{
	"data/TEXTURE/EFFECT/effect_bom.png",
	"data/TEXTURE/EFFECT/effect_kemuri.png",
	"data/TEXTURE/EFFECT/effect_kemuri2.png",
	"data/TEXTURE/EFFECT/effect_light.png",
	"data/TEXTURE/EFFECT/effect_reflection.png",
};

static BOOL						g_Load = FALSE;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitParticle(void)
{
	// 頂点情報の作成
	MakeVertexParticle();


	for (int i = 0; i < PARTICLE_BUFFER; i++)
	{
		g_pParticle[i] = new PARTICLE[MAX_PARTICLE];
	}

	// テクスチャ生成
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
			NULL,
			NULL,
			&g_Texture[i],
			NULL);
	}

	g_TexNo = 0;

	g_posBase = XMFLOAT3(0.0f, 0.0f, 0.0f);

	g_Load = TRUE;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitParticle(void)
{
	if (g_Load == FALSE) return;

	//テクスチャの解放
	for (int nCntTex = 0; nCntTex < TEXTURE_MAX; nCntTex++)
	{
		if (g_Texture[nCntTex] != NULL)
		{
			g_Texture[nCntTex]->Release();
			g_Texture[nCntTex] = NULL;
		}
	}

	// 頂点バッファの解放
	if (g_VertexBuffer != NULL)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}


	for (int i = 0; i < PARTICLE_BUFFER; i++)
	{
		if (g_pParticle[i])
		{
			delete[] g_pParticle[i];
			g_pParticle[i] = NULL;
		}

	}


	g_Load = FALSE;
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateParticle(void)
{
	for (int i = 0; i < PARTICLE_BUFFER; i++)
	{
		if (g_pParticle[i]->GetSwich())
		{
			for (int j = 0; j < MAX_PARTICLE; j++)
			{
				g_pParticle[i][j].Update();
				g_pParticle[i][j].SpriteAnim.Update(g_pParticle[i][j].GetAnimeTime());

			}
		}

	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawParticle(void)
{
	// ライティングを無効に
	SetLightEnable(FALSE);

	// Z比較無し
	SetDepthEnable(FALSE);

	// 通常ブレンドに戻す
	SetBlendState(BLEND_MODE_ALPHABLEND);

	for (int i = 0; i < PARTICLE_BUFFER; i++)
	{
		if (g_pParticle[i]->GetSwich())
		{
			for (int j = 0; j < MAX_PARTICLE; j++)
			{
				g_pParticle[i][j].Draw();

			}
		}
	}


	// Z比較有効
	SetDepthEnable(TRUE);

	// ライティングを有効に
	SetLightEnable(TRUE);

}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexParticle(void)
{
	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

	{//頂点バッファの中身を埋める
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		// 頂点座標の設定
		vertex[0].Position = XMFLOAT3(-PARTICLE_SIZE_X, PARTICLE_SIZE_Y, 0.0f);
		vertex[1].Position = XMFLOAT3(PARTICLE_SIZE_X, PARTICLE_SIZE_Y, 0.0f);
		vertex[2].Position = XMFLOAT3(-PARTICLE_SIZE_X, -PARTICLE_SIZE_Y, 0.0f);
		vertex[3].Position = XMFLOAT3(PARTICLE_SIZE_X, -PARTICLE_SIZE_Y, 0.0f);

		// 法線の設定
		vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
		vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

		// 反射光の設定
		vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		vertex[0].TexCoord = { 0.0f, 0.0f };
		vertex[1].TexCoord = { 1.0f, 0.0f };
		vertex[2].TexCoord = { 0.0f, 1.0f };
		vertex[3].TexCoord = { 1.0f, 1.0f };

		GetDeviceContext()->Unmap(g_VertexBuffer, 0);
	}

	return S_OK;
}




//=============================================================================
// 　　　　　　　　　　　　クラス関数の定義
//=============================================================================

// コンストラクター
PARTICLE::PARTICLE()
{
	// パーティクルワークの初期化
	m_posBase = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_move = XMFLOAT3(1.0f, 1.0f, 1.0f);

	ZeroMemory(&m_material, sizeof(m_material));
	m_material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	m_fSizeX = PARTICLE_SIZE_X;
	m_fSizeY = PARTICLE_SIZE_Y;
	m_nLife = 0;
	m_bUse = FALSE;
	m_bSwich = FALSE;
	m_nTexno = EFFECT_KEMURI;
	m_Pattern = MOVE_PATTERN_UP;
	m_nextAnime = 0;
}

void PARTICLE::Update(void)
{


	XMFLOAT3 move;
	float fAngle, fLength;
	int nLife;

	switch (m_Pattern)
	{
	case MOVE_PATTERN_UP:


		fAngle = (float)(rand() % 628 - 314) / 100.0f;
		fLength = rand() % (int)(g_fWidthBase * 200) / 100.0f - g_fWidthBase;
		move.x = sinf(fAngle) * fLength;
		move.y = rand() % 300 / 200.0f;
		move.z = cosf(fAngle) * fLength;

		nLife = rand() % 100 + 50;

		// ビルボードの設定
		SetParticle(/*m_posBase,*/ move, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), m_fSizeX, m_fSizeY, nLife);

		break;

	case MOVE_PATTERN_UP_SMALL:


		fAngle = (float)(rand() % 628 - 314) / 100.0f;
		fLength = rand() % (int)(300) / 100.0f;
		move.x = sinf(fAngle) * fLength;
		move.y = (float)(rand() % 300 - 150) / 100.0f;
		move.z = cosf(fAngle) * fLength;

		nLife = rand() % 50 + 50;

		// ビルボードの設定
		SetParticle(/*m_posBase,*/ move, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), m_fSizeX, m_fSizeY, nLife);

		break;

	case MOVE_PATTERN_UPLEFT:

		fAngle = (float)(rand() % 314) / 100.0f;
		fLength = (float)(rand() % 200) ;
		move.x = -fLength * 0.4f;
		move.y = 3.0f;
		move.z = cosf(fAngle) * fLength * 1.2f;

		nLife = rand() % 100 + 50;

		// ビルボードの設定
		SetParticle(/*m_posBase,*/ move, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), m_fSizeX, m_fSizeY, nLife);

		break;

	}


	// 使用されていたら、位置とライフを更新
	if (m_bUse)
	{
		AddPos(m_move);

		m_nLife--;

		if (m_nLife <= 0 || SpriteAnim.GetUse() == FALSE)
		{
			m_bUse = FALSE;
			SpriteAnim.SetUse(FALSE);
			SetUse(FALSE);
			SetSwich(FALSE);
			SpriteAnim.Init();
		}
	}

}

void PARTICLE::Draw(void)
{

	if (m_bUse)
	{

		XMMATRIX mtxScl, mtxTranslate, mtxWorld, mtxView;
		CAMERA *cam = GetCamera();

		// 頂点バッファ設定
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

		// プリミティブトポロジ設定
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[m_nTexno]);

		{//頂点バッファの中身を埋める
			D3D11_MAPPED_SUBRESOURCE msr;
			GetDeviceContext()->Map(g_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

			// 頂点座標の設定
			vertex[0].Position = XMFLOAT3(-m_fSizeX, m_fSizeY, 0.0f);
			vertex[1].Position = XMFLOAT3(m_fSizeX, m_fSizeY, 0.0f);
			vertex[2].Position = XMFLOAT3(-m_fSizeX, -m_fSizeY, 0.0f);
			vertex[3].Position = XMFLOAT3(m_fSizeX, -m_fSizeY, 0.0f);

			// 法線の設定
			vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
			vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
			vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
			vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			// 反射光の設定
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);


			XMFLOAT2 tpos = SpriteAnim.GetTexPos();
			XMFLOAT2 twidth = SpriteAnim.GetTexWidth();

			// テクスチャ座標の設定
			vertex[0].TexCoord = XMFLOAT2(tpos.x, tpos.y);
			vertex[1].TexCoord = XMFLOAT2(tpos.x + twidth.x, tpos.y);
			vertex[2].TexCoord = XMFLOAT2(tpos.x, tpos.y + twidth.y);
			vertex[3].TexCoord = XMFLOAT2(tpos.x + twidth.x, tpos.y + twidth.y);

			GetDeviceContext()->Unmap(g_VertexBuffer, 0);
		}


		// ワールドマトリックスの初期化
		mtxWorld = XMMatrixIdentity();

		// ビューマトリックスを取得
		mtxView = XMLoadFloat4x4(&cam->mtxView);

		// ビルボード処理(処理が速い)
		mtxWorld.r[0].m128_f32[0] = mtxView.r[0].m128_f32[0];
		mtxWorld.r[0].m128_f32[1] = mtxView.r[1].m128_f32[0];
		mtxWorld.r[0].m128_f32[2] = mtxView.r[2].m128_f32[0];

		mtxWorld.r[1].m128_f32[0] = mtxView.r[0].m128_f32[1];
		mtxWorld.r[1].m128_f32[1] = mtxView.r[1].m128_f32[1];
		mtxWorld.r[1].m128_f32[2] = mtxView.r[2].m128_f32[1];

		mtxWorld.r[2].m128_f32[0] = mtxView.r[0].m128_f32[2];
		mtxWorld.r[2].m128_f32[1] = mtxView.r[1].m128_f32[2];
		mtxWorld.r[2].m128_f32[2] = mtxView.r[2].m128_f32[2];

		// スケールを反映
		mtxScl = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ワールドマトリックスの設定
		SetWorldMatrix(&mtxWorld);

		// マテリアル設定
		SetMaterial(m_material);

		// ポリゴンの描画
		GetDeviceContext()->Draw(4, 0);
	}

}


void PARTICLE::SetParticle(/*XMFLOAT3 pos,*/ XMFLOAT3 move, XMFLOAT4 col, float fSizeX, float fSizeY, int nLife)
{
	if (!m_bUse)
	{
		//m_pos = pos;
		m_rot = { 0.0f, 0.0f, 0.0f };
		m_scale = { 1.0f, 1.0f, 1.0f };
		m_move = move;
		m_material.Diffuse = col;
		m_fSizeX = fSizeX;
		m_fSizeY = fSizeY;
		m_nLife = nLife;
		m_bUse = TRUE;
	}
}

void SPRITE_ANIMATION::Update(int time)
{

	if (m_use == TRUE)
	{
		m_tw = 1.0f / TEXTURE_PATTERN_DIVIDE_X;       // テクスチャの幅
		m_th = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;       // テクスチャの高さ
		m_tx = m_tw * m_uwnum;
		m_ty = m_th;

		m_countAnim++;

		if (m_countAnim > time)
		{
			m_countAnim = 0.0f;

			if (m_uwnum < TEXTURE_PATTERN_DIVIDE_X - 1)
			{
				m_uwnum++;
			}
			else
			{
				//m_use = FALSE;
				SetUse(FALSE);
				m_uwnum = 0;

			}
		}
	}

	if (!m_use)
	{
		m_uwnum = 0;
	}


}



//=============================================================================
// パーティクルの呼び出し
// <引数>
// XMFLOAT3 pos   : 発生座標 
// float    size  : 大きさ
// int      num   : 発生させるパーティクルの数　※マクロ定義 MAX_PARTICLE を超えないように！
// int      texID : テクスチャーID
//
// 
//=============================================================================
void CallParticle(XMFLOAT3 pos, float size, int num, int texID, int pattern)
{

	for (int i = 0; i < PARTICLE_BUFFER; i++)
	{
		if (!g_pParticle[i]->GetSwich())
		{
			for (int j = 0; j < num; j++)
			{
				g_pParticle[i][j].SetSwich(TRUE);
				g_pParticle[i][j].SetPosBase(pos);
				g_pParticle[i][j].SetPos(pos);
				g_pParticle[i][j].SetTexno(texID);
				g_pParticle[i][j].SetSize(size);
				g_pParticle[i][j].SetPattern(pattern);
				g_pParticle[i][j].SpriteAnim.SetUse(TRUE);
				g_pParticle[i][j].SetAnimeTime(rand() % 5 + 3);
			}

			break;
		}

	}

}
