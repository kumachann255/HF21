//=============================================================================
//
// �N�G�X�g�{�[�h���� [QuestBoard.cpp]
// Author : ������n
//
//=============================================================================
#include "QuestBoard.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BOARD_ROTATE_SPEED	(0.001f)		// ��]���x
#define	BOARD_SCL			(0.6f)			// �傫��
#define	ROLLER_RADIUS		(85.0f)			// ���[���[�̔��a


//=============================================================================
// �R���X�g���N�^�[
//=============================================================================
QuestBoard::QuestBoard(std::string name , XMFLOAT3 pos)
{

	m_prefab = new Prefab;
	m_prefab->SetModel(name);

	//XMFLOAT3 rot = { 0.0f, XMConvertToRadians(45.0f), XMConvertToRadians(-30.0f) };
	XMFLOAT3 rot = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 scl = { BOARD_SCL, BOARD_SCL, BOARD_SCL };

	m_prefab->SetPos(pos);
	m_prefab->SetRot(rot);
	m_prefab->SetScl(scl);

	//XMFLOAT4 color = { 1.0f,0.0f,0.0f,1.0f };
	//m_prefab->SetColor(color);
}

//=============================================================================
// �f�X�g���N�^�[
//=============================================================================
QuestBoard::~QuestBoard()
{
	if (m_prefab) {
		delete m_prefab;
		m_prefab = nullptr;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void QuestBoard::Update(void)
{
	//m_time += 0.01f;
	//if (m_time >= XM_2PI)	m_time = 0.0f;

	//m_pos.y = ROLLER_RADIUS * sinf(m_time);
	//m_pos.z = ROLLER_RADIUS * cosf(m_time);
	//m_prefab->SetPos(m_pos);

	//m_rot = { -m_time * 0.25f,XMConvertToRadians(45.0f), XMConvertToRadians(3.0f) };
	//m_prefab->SetRot(m_rot);

}


//=============================================================================
// �`�揈��
//=============================================================================
void QuestBoard::Draw(XMMATRIX WorldMatrix)
{
	SetCullingMode(CULL_MODE_NONE);		//�J�����O�Ȃ�

	SetDepthEnable(TRUE);

	// ���[���h�}�g���N�X����
	XMMATRIX mtxWorld = GetWorldMatrix(m_prefab->GetPos(), m_prefab->GetRot(), m_prefab->GetScl());

	// �v���n�u(���[�J�����W)�Ƀ��[���h�}�g���N�X��������
	mtxWorld = XMMatrixMultiply(mtxWorld, WorldMatrix);

	SetWorldMatrix(&mtxWorld);	// �V�F�[�_�[�Ƀf�[�^�𑗂�

	DrawModel(m_prefab->GetModel());

	SetCullingMode(CULL_MODE_BACK);		//�J�����O��߂�

}
