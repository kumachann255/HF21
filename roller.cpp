#include "main.h"
#include "roller.h"

void Roller::Update(void)
{
	// ワールド座標回転
	static XMFLOAT3 rot = { 0.0f,0.0f, 0.0f };
	rot.y += XMConvertToRadians(1.0f);
	this->SetRot(rot);

	// ローカル回転
	XMFLOAT3 rot2 = { XMConvertToRadians(90.0f),XMConvertToRadians(-45.0f), 0.0f };
	this->m_prefab->SetRot(rot2);	

}
