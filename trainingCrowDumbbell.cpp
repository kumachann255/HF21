#include "trainingCrowDumbbell.h"

void TrainingCrowDumbbell::Update()
{
	if ((GetRot().x < m_wing_Rot.x) || (GetRot().x - DUMBBELL_MAX_ROT > m_wing_Rot.x))
	{
		m_vec *= -1.0f;
	}

	m_wing_Rot.x += DUMBBELL_SPEED * m_vec;
}

void TrainingCrowDumbbell::Draw()
{
	if (!m_prefab) return;

	SetDepthEnable(TRUE);

	// ���X�^���C�U�ݒ�
	SetCullingMode(CULL_MODE_NONE);
	//SetBlendState(BLEND_MODE_ADD);

	// ���̂̕`��
	{
		// ���[���h�}�g���N�X����
		XMMATRIX mtxWorld = GetWorldMatrix(GetPos(), GetRot(), GetScl());

		// �v���n�u(���[�J�����W)�Ƀ��[���h�}�g���N�X��������
		mtxWorld = XMMatrixMultiply(m_prefab->GetMtxWorld(), mtxWorld);

		SetWorldMatrix(&mtxWorld);	// �V�F�[�_�[�Ƀf�[�^�𑗂�

		DrawModel(m_prefab->GetModel());
	}

	// �H�̕`��
	{
		// ���[���h�}�g���N�X����
		XMMATRIX mtxWorld = GetWorldMatrix(m_wing_Pos, m_wing_Rot, GetScl());

		// �v���n�u(���[�J�����W)�Ƀ��[���h�}�g���N�X��������
		mtxWorld = XMMatrixMultiply(m_prefabWing->GetMtxWorld(), mtxWorld);

		SetWorldMatrix(&mtxWorld);	// �V�F�[�_�[�Ƀf�[�^�𑗂�

		DrawModel(m_prefabWing->GetModel());
	}

	// �x���`�̕`��
	{
		// ���[���h�}�g���N�X����
		XMMATRIX mtxWorld = GetWorldMatrix(GetPos(), GetRot(), GetScl());

		// �v���n�u(���[�J�����W)�Ƀ��[���h�}�g���N�X��������
		mtxWorld = XMMatrixMultiply(m_prefabBench->GetMtxWorld(), mtxWorld);

		SetWorldMatrix(&mtxWorld);	// �V�F�[�_�[�Ƀf�[�^�𑗂�

		DrawModel(m_prefabBench->GetModel());
	}
}
