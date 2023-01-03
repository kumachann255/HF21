#include "tutorialBG.h"
#include "modeSelect.h"

TutorialBG::TutorialBG()
{
	ID3D11Device *pDevice = GetDevice();

	//テクスチャ生成
	for (int i = 0; i < TUTORIALBG_TEXTURE_MAX; i++)
	{
		m_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			m_TexturName[i],
			NULL,
			NULL,
			&m_Texture[i],
			NULL);

		m_Use[i] = FALSE;
	}


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);


	// プレイヤーの初期化
	m_Use[0] = TRUE;
	m_w = 960.0f;
	m_h = 540.0f;
	m_Pos = { m_w / 2, m_h / 2, 0.0f };

}

void TutorialBG::Update()
{
}

void TutorialBG::Draw()
{
	// 2Dの物を描画する処理
	// Z比較あり（炎とかぶってしまうから）
	SetDepthEnable(FALSE);

	// ライティングを無効
	SetLightEnable(FALSE);

	// FALSEが透明化
	SetAlphaTestEnable(FALSE);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// マトリクス設定
	SetWorldViewProjection2D();

	// プリミティブトポロジ設定
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	for (int i = 0; i < TUTORIALBG_TEXTURE_MAX - 1; i++)
	{
		if (!m_Use[i]) continue;

		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[i]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColor(m_VertexBuffer, m_Pos.x, m_Pos.y, m_w, m_h, 0.0f, 0.0f, 1.0f, 1.0f,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	// スキップボタンの描画
	// テクスチャ設定
	if (GetPlayerType())
	{	// キーボード
		GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[tutorial_skip]);
	}
	else
	{	// パッド
		GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[tutorial_skip_pad]);
	}

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSpriteColor(m_VertexBuffer, m_Pos.x, m_Pos.y, m_w, m_h, 0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);

	// FALSEが透明化
	SetAlphaTestEnable(TRUE);

	// ライティングを有効に
	SetLightEnable(TRUE);

	// Z比較あり
	SetDepthEnable(TRUE);

}

void TutorialBG::SetTex(int num, BOOL data)
{
	m_Use[num] = data;
}

void TutorialBG::Init()
{
	for (int i = 0; i < TUTORIALBG_TEXTURE_MAX; i++)
	{
		m_Use[i] = FALSE;
	}
	m_Use[0] = TRUE;
}
