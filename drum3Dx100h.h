#pragma once
#include "drum3D.h"


class Drum3Dx100 : public Drum3D
{
private:

public:
	Drum3Dx100() {
			m_prefab = new Prefab;
			m_prefab->SetModel("model_slot_x100drum.obj");

			XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
			XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
			XMFLOAT3 scl = { 1.0f, 1.0f, 1.0f };

			SetPos(pos);
			SetRot(rot);
			SetScl(scl);
	}
};