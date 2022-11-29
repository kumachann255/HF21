#include "trainingCrowBench.h"
#include "TrainingCrowManager.h"

void TrainingCrowBench::Update()
{
	if (this->GetGod()->GetTrainingCrowManager()->GetIsSpeedUp())
	{
		if(m_speed < MAX_BENCH_SPEED) m_speed += ADD_BENCH_SPEED;
		else
		{
			m_count++;
		}
	}
	else
	{
		m_speed = BENCH_SPEED;
		m_count = 0;
	}

	if ((GetPos().y < m_wing_Pos.y) || (GetPos().y - BENCH_MAX_HEIGHT > m_wing_Pos.y))
	{
		m_vec *= -1.0f;
	}

	if (m_count < MAX_BENCH_MAXSPEED_TIME)
	{
		m_wing_Pos.y += m_speed * m_vec;
		m_barbell_Pos.y += m_speed * m_vec;
	}
	else
	{	// ����
		m_wing_Pos.y = GetPos().y;
		m_barbell_Pos.y = GetPos().y;
	}
	//else
	//{	// ���s
	//	m_wing_Pos.y = GetPos().y - BENCH_MAX_HEIGHT;
	//	m_barbell_Pos.y = GetPos().y - BENCH_MAX_HEIGHT;
	//}

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
