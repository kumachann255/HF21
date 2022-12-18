#include "bonusBGh.h"

#define BONUSBG_ROT_SPEED	(0.006f)

BonusBG::BonusBG()
{
	m_prefab = new Prefab;
	m_prefab->SetModel("model_BG.obj");

	XMFLOAT3 pos = { 0.0f, 0.0f, 100.0f };
	XMFLOAT3 rot = { 0.0f, -1.74f, 0.0f };
	XMFLOAT3 scl = { 2.0f, 2.0f, 2.0f };

	SetPos(pos);
	SetRot(rot);
	SetScl(scl);

}

void BonusBG::Update()
{
	XMFLOAT3 rot = GetRot();
	rot.x += BONUSBG_ROT_SPEED;
	SetRot(rot);
}