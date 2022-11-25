#include "trainingCrowBench.h"

void TrainingCrowBench::Update()
{
	if ((GetPos().y < m_wing_Pos.y) || (GetPos().y - BENCH_MAX_HEIGHT > m_wing_Pos.y))
	{
		m_vec *= -1.0f;
	}

	m_wing_Pos.y += BENCH_SPEED * m_vec;
	m_barbell_Pos.y += BENCH_SPEED * m_vec;

}

void TrainingCrowBench::Draw()
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
		XMFLOAT3 pos = m_wing_Pos;
		pos.y += BENCH_Y_OFFSET;
		// ���[���h�}�g���N�X����
		XMMATRIX mtxWorld = GetWorldMatrix(pos, GetRot(), GetScl());

		// �v���n�u(���[�J�����W)�Ƀ��[���h�}�g���N�X��������
		mtxWorld = XMMatrixMultiply(m_prefabWing->GetMtxWorld(), mtxWorld);

		SetWorldMatrix(&mtxWorld);	// �V�F�[�_�[�Ƀf�[�^�𑗂�

		DrawModel(m_prefabWing->GetModel());
	}

	// �o�[�x���̕`��
	{
		XMFLOAT3 pos = m_barbell_Pos;
		pos.y += BENCH_Y_OFFSET;
		// ���[���h�}�g���N�X����
		XMMATRIX mtxWorld = GetWorldMatrix(pos, GetRot(), GetScl());

		// �v���n�u(���[�J�����W)�Ƀ��[���h�}�g���N�X��������
		mtxWorld = XMMatrixMultiply(m_prefabbarbell->GetMtxWorld(), mtxWorld);

		SetWorldMatrix(&mtxWorld);	// �V�F�[�_�[�Ƀf�[�^�𑗂�

		DrawModel(m_prefabbarbell->GetModel());
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
