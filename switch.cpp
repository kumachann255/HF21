#include "switch.h"

Switch::Switch()
{
	ID3D11Device *pDevice = GetDevice();

	//テクスチャ生成
	for (int i = 0; i < SWITCH_TEXTURE_MAX; i++)
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
	m_w = SWITCH_TEXTURE_WIDTH;
	m_h = SWITCH_TEXTURE_HEIGHT;
	m_Pos = m_PosEffect = { 760.0f, 490.0f, 0.0f };

	for (int i = 0; i < 3; i++)
	{
		m_texNum[i] = 0;
	}
}

Switch::~Switch()
{
}

void Switch::Update()
{
	if (!m_isEffect) return;

	m_count++;
	if (m_count > SWITCH_EFFECT_LIFE) m_isEffect = FALSE;
}

void Switch::Draw()
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

	if (m_isEffect)
	{
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[2]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColor(m_VertexBuffer, m_PosEffect.x, m_PosEffect.y, m_w * 3.0f, m_h * 3.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	for (int i = 0; i < 3; i++)
	{
		// テクスチャ設定
		GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[m_texNum[i]]);

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColor(m_VertexBuffer, m_Pos.x - SWITCH_DISTANCE * i, m_Pos.y, m_w, m_h, 0.0f, 0.0f, 1.0f, 1.0f,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	// ライティングを有効に
	SetLightEnable(TRUE);

	// Z比較あり
	SetDepthEnable(TRUE);
}

void Switch::SwitchON(int num)
{
	m_isEffect = TRUE;
	m_texNum[num] = 1;
	m_count = 0;
	m_PosEffect.x = m_Pos.x - SWITCH_DISTANCE * num;
}

void Switch::SwitchOFF(void)
{
	for (int i = 0; i < 3; i++)
	{
		m_texNum[i] = 0;
	}
}
