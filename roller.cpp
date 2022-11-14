//=============================================================================
//
// ���[���[���� [roller.cpp]
// Author : ������n
//
//=============================================================================

#include "main.h"
#include "roller.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	ROTATE_SPEED		(0.01f)			// ��]���x
#define	ROLLER_SCL			(10.0f)			// ���[���[�̑傫��


Roller::Roller(God *god) :GodObject(god)
{
	// ���f���̐ݒ�
	m_prefab = new Prefab;
	m_prefab->SetModel("model_map.obj");

	// ���[�J���ݒ�
	XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 rot = { 0.0f, 0.0f , 0.0f };
	XMFLOAT3 scl = { ROLLER_SCL, ROLLER_SCL, ROLLER_SCL };

	m_prefab->SetPos(pos);
	m_prefab->SetRot(rot);
	m_prefab->SetScl(scl);

}

Roller::~Roller()
{
	if (m_prefab) { delete m_prefab; }
}



void Roller::Update(void)
{

	// ���[�J����]
	static XMFLOAT3 rot = { 0.0f,XMConvertToRadians(45.0f), 0.0f };
	rot.x -= ROTATE_SPEED;

	if (rot.x < -XM_PI)
	{
		rot.x += XM_PI * 2.0f;
	}

	m_prefab->SetRot(rot);

}
