#include "calendar_num.h"
#include "RollerManager.h"
#include "fade.h"
#include "texManager.h"
#include "sound.h"
#include "TrainingCrowManager.h"

CalendarNum::CalendarNum(God *god) :GodObject(god)
{
	ID3D11Device *pDevice = GetDevice();

	//テクスチャ生成
	for (int i = 0; i < CALENDAR_TEXTURE_MAX; i++)
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
	m_w[0] = CALENDAR_WAKU_TEXTURE_WIDTH;
	m_h[0] = CALENDAR_WAKU_TEXTURE_HEIGHT;
	m_Pos[0] = { 850.0f, 80.0f, 0.0f };

	m_w[1] = CALENDAR_TEXTURE_WIDTH;
	m_h[1] = CALENDAR_TEXTURE_HEIGHT;
	m_Pos[1] = { 850.0f, 85.0f, 0.0f };
}

CalendarNum::~CalendarNum()
{
}

void CalendarNum::Update()
{
	// チュートリアル以外は時間を進める
	// ボーナスチャンスの時には時間を進めない
	if ((GetSceneID() != TUTORIAL_ID) || (!GetGod()->GetTrainingCrowManager()->GetBonus()))
	{
		m_count++;
		//m_count += SOEED_CALENDAR;
	}

	// 月を更新
	if (m_count >= CALENDAR_SWITCH_TIME)
	{
		AddMonth();
		m_count = 0;

		if (m_month % 3 == 0)
		{
			m_swichfFlag = TRUE;
		}

		// 3月から4月に変わろうとすると時間切れ
		if ((m_month % month_max == month_3) && (m_loopNum < 2))
		{
			m_loopNum++;
		}
		
		if ((m_month % month_max == month_3) && (m_loopNum == 3))
		{
			m_isTimeUp = TRUE;

			GetGod()->GetTexManager()->GetUIManager()->SetTexture(
				telop_timeUp, texType_cutIn_up, XMFLOAT3(480.f, 240.0f, 0.0f), TIMEUP_COUNT_MAX / 60);
		}
	}
	else
	{
		m_swichfFlag = FALSE;
	}

	if (m_uvStartY < m_month * DIStANCE_CALENDAR)
	{
		m_uvStartY += SOEED_CALENDAR;
		//m_uvEndY += SOEED_CALENDAR;
	}

	if (m_isTimeUp)
	{
		m_timeUpCount++;

		if (m_timeUpCount == TIMEUP_COUNT_MAX)
		{
			m_isTimeUp = FALSE;
			// シーン変更
			SetFade(FADE_OUT, ENDROLL_ID);
			StopSound(SOUND_LABEL_BGM_stage01);
		}
	}
}

void CalendarNum::Draw()
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

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[0]);

	{
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColor(m_VertexBuffer, m_Pos[0].x, m_Pos[0].y, m_w[0], m_h[0], 0.0f, 0.0f, 1.0f, 1.0f,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	// テクスチャ設定
	GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[1]);

	{
		// １枚のポリゴンの頂点とテクスチャ座標を設定
		SetSpriteColor(m_VertexBuffer, m_Pos[1].x, m_Pos[1].y, m_w[1], m_h[1], 0.0f, m_uvStartY, 1.0f, m_uvEndY,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// ポリゴン描画
		GetDeviceContext()->Draw(4, 0);
	}

	// ライティングを有効に
	SetLightEnable(TRUE);

	// Z比較あり
	SetDepthEnable(TRUE);
}

void CalendarNum::Init()
{
	m_month = month_4;
	m_uvStartY = 0.0f;
	m_uvEndY = 1.0f / MAX_CALENDAR_NUM;
	m_count = 0;
	m_swichfFlag = FALSE;
	m_isTimeUp = FALSE;
	m_timeUpCount = 0;
	m_loopNum = 0;

	// プレイヤーの初期化
	m_w[0] = CALENDAR_WAKU_TEXTURE_WIDTH;
	m_h[0] = CALENDAR_WAKU_TEXTURE_HEIGHT;
	m_Pos[0] = { 850.0f, 80.0f, 0.0f };

	m_w[1] = CALENDAR_TEXTURE_WIDTH;
	m_h[1] = CALENDAR_TEXTURE_HEIGHT;
	m_Pos[1] = { 850.0f, 85.0f, 0.0f };
}
