#include "garbageIcon.h"

GarbageIcon::GarbageIcon()
{
	ID3D11Device *pDevice = GetDevice();

	//テクスチャ生成
	for (int i = 0; i < GARBAGE_TEXTURE_MAX; i++)
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
	m_w = GARBAGE_TEXTURE_WIDTH;
	m_h = GARBAGE_TEXTURE_HEIGHT;
	m_Pos = { 95.0f, 493.0f, 0.0f };
	m_TexNo = 0;

	m_startColor = { 0.854f, 0.854f, 0.0f, 1.0f };
	m_endColor = { 1.0f, 0.282f, 0.333f, 1.0f };
}

GarbageIcon::~GarbageIcon()
{
}

void GarbageIcon::Update()
{
}

void GarbageIcon::Draw()
{
	// 2Dの物を描画する処理
	// Z比較なし
	SetDepthEnable(FALSE);

	// ライティングを無効
	SetLightEnable(FALSE);

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

	XMFLOAT4 color;
	float p;
	float sclValue = 1.0f;

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[0]);

	for (int i = 0; i < m_iconNum; i++)
	{
		p = (float)i / (float)MAX_GARBAGE;
		color.x = m_startColor.x + (m_endColor.x - m_startColor.x) * p;
		color.y = m_startColor.y + (m_endColor.y - m_startColor.y) * p;
		color.z = m_startColor.z + (m_endColor.z - m_startColor.z) * p;
		color.w = 1.0f;

		if (i > 12)
		{
			sclValue *= SCL_VALUE_GARBAGE;
		}
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColor(m_VertexBuffer, m_Pos.x + i * GARBAGE_TEXTURE_DISTANCE, m_Pos.y - (m_h * sclValue - m_h) / 2.0f, m_w, m_h * sclValue, 0.0f, 0.0f, 1.0f, 1.0f,
			color);

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[1]);

	// １枚のポリゴンの頂点とテクスチャ座標を設定
	SetSpriteColor(m_VertexBuffer, 350.0f, 485.0f, 670.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	// ポリゴン描画
	GetDeviceContext()->Draw(4, 0);


	// ライティングを有効に
	SetLightEnable(TRUE);

	// Z比較あり
	SetDepthEnable(TRUE);
}
