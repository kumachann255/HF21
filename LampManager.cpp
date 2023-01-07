//=============================================================================
//
// �����v�}�l�[�W���[���� [LampManager.cpp]
// Author : ������n
//
//=============================================================================
#include "LampManager.h"
#include "input.h"
#include "debugproc.h"
#include "QuestBoardManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define LAMP_OFSETX		(20.0f)
#define LAMP_OFSETY		(70.0f)

//=============================================================================
// �R���X�g���N�^
//=============================================================================
LampManager::LampManager(void)
{

	for (int i = 0; i < LAMP_MAX; i++)
	{

		XMFLOAT3 pos = { -LAMP_OFSETX + (i*LAMP_OFSETX),LAMP_OFSETY,0.0f };
		m_lamps[i].GetPrefab()->SetPos(pos);
		m_lamps[i].SetIsUse(TRUE);
		m_lamps[i].SetDelete(FALSE);

	}

}

//=============================================================================
// �f�X�g���N�^�[
//=============================================================================
LampManager::~LampManager()
{

	for (int i = 0; i < LAMP_TYPE_MAX; i++)
	{
		if (m_Texture[i])
		{// �e�N�X�`���̉��
			m_Texture[i]->Release();
			m_Texture[i] = nullptr;
		}
	}

}

//=============================================================================
// �X�V����
//=============================================================================
void LampManager::Update(void)
{
	for (int i = 0; i < LAMP_MAX; i++)
	{
		if (!m_lamps[i].GetIsUse())
		{
			XMFLOAT3 pos = m_lamps[i].GetPrefab()->GetPos();
			XMFLOAT3 rot = m_lamps[i].GetPrefab()->GetRot();
			pos.y = 40.0f;
			pos.x = -5.0f;

			rot.z += 0.06f;

			m_lamps[i].GetPrefab()->SetPos(pos);
			m_lamps[i].GetPrefab()->SetRot(rot);
		}

		m_lamps[i].Update();
	}
}


//=============================================================================
// �`�揈��
//=============================================================================
void LampManager::Draw(XMMATRIX WorldMatrix)
{
	for (int i = 0; i < LAMP_MAX; i++)
	{
		//if (m_lamps[i].GetIsUse())
		{
			m_lamps[i].Draw(WorldMatrix);
		}
	}
}