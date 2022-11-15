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

}
