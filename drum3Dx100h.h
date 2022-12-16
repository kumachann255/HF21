#pragma once
#include "drum3D.h"


class Drum3Dx100 : public Drum3D
{
private:

public:
	Drum3Dx100() {
			m_prefab = new Prefab;
			m_prefab->SetModel("model_slot_rainbowdrum_x5.obj");

			XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
			XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
			XMFLOAT3 scl = { 1.0f, 1.0f, 1.0f };

			SetPos(pos);
			SetRot(rot);
			SetScl(scl);
	}
};


class Drum3Dx1050 : public Drum3D
{
private:

public:
	Drum3Dx1050() {
		m_prefab = new Prefab;
		m_prefab->SetModel("model_slot_x1-2-3drum.obj");

		XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
		XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
		XMFLOAT3 scl = { 1.0f, 1.0f, 1.0f };

		SetPos(pos);
		SetRot(rot);
		SetScl(scl);
	}
};