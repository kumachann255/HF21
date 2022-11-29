#include "trainingCrow.h"
#include "input.h"
#include "TrainingCrowManager.h"

void TrainingCrowSquat::Update()
{
	// モーフィングの処理
	{
		int after, brfore;

		// モーフィングモデルの番号調整
		if (m_MorphingType == 0)
		{
			after = 1;
			brfore = 0;
		}
		else if (m_MorphingType == 1)
		{
			after = 0;
			brfore = 1;
		}

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

		if (this->GetGod()->GetTrainingCrowManager()->GetIsSpeedUp())
		{
			if(m_speed < MAX_SQUAT_SPEED) m_speed += ADD_SQUAT_SPEED;
			else
			{
				m_count++;
			}
		}
		else
		{
			m_speed = MIN_SQUAT_SPEED;
			m_count = 0;
		}

		if ((m_time < 1.0f) && (m_count < MAX_SQUAT_MAXSPEED_TIME))
		{
			m_time += m_speed;

			if (m_time > 1.0f)
			{
				m_time = 0.0f;
				m_MorphingType++;
				m_MorphingType %= m_MorphingTypeMax;
			}
		}
		else
		{	// 成功
			m_time = 0.0f;
			m_MorphingType = 0;
		}
		//else
		//{	// 失敗
		//	m_time = 0.0f;
		//	m_MorphingType = 1;
		//}

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
