//=============================================================================
//
// UI処理 [UI.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "sprite.h"
#include "UI.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// コンストラクター
//=============================================================================
UITexData::UITexData()
{
}

//=============================================================================
// 引数付きコンストラクター
//=============================================================================
UITexData::UITexData(char *textureName) : m_TextureName(textureName)
{
	//Create();
}

//=============================================================================
// テクスチャー生成処理
//=============================================================================
HRESULT UITexData::Create(char *textureName)
{
	m_TextureName = textureName;

	// テクスチャ生成
	D3DX11CreateShaderResourceViewFromFile(GetDevice(),
		m_TextureName,
		NULL,
		NULL,
		&m_Texture,
		NULL);

	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);



	return S_OK;
}

//=============================================================================
// デストラクター
//=============================================================================
UITexData::~UITexData()
{

	if (m_VertexBuffer)
	{
		m_VertexBuffer->Release();
		m_VertexBuffer = NULL;
	}

	if (m_Texture)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}
}



//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================


//=============================================================================
// コンストラクター
//=============================================================================
UIObject::UIObject()
{
	m_UITexData = new UITexData;
	m_isUse = TRUE;
}

//=============================================================================
// デストラクター
//=============================================================================
UIObject::~UIObject()
{
	delete m_UITexData;
}

//=============================================================================
// 更新処理
//=============================================================================
void UIObject::Update(void)
{
	if (!m_isUse) return;

	m_timeCnt++;

	if (m_timeCnt > m_timeLimit)
	{
		m_isUse = FALSE;
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void UIObject::Draw(void)
{

	if (!m_isUse) return;

	SetViewPort(TYPE_FULL_SCREEN);

	// 2Dの物を描画する処理
	// Z比較なし
	SetDepthEnable(FALSE);

	// ライティングを無効
	SetLightEnable(FALSE);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, m_UITexData->GetpVertexBuffer(), &stride, &offset);

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
	{
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, m_UITexData->GetTexture());

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColorRotation(m_UITexData->GetVertexBuffer(),
			m_pos.x, m_pos.y, m_fWidth, m_fHeight,
			0.0f, 0.0f, 1.0f, 1.0f,
			m_color, m_rot);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	// ライティングを有効に
	SetLightEnable(TRUE);

	// Z比較あり
	SetDepthEnable(TRUE);
}

