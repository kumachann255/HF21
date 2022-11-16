#include "drum3D.h"
#include "input.h"

#define RADIAN9 (6.14f / 9.0f)
#define OFFSET	(0.25f)

Drum3D::Drum3D()
{
	m_prefab = new Prefab;
	m_prefab->SetModel("model_slot_roll.obj");

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

		m_speed += 0.001f;
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

	for (int i = 0; i < 9; i++)
	{
		if ((rot.x < temp + RADIAN9 / 2) && (rot.x > temp - RADIAN9 / 2))
		{
			m_color = i % 3;
			m_result = i * RADIAN9;
			m_result *= -1.0f;
			m_result -= OFFSET;
			return;
		}

		temp += RADIAN9;
	}
}
