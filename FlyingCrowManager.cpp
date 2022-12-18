//=============================================================================
//
// �J���[�X�Ǘ����� [FlyingCrowManager.cpp]
// Author : 
//
//=============================================================================
#include "FlyingCrowManager.h"
#include "input.h"
#include "QuestBoardManager.h"
#include "QuestBoard.h"
#include "Lamp.h"
#include "slotManager.h"
#include "sound.h"

#define MAX_CROW_NORMAL		(20)
#define MAX_CROW_RAINBOW	(30)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
FlyingCrowManager::FlyingCrowManager(God *god):GodObject(god)
{
	m_pFlyingCrow = new FlyingCrow[CROWS_MAX];

	for (int i = 0; i < CROWS_MAX; i++)
	{
		m_pFlyingCrow[i].SetIsUse(FALSE);
	}

	m_pFlyingCrow[0].CreateCrow();
	m_pFlyingCrow[0].GetPrefab()->SetModel("model_crow.obj");
}

//=============================================================================
// �f�X�g���N�^�[
//=============================================================================
FlyingCrowManager::~FlyingCrowManager()
{
	// �z��̃f���[�g
	delete[] m_pFlyingCrow;

}

//=============================================================================
// �X�V����
//=============================================================================
void FlyingCrowManager::Update(void)
{

	XMFLOAT3 pos = { 0.0f,0.0f,0.0f };

	QuestBoard **pQuestBoardArray = this->GetGod()->GetQuestBoardManager()->GetBoardArray()->data();
	int count = -1;

	// ���ԃJ���X�̍X�V
	for (int i = 0; i < CROWS_MAX; i++)
	{
		if (this->GetGod()->GetSlotManager()->GetRainbow())
		{
			if (i % MAX_CROW_RAINBOW == 0) count++;
		}
		else
		{
			if (i % MAX_CROW_NORMAL == 0) count++;
		}
		if (count >= 3) count = 2;

		if (m_pFlyingCrow[i].GetIsUse())
		{
			if (m_targetNo[count] == LAMP_TYPE_NONE)
			{
				m_pFlyingCrow[i].SetTargetPos(m_noneTargetPos);
			}
			else
			{
				XMFLOAT3 targetPos = pQuestBoardArray[m_targetNo[count]]->GetPos();
				XMFLOAT3 targetRot = pQuestBoardArray[m_targetNo[count]]->GetRot();

				targetPos.y += cosf(targetRot.x) * m_pFlyingCrow[i].GetOffset().y;
				targetPos.z -= sinf(targetRot.x) * m_pFlyingCrow[i].GetOffset().y;

				targetPos.x += m_pFlyingCrow[i].GetOffset().x;

				m_pFlyingCrow[i].SetTargetPos(targetPos);
			}

			m_pFlyingCrow[i].Update();

			// ���Z�b�g����
			if (m_pFlyingCrow[i].GetTime() >= 1.0f)
			{
				m_pFlyingCrow[i].SetIsUse(FALSE);
				m_pFlyingCrow[i].SetPos(pos);
				m_pFlyingCrow[i].ResetControlPos();

			}
		}
	}

}

//=============================================================================
// �`�揈��
//=============================================================================
void FlyingCrowManager::Draw(void)
{
	SetDepthEnable(TRUE);
	// ���X�^���C�U�ݒ�
	SetCullingMode(CULL_MODE_NONE);
	//SetBlendState(BLEND_MODE_ADD);

	// ���ԃJ���X�̕`�揈��
	for (int i = 0; i < CROWS_MAX; i++)
	{
		if (m_pFlyingCrow[i].GetIsUse())
		{
			// ���[���h�}�g���N�X����
			XMMATRIX mtxWorld = GetWorldMatrix(m_pFlyingCrow[i].GetPos(), m_pFlyingCrow[i].GetRot(), m_pFlyingCrow[i].GetScl());

			// �v���n�u(���[�J�����W)�Ƀ��[���h�}�g���N�X��������
			mtxWorld = XMMatrixMultiply(m_pFlyingCrow[0].GetPrefab()->GetMtxWorld(), mtxWorld);

			SetWorldMatrix(&mtxWorld);	// �V�F�[�_�[�Ƀf�[�^�𑗂�

			// 0�Ԗڂ̃��f���ɐF�f�[�^�𖈉�㏑��
			m_pFlyingCrow[0].GetPrefab()->SetColor(m_pFlyingCrow[i].GetColor());
			
			// �`�悷�郂�f����0�Ԗڂ̃��f�������ɕ`��
			DrawModel(m_pFlyingCrow[0].GetPrefab()->GetModel());
		}
	}
}

//=============================================================================
// ��������
//=============================================================================
void FlyingCrowManager::SetShotCrows(XMFLOAT4 color ,int colorType, int num)
{	
	QuestBoard **pQuestBoardArray = this->GetGod()->GetQuestBoardManager()->GetBoardArray()->data();

	int count = 1;

	PlaySound(SOUND_LABEL_SE_se_crow_flap_04); // �J���[�X����
	PlaySound(SOUND_LABEL_SE_se_crow_cry_01);  // �J���[�X�̖���

	XMFLOAT3 targetPos;

	for (int i = 0; i < CROWS_MAX; i++)
	{
		m_targetNo[num] = colorType;

		if (!m_pFlyingCrow[i].GetIsUse())
		{
			//XMFLOAT3 targetPos = { -50.0f, 20.0f, -100.0f };
			XMFLOAT3 scl = { 0.5f,0.5f,0.5f };
			float speed = (float)(rand() % FLYINGCROW_SPEED_MAX + 10) * 0.001f;

			// �p�����[�^�[�̃Z�b�g
			m_pFlyingCrow[i].SetIsUse(TRUE);
			m_pFlyingCrow[i].SetControlPos();
			m_pFlyingCrow[i].SetScl(scl);

			if (m_targetNo[num] == LAMP_TYPE_NONE)
			{
				m_pFlyingCrow[i].SetTargetPos(m_noneTargetPos);
			}
			else
			{
				targetPos = pQuestBoardArray[m_targetNo[num]]->GetPos();
			}

			m_pFlyingCrow[i].SetColor(color);
			m_pFlyingCrow[i].SetSpeed(speed);
			m_pFlyingCrow[i].SetTime(0.0f);

			count++;

			if (this->GetGod()->GetSlotManager()->GetRainbow())
			{
				SetRainbowColor(i);
				if (count > MAX_CROW_RAINBOW) return;
			}
			else
			{
				if (count > MAX_CROW_NORMAL) return;
			}
		}
	}
}

void FlyingCrowManager::SetRainbowColor(int i)
{
	XMFLOAT4 color;

	switch (i % LAMP_TYPE_MAX)
	{
	case LAMP_TYPE_RED:
		color = { 1.0f, 0.282f, 0.333f, 1.0f };
		break;

	case LAMP_TYPE_BLUE:
		color = { 0.0f, 0.282f, 0.666f, 1.0f };
		break;

	case LAMP_TYPE_GREEN:
		color = { 0.427f, 0.713f, 0.0f, 1.0f };
		break;

	case LAMP_TYPE_YELLOW:
		color = { 0.854f, 0.854f, 0.2f, 1.0f };
		break;

	case LAMP_TYPE_PINK:
		color = { 0.2f, 0.7f,0.7f, 1.0f };
		break;

	case LAMP_TYPE_PURPLE:
		color = { 0.427f, 0.427f, 0.666f, 1.0f };
		break;

	case LAMP_TYPE_ORANGE:
		color = { 1.0f, 0.568f,0.2f, 1.0f };
		break;

	}

	m_pFlyingCrow[i].SetColor(color);
}


