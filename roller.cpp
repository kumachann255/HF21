//=============================================================================
//
// ローラー処理 [roller.cpp]
// Author : 柏村大地
//
//=============================================================================

#include "main.h"
#include "roller.h"



Roller::Roller()
{
	m_prefab = new Prefab;

	XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 rot = { XMConvertToRadians(90.0f), 0.0f, 0.0f };
	XMFLOAT3 scl = { 10.0f, 10.0f, 10.0f };

	SetPos(pos);
	SetRot(rot);
	SetScl(scl);

}

Roller::~Roller()
{
	if (m_prefab) { delete m_prefab; }
}



void Roller::Update(void)
{
	// ワールド座標回転
	static XMFLOAT3 rot = { 0.0f,0.0f, 0.0f };
	rot.x -= XMConvertToRadians(0.3f);
	this->SetRot(rot);

	// ローカル回転
	XMFLOAT3 rot2 = { 0.0f,XMConvertToRadians(45.0f), 0.0f };
	SetPrefabRot(rot2);

}
