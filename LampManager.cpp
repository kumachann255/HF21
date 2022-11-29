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

		//m_lamps[i].GetPrefab()->SetModel(g_ModelName[LAMP_TYPE_RED]);
		XMFLOAT3 pos = { -LAMP_OFSETX + (i*LAMP_OFSETX),LAMP_OFSETY,0.0f };
		m_lamps[i].GetPrefab()->SetPos(pos);
		m_lamps[i].SetIsUse(TRUE);

		//int colorId = rand() % 4;
		//m_lamps[i].SetColorTypeId(colorId);
		//m_lamps[i].GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[colorId];

	}

}

//=============================================================================
// �f�X�g���N�^�[
//=============================================================================
LampManager::~LampManager()
{
	for (int i = 0; i < LAMP_MAX; i++)
	{
		//if (m_lamps[i])
		//{
		//	delete m_lamps[i];
		//}
	}

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
		if (m_lamps[i].GetIsUse())
		{
			m_lamps[i].Draw(WorldMatrix);
		}
	}
}