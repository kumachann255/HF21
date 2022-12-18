#include "bonusHousing.h"
#include "input.h"
#include <time.h>
#include "texManager.h"
#include "sound.h"

#define MAX_BONUS_HOUSING_LOOP	(2)

BonusHousing::BonusHousing()
{
	m_prefab = new Prefab;
	m_prefab->SetModelMorphing("model_slot_crow03.obj");

	m_MorphingTypeMax = MAX_HOUSING_MOVE;

	m_Squat_Vertex = new MODEL[MAX_HOUSING_MOVE];

	// モーフィングするオブジェクトの読み込み
	LoadObj("data/MODEL/model_slot_crow03.obj", &m_Squat_Vertex[0]);
	LoadObj("data/MODEL/model_slot_crow02.obj", &m_Squat_Vertex[1]);
	LoadObj("data/MODEL/model_slot_crow01.obj", &m_Squat_Vertex[2]);

	// 中身を配列として使用できるように仕様変更
	m_pVertex = new VERTEX_3D[m_Squat_Vertex[0].VertexNum];

	// 差分(途中経過)の初期化
	for (int i = 0; i < m_Squat_Vertex[0].VertexNum; i++)
	{
		m_pVertex[i].Position = m_Squat_Vertex[0].VertexArray[i].Position;
		m_pVertex[i].Diffuse = m_Squat_Vertex[0].VertexArray[i].Diffuse;
		m_pVertex[i].Normal = m_Squat_Vertex[0].VertexArray[i].Normal;
		m_pVertex[i].TexCoord = m_Squat_Vertex[0].VertexArray[i].TexCoord;
	}

	for (int i = 0; i < 3; i++)
	{
		m_resultColor[i] = { 1.0f, 1.0f, 1.0f, 1.0f };
	}
	m_ansColor = { 1.0f, 1.0f, 1.0f, 1.0f };

	XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 scl = { 1.0f, 1.0f, 1.0f };
	SetPos(pos);
	SetRot(rot);
	SetScl(scl);
}

void BonusHousing::Update()
{
	if (GetKeyboardTrigger(DIK_H))
	{
		SetGoMorphing();
	}
	if (GetKeyboardTrigger(DIK_N))
	{
		m_isMove = FALSE;
		m_MorphingType = 0;
		m_time = 0.0f;
	}

	// 色のモーフィング
	if (m_resultNum > 0)
	{
		int before = m_colorType;
		int after = (m_colorType + 1) % m_resultNum;

		m_colorTime += HOUSING_COLOR_SPEED;
		if(m_resultNum >= 3) m_colorTime += MAX_HOUSING_COLOR_SPEED;

		if (m_colorTime > 1.0f)
		{
			m_colorTime = 0.0f;
			m_colorType++;
			m_colorType %= m_resultNum;
		}

		m_ansColor.x = m_resultColor[before].x + ((m_resultColor[after].x - m_resultColor[before].x) * m_colorTime);
		m_ansColor.y = m_resultColor[before].y + ((m_resultColor[after].y - m_resultColor[before].y) * m_colorTime);
		m_ansColor.z = m_resultColor[before].z + ((m_resultColor[after].z - m_resultColor[before].z) * m_colorTime);

		this->GetPrefab()->SetColor(m_ansColor);
	}


	// モーフィングの処理
	if (m_isMove)
	{
		int after, brfore;

		// モーフィングモデルの番号調整
		after = m_MorphingType + 1;
		brfore = m_MorphingType;

		// モーフィング処理
		for (int p = 0; p < m_Squat_Vertex[0].VertexNum; p++)
		{
			m_pVertex[p].Position.x = m_Squat_Vertex[after].VertexArray[p].Position.x - m_Squat_Vertex[brfore].VertexArray[p].Position.x;
			m_pVertex[p].Position.y = m_Squat_Vertex[after].VertexArray[p].Position.y - m_Squat_Vertex[brfore].VertexArray[p].Position.y;
			m_pVertex[p].Position.z = m_Squat_Vertex[after].VertexArray[p].Position.z - m_Squat_Vertex[brfore].VertexArray[p].Position.z;

			m_pVertex[p].Position.x *= m_time;
			m_pVertex[p].Position.y *= m_time;
			m_pVertex[p].Position.z *= m_time;

			m_pVertex[p].Position.x += m_Squat_Vertex[brfore].VertexArray[p].Position.x;
			m_pVertex[p].Position.y += m_Squat_Vertex[brfore].VertexArray[p].Position.y;
			m_pVertex[p].Position.z += m_Squat_Vertex[brfore].VertexArray[p].Position.z;
		}

		if (m_isVibration)
		{
			m_time += 0.04f * m_vec;
			if ((m_time < 0.0f) || (m_time > 0.1f))
			{
				m_vec *= -1.0f;
			}
			if (m_time < 0.0f) m_time = 0.0f;
			
		}
		else if (m_time < 1.0f)
		{
			m_time += 0.03f;
			if (m_MorphingType == 1)
			{
				if (m_loopNum == MAX_BONUS_HOUSING_LOOP) m_time -= 0.01f;
				else m_time += 0.015f;

				if ((m_time > 1.0f) && (m_loopNum < MAX_BONUS_HOUSING_LOOP))
				{
					m_time = 0.0f;
					m_loopNum++;
					PlaySound(SOUND_LABEL_SE_se_wing_x1);

					if(m_loopNum == MAX_BONUS_HOUSING_LOOP) PlaySound(SOUND_LABEL_SE_se_pkieeen);
				}
			}
		}

		if ((m_time > 1.0f) && (m_loopNum == MAX_BONUS_HOUSING_LOOP))
		{
			m_waitTime++;
		}

		if (m_waitTime == 1)
		{
			m_isHit = TRUE;
			PlaySound(SOUND_LABEL_SE_se_BonusHit);
		}

		if (m_waitTime == MAX_HOUSING_CLEAR_WAIT - TRANSITION_HALF_TIME)
		{
			m_isTransition = TRUE;
		}

		if (m_waitTime > MAX_HOUSING_CLEAR_WAIT)
		{
			ResetMorphing();
		}

		D3D11_SUBRESOURCE_DATA sd;
		ZeroMemory(&sd, sizeof(sd));
		sd.pSysMem = m_pVertex;

		// 頂点バッファに値をセットする
		D3D11_MAPPED_SUBRESOURCE msr;
		GetDeviceContext()->Map(m_prefab->GetModel()->VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
		VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

		// 全頂点情報を毎回上書きしているのはDX11ではこの方が早いからです
		memcpy(pVtx, m_pVertex, sizeof(VERTEX_3D)*m_Squat_Vertex[0].VertexNum);

		GetDeviceContext()->Unmap(m_prefab->GetModel()->VertexBuffer, 0);
	}
}

void BonusHousing::SetGoMorphing()
{
	if (!m_isMove) {
		m_isMove = TRUE;
		PlaySound(SOUND_LABEL_SE_se_wing_x1);
	}
	else if (m_isMove && !m_isVibration)
	{
		m_isVibration = TRUE;
		PlaySound(SOUND_LABEL_SE_se_wing_x6);

		if (m_MorphingType < m_MorphingTypeMax - 2)
		{
			m_MorphingType++;
			m_time = 0.0f;
			PlaySound(SOUND_LABEL_SE_se_wing_x1);
		}
	}
	else
	{
		m_isVibration = FALSE;
	}
}

void BonusHousing::ResetMorphing()
{
	m_MorphingType = 0;
	m_waitTime = 0;
	m_isVibration = FALSE;
	m_isMove = FALSE;
	m_isEnd = TRUE;
	m_loopNum = 0;

	// 差分(途中経過)の初期化
	for (int i = 0; i < m_Squat_Vertex[0].VertexNum; i++)
	{
		m_pVertex[i].Position = m_Squat_Vertex[0].VertexArray[i].Position;
		m_pVertex[i].Diffuse = m_Squat_Vertex[0].VertexArray[i].Diffuse;
		m_pVertex[i].Normal = m_Squat_Vertex[0].VertexArray[i].Normal;
		m_pVertex[i].TexCoord = m_Squat_Vertex[0].VertexArray[i].TexCoord;
	}

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = m_pVertex;

	// 頂点バッファに値をセットする
	D3D11_MAPPED_SUBRESOURCE msr;
	GetDeviceContext()->Map(m_prefab->GetModel()->VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	VERTEX_3D* pVtx = (VERTEX_3D*)msr.pData;

	// 全頂点情報を毎回上書きしているのはDX11ではこの方が早いからです
	memcpy(pVtx, m_pVertex, sizeof(VERTEX_3D)*m_Squat_Vertex[0].VertexNum);

	GetDeviceContext()->Unmap(m_prefab->GetModel()->VertexBuffer, 0);

}

void BonusHousing::SetColor(XMFLOAT4 color)
{
	m_resultColor[m_resultNum] = color;

	m_resultNum++;
	if (m_resultNum == 3)
	{
		m_isTimeStop = TRUE;
	}
}

void BonusHousing::ResetColor(void)
{
	m_colorTime = 0.0f;
	m_resultNum = 0;
	m_colorType = 0; 
	m_time = 0.0f;
	ResetMorphing();

	for (int i = 0; i < 3; i++)
	{
		m_resultColor[i] = { 1.0f, 1.0f, 1.0f, 1.0f };
	}
	m_ansColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	this->GetPrefab()->SetColor(m_ansColor);
}


