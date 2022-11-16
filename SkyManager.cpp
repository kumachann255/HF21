//=============================================================================
//
// �G�ߊǗ����� [SkyManager.cpp]
// Author : ������n
//
//=============================================================================
#include "SkyManager.h"
#include "input.h"
#include "debugproc.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
SkyManager::SkyManager(God *god):GodObject(god)
{

	// �e�N�X�`������
	for (int i = 0; i < SEASON_MODE_MAX; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
			nullptr,
			nullptr,
			&m_Texture[i],
			nullptr);
	}

	m_seasons[BUFFER_FRONT] = new Sky;
	m_seasons[BUFFER_FRONT]->GetPrefab()->SetModel(g_ModelName[SEASON_MODE_SPRING]);
	m_seasons[BUFFER_FRONT]->SetIsUse(TRUE);
	m_seasons[BUFFER_FRONT]->GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[SEASON_MODE_SPRING];

}

//=============================================================================
// �f�X�g���N�^�[
//=============================================================================
SkyManager::~SkyManager()
{
	for (int i = 0; i < BUFFER_MAX; i++)
	{
		if (m_seasons[i])
		{
			delete m_seasons[i];
		}
				
	}

	for (int i = 0; i < SEASON_MODE_MAX; i++)
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
void SkyManager::Update(void)
{
	for (int i = 0; i < BUFFER_MAX; i++)
	{
		if (m_seasons[i])	m_seasons[i]->Update();

	}

	// m_color = { 1.0f,1.0f,1.0f,1.0f };
	// m_time += 0.01f;
	// m_color.w += 0.02f * cosf(m_time);

	//if (m_time >= (XM_PI * 2) - XMConvertToRadians(30.0f))
	//{
	//	m_swich++;
	//	m_swich %= SEASON_MODE_MAX;


	//}

	//if (m_time >= (XM_PI * 2))
	//{
	//	m_time = 0.0f;

	//}

	//m_seasons[BUFFER_FRONT]->GetPrefab()->SetColor(m_color);

	//if (GetKeyboardTrigger(DIK_F1))
	//{
	//	m_swich++;
	//	m_swich %= SEASON_MODE_MAX;

	//}


	// �f�o�b�O�p
	//if (GetKeyboardTrigger(DIK_F1))
	{

		switch (m_swich)
		{
		case SEASON_MODE_SPRING: 	
			m_seasons[BUFFER_FRONT]->GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[SEASON_MODE_SPRING];
			break;

		case SEASON_MODE_SUMMER: 
			m_seasons[BUFFER_FRONT]->GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[SEASON_MODE_SUMMER];
			break;

		case SEASON_MODE_AUTUMN:
			m_seasons[BUFFER_FRONT]->GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[SEASON_MODE_AUTUMN];
			break;

		case SEASON_MODE_WINTER: 
			m_seasons[BUFFER_FRONT]->GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[SEASON_MODE_WINTER];
			break;

		case SEASON_MODE_RAIN: 
			m_seasons[BUFFER_FRONT]->GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[SEASON_MODE_RAIN];
			break;
		}

	}


}


//=============================================================================
// �`�揈��
//=============================================================================
void SkyManager::Draw(SKYBG_MODE swich)
{
	m_swich = swich;

	switch (m_swich)
	{
	case SEASON_MODE_SPRING:
		m_seasons[BUFFER_FRONT]->GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[SEASON_MODE_SPRING];
		break;

	case SEASON_MODE_SUMMER:
		m_seasons[BUFFER_FRONT]->GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[SEASON_MODE_SUMMER];
		break;

	case SEASON_MODE_AUTUMN:
		m_seasons[BUFFER_FRONT]->GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[SEASON_MODE_AUTUMN];
		break;

	case SEASON_MODE_WINTER:
		m_seasons[BUFFER_FRONT]->GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[SEASON_MODE_WINTER];
		break;

	case SEASON_MODE_RAIN:
		m_seasons[BUFFER_FRONT]->GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[SEASON_MODE_RAIN];
		break;
	}


	for (int i = 0; i < BUFFER_MAX; i++)
	{
		if (m_seasons[i])
		{
			m_seasons[i]->Draw();
		}
	}

#ifdef _DEBUG	// �f�o�b�O����\������
	//PrintDebugProc("TEST_SKY\n");
#endif

}
