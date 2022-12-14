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
#include "texManager.h"
#include "God.h"


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

	if (m_texType != texType_endless)
	{
		m_timeCnt++;
		m_count++;
	}

	if (m_timeCnt > m_timeLimit)
	{
		m_isUse = FALSE;
	}

	// チュートリアルの場合テロップをスキップ機能追加
	if (GetSceneID() == TUTORIAL_ID)
	{
		if (GetKeyboardTrigger(DIK_SPACE))
		{
			if (m_timeCnt < m_timeLimit - UI_ACTION_TIME)
			{
				m_timeCnt = m_timeLimit - UI_ACTION_TIME;
			}
		}
	}

	switch (m_texType)
	{
	case texType_normal:
		UpdateNomal();
		break;

	case texType_spring:
		UpdateSpring();

	case texType_fade:
		UpdateFade();
		break;

	case texType_cutIn_up_Update:
	case texType_cutIn_under_Update:
		UpdateZoomInOut();

	case texType_cutIn_right:
	case texType_cutIn_left:
	case texType_cutIn_up:
	case texType_cutIn_under:
		UpdateCutIn();
		break;

	case texType_zoomIn_Update:
		UpdateZoomInOut();

	case texType_zoomIn:
	case texType_zoomIn_rot:
		UpdateZoomIn();
		break;

	case texType_tansition:
		UpdateTransition();
		break;

	case texType_line0:
		UpdateLine(concentration_line0);
		break;

	case texType_line1:
		UpdateLine(concentration_line1);
		break;

	case texType_spin_clockwise:
		UpdateSpin(texType_spin_clockwise);
		break;

	case texType_spin_anticlockwise:
		UpdateSpin(texType_spin_anticlockwise);
		break;
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
	SetDepthEnable(TRUE);

	// ライティングを無効
	SetLightEnable(FALSE);

	// FALSEが透明化
	SetAlphaTestEnable(FALSE);

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
	material.Diffuse = m_color;
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

	// FALSEが透明化
	SetAlphaTestEnable(TRUE);

	// ライティングを有効に
	SetLightEnable(TRUE);

	// Z比較あり
	SetDepthEnable(TRUE);
}

void UIObject::UpdateNomal(void)
{
}

void UIObject::UpdateFade(void)
{
	if (m_timeCnt < UI_ACTION_TIME)
	{
		m_color.w = ((float)m_timeCnt / (float)UI_ACTION_TIME);
	}
	else if ((m_timeCnt > m_timeLimit - UI_ACTION_TIME) &&
		(m_timeCnt < m_timeLimit))
	{
		m_color.w = 1.0f - (((float)m_timeCnt - (float)(m_timeLimit - UI_ACTION_TIME)) / ((float)UI_ACTION_TIME));
	}
}

void UIObject::UpdateCutIn(void)
{
	switch (m_texType)
	{
	case texType_cutIn_right:
	case texType_cutIn_up:
	case texType_cutIn_up_Update:
		m_vec = 1.0f;

		break;

	case texType_cutIn_left:
	case texType_cutIn_under:
	case texType_cutIn_under_Update:
		m_vec = -1.0f;

		break;
	}

	float t;
	switch (m_texType)
	{
	case texType_cutIn_right:
	case texType_cutIn_left:

		if (m_timeCnt < UI_ACTION_TIME)
		{
			t = (float)m_timeCnt / (float)UI_ACTION_TIME;
			m_pos.x += (t * t) * m_vec * UI_CUTIN_SPEED;
			m_color.w = ((float)m_timeCnt / (float)UI_ACTION_TIME);

		}
		else if ((m_timeCnt > m_timeLimit - UI_ACTION_TIME) &&
			(m_timeCnt < m_timeLimit))
		{
			t = (float)(m_timeCnt - (m_timeLimit - UI_ACTION_TIME)) / (float)UI_ACTION_TIME;
			m_pos.x += (t * t) * m_vec * UI_CUTIN_SPEED;
			m_color.w = 1.0f - (((float)m_timeCnt - (float)(m_timeLimit - UI_ACTION_TIME)) / (float)UI_ACTION_TIME);
		}

		break;

	case texType_cutIn_up:
	case texType_cutIn_under:
	case texType_cutIn_up_Update:
	case texType_cutIn_under_Update:
		if (m_timeCnt < UI_ACTION_TIME)
		{
			t = (float)m_timeCnt / (float)UI_ACTION_TIME;
			m_pos.y += (t * t) * m_vec * UI_CUTIN_SPEED;
			m_color.w = ((float)m_timeCnt / (float)UI_ACTION_TIME);

		}
		else if ((m_timeCnt > m_timeLimit - UI_ACTION_TIME) &&
			(m_timeCnt < m_timeLimit))
		{
			t = (float)(m_timeCnt - (m_timeLimit - UI_ACTION_TIME)) / (float)UI_ACTION_TIME;
			m_pos.y += (t * t) * m_vec * UI_CUTIN_SPEED;
			m_color.w = 1.0f - (((float)m_timeCnt - (float)(m_timeLimit - UI_ACTION_TIME)) / (float)UI_ACTION_TIME);
		}

		break;
	}
}

void UIObject::UpdateZoomIn(void)
{
	if (m_timeCnt < UI_ACTION_TIME)
	{
		m_fWidth = m_fWidthMax * ((float)m_timeCnt / (float)UI_ACTION_TIME);
		m_fHeight = m_fHeightMax * ((float)m_timeCnt / (float)UI_ACTION_TIME);

		if (m_texType == texType_zoomIn_rot)
		{
			m_rot += UI_ROT_SPEED;
		}
	}
	else if ((m_timeCnt > m_timeLimit - UI_ACTION_TIME) &&
		(m_timeCnt < m_timeLimit))
	{
		m_fWidth = m_fWidthMax * (1.0f - ((float)m_timeCnt - (float)(m_timeLimit - UI_ACTION_TIME)) / (float)UI_ACTION_TIME);
		m_fHeight = m_fHeightMax * (1.0f - ((float)m_timeCnt - (float)(m_timeLimit - UI_ACTION_TIME)) / (float)UI_ACTION_TIME);

		if (m_texType == texType_zoomIn_rot)
		{
			m_rot -= UI_ROT_SPEED;
		}

		if (m_fWidth < 10.0f)
		{
			m_isUse = FALSE;
		}
	}
	else if(m_timeCnt == UI_ACTION_TIME)
	{
		m_fWidth = m_fWidthMax;
		m_fHeight = m_fHeightMax;
		m_rot = 0.0f;
	}

}

void UIObject::UpdateTransition(void)
{
	m_pos.x += UI_TRANSITION_SPEED;
}

void UIObject::UpdateZoomInOut(void)
{
	if ((m_timeCnt > UI_ACTION_TIME) && (m_timeCnt < m_timeLimit - UI_ACTION_TIME))
	{
		if (m_timeCnt % UI_UPDATE_SWITCH == 0) m_updateVec *= -1.0f;

		m_fWidth += m_updateVec * (UI_UPDATE_ZOOM_SPEED * (m_fWidthMax));
		m_fHeight += m_updateVec * (UI_UPDATE_ZOOM_SPEED * (m_fHeightMax));
	}
}

void UIObject::UpdateLine(int type)
{
	switch (type)
	{
	case concentration_line0:
		if ((m_timeCnt % 6) > 3) m_color.w = 1.0f;
		else m_color.w = 0.0f;

		break;

	case concentration_line1:
		if ((m_timeCnt % 6) > 3) m_color.w = 0.0f;
		else m_color.w = 1.0f;

		break;
	}
}

void UIObject::UpdateSpring(void)
{
	if(m_time < 1.0f) m_time += 0.1f;

	if (m_springStartY < m_pos.y)
	{
		m_springSpeed = -UI_UPDATE_SPRING_MAX_SPEED;
	}

	m_springSpeed += UI_UPDATE_SPRING_DOWN_SPEED;
	m_pos.y += m_springSpeed;

}

void UIObject::UpdateSpin(int type)
{
	switch (type)
	{
	case texType_spin_clockwise:
		m_rot += UI_UPDATE_SPIN_MAX_SPEED;
		break;

	case texType_spin_anticlockwise:
		m_rot -= UI_UPDATE_SPIN_MAX_SPEED;
		break;
	}
}


