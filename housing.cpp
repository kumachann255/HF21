#include "housing.h"

Housing::Housing()
{
	m_prefab = new Prefab;
	m_prefab->SetModel("model_slot.obj");

	XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 scl = { 1.0f, 1.0f, 1.0f };

	this->GetPrefab()->SetColor(m_resetColor);

	SetPos(pos);
	SetRot(rot);
	SetScl(scl);

	m_resultColor[0] = { 0.7f, 0.2f,0.2f,1.0f };
	m_resultColor[1] = { 0.2f, 0.2f,0.7f,1.0f };
	m_resultColor[2] = { 0.2f, 0.7f,0.2f,1.0f };
	m_resultColor[3] = { 0.7f, 0.7f,0.2f,1.0f };
	m_resultColor[4] = { 0.2f, 0.7f,0.7f,1.0f };
	m_resultColor[5] = { 0.7f, 0.2f,0.7f,1.0f };

}

void Housing::Update(void)
{
	if (!m_isRainbow) return;

	// 色のモーフィング
	{
		int before = m_colorType;
		int after = (m_colorType + 1) % m_resultNum;

		m_colorTime += COLOR_SPEED;

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
}
