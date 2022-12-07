#include "bonusTimer.h"

BonusTimer::BonusTimer()
{
	ID3D11Device *pDevice = GetDevice();

	//テクスチャ生成
	for (int i = 0; i < BONUS_TIMER_TEXTURE_MAX; i++)
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
	m_Use = TRUE;
	m_w = BONUS_TIMER_TEXTURE_WIDTH;
	m_h = BONUS_TIMER_TEXTURE_HEIGHT;
	m_Pos = { 550.0f, 130.0f, 0.0f };
	m_TexNo = 0;

	m_time = 0;	// スコアの初期化

}

BonusTimer::~BonusTimer()
{
}

void BonusTimer::Update(void)
{
}

void BonusTimer::Draw(void)
{
	// 2Dの物を描画する処理
	// Z比較なし
	SetDepthEnable(TRUE);

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

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[m_TexNo]);

	// 桁数分処理する
	int number = (int)(m_time * 100.0f);
	for (int i = 0; i < 3; i++)
	{
		// 今回表示する桁の数字
		float x = (float)(number % 10);

		// スコアの位置やテクスチャー座標を反映
		float px = m_Pos.x - m_w * i;	// スコアの表示位置X
		if (i == 2) px -= 20.0f;

		float py = m_Pos.y;			// スコアの表示位置Y
		float pw = m_w;				// スコアの表示幅
		float ph = m_h;				// スコアの表示高さ

		float tw = 1.0f / 10;		// テクスチャの幅
		float th = 1.0f / 1;		// テクスチャの高さ
		float tx = x * tw;			// テクスチャの左上X座標
		float ty = 0.0f;			// テクスチャの左上Y座標

		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColor(m_VertexBuffer, px, py, pw, ph, tx, ty, tw, th,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);

		// 次の桁へ
		number /= 10;
	}

	// ライティングを有効に
	SetLightEnable(TRUE);

	// Z比較あり
	SetDepthEnable(TRUE);
}

void BonusTimer::SetTime(float time)
{
	m_time = time;
}
