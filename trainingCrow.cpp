#include "trainingCrow.h"
#include "input.h"
#include "TrainingCrowManager.h"
#include "texManager.h"

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
			if (m_speed < MAX_SQUAT_SPEED)
			{
				m_speed += ADD_SQUAT_SPEED;
			}
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
		else if(this->GetGod()->GetTrainingCrowManager()->GetSuccess())
		{	// 成功
			m_time = 0.0f;
			m_MorphingType = 0;
			m_waitCount++;

			this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(telop_bonusChance, texType_zoomIn_rot, XMFLOAT3(480.0f, 400.0f, 0.0f), 5);

			if (m_waitCount == WAIT_SQUAT_TIME * 4 - TRANSITION_HALF_TIME)
			{
				this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
					trandition_crow, texType_tansition, XMFLOAT3( -TRANSITION_WIDTH, 270.0f, 0.0f), 4);
			}

			if (m_waitCount > WAIT_SQUAT_TIME * 4)
			{
				this->GetGod()->GetTrainingCrowManager()->SetIsSpeedUp(FALSE);
				this->GetGod()->GetTrainingCrowManager()->SetBonusStart();
				m_waitCount = 0;
				m_speed = MIN_SQUAT_SPEED;
				m_count = 0;
			}
		}
		else if (this->GetGod()->GetTrainingCrowManager()->GetIsSpeedUp())
		{	// 失敗
			m_time = 0.0f;
			m_MorphingType = 1;
			m_waitCount++;

			if (!GetGod()->GetTrainingCrowManager()->GetFalseTelop())
			{
				GetGod()->GetTrainingCrowManager()->SetFalseTelop(TRUE);

				this->GetGod()->GetTexManager()->GetUIManager()->SetTexture(
					telop_thigh, texType_cutIn_up, XMFLOAT3(744.0f, 20.0f, 0.0f), 4);
			}

			if (m_waitCount > WAIT_SQUAT_TIME * 4)
			{
				this->GetGod()->GetTrainingCrowManager()->SetIsSpeedUp(FALSE);
				m_waitCount = 0;
				m_speed = MIN_SQUAT_SPEED;
				m_count = 0;
			}
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
