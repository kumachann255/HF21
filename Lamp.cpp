//=============================================================================
//
// �����v�Ǘ� [Lamp.cpp]
// Author : ������n
//
//=============================================================================
#include"Lamp.h"
#include "Roller.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	LAMP_ROTATE_SPEED	(0.006f)	// ��]���x
#define	LAMP_SCL			(1.0f)		// �傫��

#define LAMP_LIFE			(90)

//=============================================================================
// �R���X�g���N�^�[
//=============================================================================
Lamp::Lamp()
{
	m_prefab = new Prefab;
	m_prefab->SetModel("model_lamp_red.obj");
	XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 scl = { LAMP_SCL, LAMP_SCL, LAMP_SCL };

	m_prefab->SetPos(pos);
	m_prefab->SetRot(rot);
	m_prefab->SetScl(scl);

}

//=============================================================================
// �f�X�g���N�^�[
//=============================================================================
Lamp::~Lamp()
{
	if (m_prefab) {
		delete m_prefab; 
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Lamp::Update(void)
{
	if (!this->GetIsUse()) return;

	static XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
	rot.x += LAMP_ROTATE_SPEED;
	rot.y += LAMP_ROTATE_SPEED;
	rot.z += 0.00f;
	m_prefab->SetRot(rot);

	if (rot.x >= XM_2PI) {
		rot.x = 0.0f;
		rot.y = 0.0f;
		rot.z = 0.0f;
	}

	if (m_clear)
	{
		m_count++;
		if (m_count > LAMP_LIFE)
		{
			this->SetIsUse(FALSE);
		}
	}
}


//=============================================================================
// �`�揈��
//=============================================================================
void Lamp::Draw(XMMATRIX WorldMatrix)
{
	if (!this->GetIsUse()) return;

	SetCullingMode(CULL_MODE_BACK);

	SetDepthEnable(TRUE);

	SetBlendState(BLEND_MODE_NONE);

	// ���[���h�}�g���N�X����
	XMMATRIX mtxWorld = GetWorldMatrix(m_prefab->GetPos(), m_prefab->GetRot(), m_prefab->GetScl());

	// �v���n�u(���[�J�����W)�Ƀ��[���h�}�g���N�X��������
	mtxWorld = XMMatrixMultiply(mtxWorld, WorldMatrix);

	SetWorldMatrix(&mtxWorld);	// �V�F�[�_�[�Ƀf�[�^�𑗂�

	DrawModel(m_prefab->GetModel());

	SetBlendState(BLEND_MODE_ALPHABLEND);
}
