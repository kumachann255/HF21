#include "bonusHousing.h"
#include "input.h"

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
			if (m_MorphingType == 1) m_time += 0.08f;
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
	if(!m_isMove) m_isMove = TRUE;
	else if (m_isMove && !m_isVibration)
	{
		m_isVibration = TRUE;
		if (m_MorphingType < m_MorphingTypeMax - 2)
		{
			m_MorphingType++;
			m_time = 0.0f;
		}
	}
	else
	{
		m_isVibration = FALSE;
	}
}
