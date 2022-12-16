//=============================================================================
//
// �N�G�X�g�{�[�h���� [QuestBoard.cpp]
// Author : ������n
//
//=============================================================================
#include "QuestBoard.h"
#include "Roller.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	BOARD_ROTATE_SPEED	(0.001f)		// ��]���x
#define	BOARD_SCL			(3.0f)			// �傫��
#define	ROLLER_RADIUS		(85.0f)			// ���[���[�̔��a


//=============================================================================
// �R���X�g���N�^�[
//=============================================================================
QuestBoard::QuestBoard(std::string name , XMFLOAT3 pos, XMFLOAT3 rot)
{

	pLampManager = new LampManager;
	m_prefab = new Prefab;
	m_prefab->SetModel(name);
	XMFLOAT3 scl = { BOARD_SCL, BOARD_SCL, BOARD_SCL };

	m_prefab->SetPos(pos);
	m_prefab->SetRot(rot);
	m_prefab->SetScl(scl);

	SetIsUse(TRUE);
}

//=============================================================================
// �f�X�g���N�^�[
//=============================================================================
QuestBoard::~QuestBoard()
{
	if (m_prefab) {
		delete m_prefab;
	}

	if (pLampManager) {
		delete pLampManager;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void QuestBoard::Update(void)
{

	XMFLOAT3 rot = { GetRot().x, 0.0f, 0.0f };
	rot.x += ROTATE_SPEED;
	SetRot(rot);
	if (rot.x >= XM_2PI)	rot.x = 0.0f;

	pLampManager->Update();
}


//=============================================================================
// �`�揈��
//=============================================================================
void QuestBoard::Draw(XMMATRIX WorldMatrix)
{

	if (!GetIsUse())	return;

	SetCullingMode(CULL_MODE_BACK);

	SetDepthEnable(TRUE);

	SetBlendState(BLEND_MODE_NONE);

	// ���[���h�}�g���N�X����
	XMMATRIX mtxWorld = GetWorldMatrix(m_prefab->GetPos(), m_prefab->GetRot(), m_prefab->GetScl());

	// �v���n�u(���[�J�����W)�Ƀ��[���h�}�g���N�X��������
	mtxWorld = XMMatrixMultiply(mtxWorld, WorldMatrix);

	// ���W�����o��
	XMFLOAT3 pos = { mtxWorld.r[3].m128_f32[0], 
					 mtxWorld.r[3].m128_f32[1], 
					 mtxWorld.r[3].m128_f32[2] };

	SetPos(pos);

	//XMVECTOR r[4];
	//struct
	//{
	//	float _11, _12, _13, _14;
	//	float _21, _22, _23, _24;
	//	float _31, _32, _33, _34;
	//	float _41, _42, _43, _44;
	//};
	//float m[4][4];


	SetWorldMatrix(&mtxWorld);	// �V�F�[�_�[�Ƀf�[�^�𑗂�

	DrawModel(m_prefab->GetModel());

	SetBlendState(BLEND_MODE_ALPHABLEND);
}
