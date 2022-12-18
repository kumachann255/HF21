#include "bonusGuidanceY.h"

BonusGuidance::BonusGuidance()
{
	ID3D11Device *pDevice = GetDevice();

	//テクスチャ生成
	for (int i = 0; i < GUIDANCE_TEXTURE_MAX; i++)
	{
		m_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			m_TexturName[i],
			NULL,
			NULL,
			&m_Texture[i],
			NULL);
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
	for (int i = 0; i < GUIDANCE_TEXTURE_MAX; i++)
	{
		m_Use[i] = TRUE;
		m_w[i] = GUIDANCE_TEXTURE_WIDTH;
		m_h[i] = GUIDANCE_TEXTURE_HEIGHT;
		m_Pos[i] = { 90.0f + (960.0f - 90.0f * 2) * i, 270.0f, 0.0f };
		m_UV[i] = { 0.0f, 0.0f };
	}
}

BonusGuidance::~BonusGuidance()
{
}

void BonusGuidance::Update(void)
{
	for (int i = 0; i < GUIDANCE_TEXTURE_MAX; i++)
	{
		m_UV[i].y += 0.001f - (GUIDANCE_SPEED * 2 * i);
		if (m_UV[i].y > 1.0f) m_UV[i].y = 0.0f;
		else if (m_UV[i].y < 0.0f) m_UV[i].y = 1.0f;
	}
}

void BonusGuidance::Draw(void)
{
	// 2Dの物を描画する処理
	// Z比較あり（炎とかぶってしまうから）
	SetDepthEnable(FALSE);

	// ライティングを無効
	SetLightEnable(FALSE);

	SetAlphaTestEnable(TRUE);

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

	for (int i = 0; i < GUIDANCE_TEXTURE_MAX; i++)
	{
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[i]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColor(m_VertexBuffer, m_Pos[i].x, m_Pos[i].y, m_w[i], m_h[i], 0.0f, m_UV[i].y, 1.0f, 1.5f,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	// ライティングを有効に
	SetLightEnable(TRUE);

	// Z比較あり
	SetDepthEnable(TRUE);
}
