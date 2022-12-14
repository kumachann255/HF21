#include "bonusDrumh.h"

BonusDrum::BonusDrum()
{
	m_prefab = new Prefab;
	m_prefab->SetModel("model_slot_x5drum.obj");

	XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 scl = { 1.0f, 1.0f, 1.0f };

	SetPos(pos);
	SetRot(rot);
	SetScl(scl);

	m_offset = OFFSET / 3;
	m_colorMax = Bonusdrum3D_max;
	m_speedMax = MAX_SPEED_BONUS;
	m_speedUpValue = SPEED_UP_VALUE * 2.0f;

	m_resultMax = 5;

	SetBonus();
}

