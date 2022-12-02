#pragma once
#include "main.h"
#include "object.h"

#define ENDING_SUM_LEN	(100.0f)
#define ENDING_SUM_ROT_SPEED	(0.)

class EndingSun : public Object
{
private:
	float m_len = ENDING_SUM_LEN;

public:
	EndingSun() {
		m_prefab = new Prefab;
		m_prefab->SetModel("sunset.obj");

		XMFLOAT3 pos = { 0.0f, 0.0f, 100.0f };
		XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
		XMFLOAT3 scl = { 1.0f, 1.0f, 1.0f };

		SetPos(pos);
		SetRot(rot);
		SetScl(scl);

	};
	~EndingSun() { delete m_prefab; };

	void Update();




};