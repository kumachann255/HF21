#pragma once
#include "main.h"
#include "object.h"

class EndingStage : public Object
{
private:


public:
	EndingStage() {
		m_prefab = new Prefab;
		m_prefab->SetModel("stage.obj");

		XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
		XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
		XMFLOAT3 scl = { 1.0f, 1.0f, 1.0f };

		SetPos(pos);
		SetRot(rot);
		SetScl(scl);

	};
	~EndingStage() { delete m_prefab; };
};