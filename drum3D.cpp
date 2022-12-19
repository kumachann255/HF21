#include "drum3D.h"
#include "input.h"


Drum3D::Drum3D()
{
	m_prefab = new Prefab;
	m_prefab->SetModel("model_slot_paintdrum.obj");

	XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 scl = { 1.0f, 1.0f, 1.0f };

	SetPos(pos);
	SetRot(rot);
	SetScl(scl);
}

void Drum3D::Update(void)
{
	XMFLOAT3 rot = this->GetRot();

	if (m_move)
	{
		rot.x *= -100.0f;
		// 正規化
		rot.x = (float)((int)(rot.x) % 614) / 100.0f;

		m_speed += m_speedUpValue;
		if (m_speed > m_speedMax) m_speed = m_speedMax;

		rot.x += m_speed;
		rot.x *= -1.0f;
	}
	else
	{
		rot.x += (m_result - rot.x) * 0.1f;
	}

	this->SetRot(rot);
}

void Drum3D::Stop(void)
{
	// とりあえずビタッと止める
	m_move = false;
	m_speed = 0.0f;

	// 出目をセット
	this->SetResult();
}

void Drum3D::SpinStart(void)
{
	m_move = true;
}

void Drum3D::SetResult(void)
{
	XMFLOAT3 rot = this->GetRot();

	rot.x *= -100.0f;

	// 正規化
	rot.x = (float)((int)(rot.x) % 614) / 100.0f;

	float temp = 0.0f;

	for (int i = 0; i < m_resultMax; i++)
	{
		if ((rot.x < temp + m_resultRadianOffset / 2) && (rot.x > temp - m_resultRadianOffset / 2))
		{
			m_color = i % m_colorMax;
			m_result = i * m_resultRadian;
			m_result *= -1.0f;
			m_result -= m_offset;
			return;
		}

		temp += m_resultRadian;
	}
}

void Drum3D::SetRainbowModel(void)
{
	m_prefab->SetModel("model_slot_rainbowdrum.obj");
}

void Drum3D::SetRainbowModelL(void)
{
	m_prefab->SetModel("model_slot_rainbowdrum_x5.obj");
}

void Drum3D::ResetRainbowModel(void)
{
	m_prefab->SetModel("model_slot_paintdrum.obj");
}

void Drum3D::ResetRainbowModelL(void)
{
	m_prefab->SetModel("model_slot_x1-2-3drum.obj");
}

void Drum3D::SetNormal(void)
{
	m_resultMax = MAX_RESULT_NORMAL;
	m_resultRadian = RADIAN9;
	m_resultRadianOffset = RADIAN9;
	m_offset = OFFSET;
	m_speedUpValue = SPEED_UP_VALUE;
}

void Drum3D::SetBonus(void)
{
	m_resultMax = MAX_RESULT_BONUS;
	m_resultRadian = RADIAN10;
	m_resultRadianOffset = RADIAN10 * 2.0f;
	m_offset = OFFSET * 2.0f;
	m_speedUpValue = SPEED_UP_VALUE * 2.0f;
}

