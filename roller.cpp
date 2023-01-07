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
#define	ROLLER_SCL			(10.0f)			// ���[���[�̑傫��


//=============================================================================
// ���[���[�N���X
//=============================================================================

Roller::Roller()
{
	// ���f���̐ݒ�
	m_prefab = new Prefab;
	//m_prefab->SetModel(g_TextureName[0]);

	// ���[�J���ݒ�
	XMFLOAT3 pos = { -50.0f, 0.0f, 0.0f };
	XMFLOAT3 rot = { 0.0f, 0.0f , 0.0f };
	XMFLOAT3 scl = { ROLLER_SCL*1.5, ROLLER_SCL, ROLLER_SCL };

	m_prefab->SetPos(pos);
	m_prefab->SetRot(rot);
	m_prefab->SetScl(scl);

	//SetIsUse(TRUE);

}

Roller::~Roller()
{
	if (m_prefab) { delete m_prefab; }
}



void Roller::Update(void)
{
	if (GetIsUse())
	{
		// ���[�J����]
		static XMFLOAT3 rot = { 0.0f,XMConvertToRadians(225.0f), 0.0f };

		rot.x += ROTATE_SPEED;

		if (rot.x > XM_PI * 2)
		{
			rot.x = 0.0f;
		}

		m_prefab->SetRot(rot);
	}

}

void Roller::Draw(void)
{
	if (!GetIsUse()) return;

	SetDepthEnable(TRUE);

	// ���X�^���C�U�ݒ�
	SetCullingMode(CULL_MODE_BACK);

	XMFLOAT3 rot = { 0.0f, 0.0f , 0.0f };

	// ���[���h�}�g���N�X����
	XMMATRIX mtxWorld = GetWorldMatrix(GetPos(), rot, GetScl());

	// �v���n�u(���[�J�����W)�Ƀ��[���h�}�g���N�X��������
	mtxWorld = XMMatrixMultiply(m_prefab->GetMtxWorld(), mtxWorld);

	SetWorldMatrix(&mtxWorld);	// �V�F�[�_�[�Ƀf�[�^�𑗂�

	DrawModel(m_prefab->GetModel());

}
