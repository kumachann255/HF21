#include "housing.h"

Housing::Housing()
{
	m_prefab = new Prefab;
	m_prefab->SetModel("model_slot.obj");

	XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 scl = { 1.0f, 1.0f, 1.0f };


	SetPos(pos);
	SetRot(rot);
	SetScl(scl);


	m_resultColor[0] = { 0.7f, 0.2f, 0.2f, 1.0f };
	m_resultColor[1] = { 0.2f, 0.2f, 0.7f, 1.0f };
	m_resultColor[2] = { 0.2f, 0.7f, 0.2f, 1.0f };
	m_resultColor[3] = { 0.7f, 0.7f, 0.2f, 1.0f };
	m_resultColor[4] = { 0.2f, 0.7f, 0.7f, 1.0f };
	m_resultColor[5] = { 0.7f, 0.2f, 0.7f, 1.0f };

	m_resetColor[0] = { 0.753f, 0.753f, 0.878f, 1.0f };
	m_resetColor[1] = { 1.0f, 0.6f, 0.8f, 1.0f };
	m_resetColor[2] = { 0.458f, 0.819f, 1.0f, 1.0f };
	m_resetColor[3] = { 1.0f, 0.568f, 0.0f, 1.0f };

	m_resetColorTemp = { 1.0f, 0.6f, 0.8f, 1.0f };

	this->GetPrefab()->SetColor(m_resetColor[0]);
}

void Housing::Update(void)
{
	if (m_isRainbow)
	{	// 色のモーフィング
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
	else if(m_time < 1.0f)
	{
		XMFLOAT4 color;
		int next = (m_nowSeason + 1) % 4;

		m_time += SPEED_COLOR;

		color.x = m_resetColor[m_nowSeason].x + (m_resetColor[next].x - m_resetColor[m_nowSeason].x) * m_time;
		color.y = m_resetColor[m_nowSeason].y + (m_resetColor[next].y - m_resetColor[m_nowSeason].y) * m_time;
		color.z = m_resetColor[m_nowSeason].z + (m_resetColor[next].z - m_resetColor[m_nowSeason].z) * m_time;
		color.w = 1.0f;

		m_resetColorTemp = color;
		this->GetPrefab()->SetColor(color);
	}
}

void Housing::NestSeason(void)
{
	m_time = 0.0f;
	m_nowSeason = (m_nowSeason + 1) % 4;
}
