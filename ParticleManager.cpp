#include "ParticleManager.h"

ParticlManager::ParticlManager()
{
	for (int i = 0; i < PARTICLE_BUFFER; i++)
	{
		m_pParticle[i] = new PARTICLE[MAX_PARTICLE];
	}

}

ParticlManager::~ParticlManager()
{
	for (int i = 0; i < PARTICLE_BUFFER; i++)
	{
		if (m_pParticle[i])
		{
			delete[] m_pParticle[i];
		}

	}

}

void ParticlManager::Update()
{
	for (int i = 0; i < PARTICLE_BUFFER; i++)
	{
		if (m_pParticle[i]->GetSwich())
		{
			for (int j = 0; j < MAX_PARTICLE; j++)
			{
				m_pParticle[i][j].Update();
				m_pParticle[i][j].SpriteAnim.Update(m_pParticle[i][j].GetAnimeTime());

			}
		}

	}

}

void ParticlManager::Draw()
{
	// ���C�e�B���O�𖳌���
	SetLightEnable(FALSE);

	// Z��r����
	SetDepthEnable(FALSE);

	// �ʏ�u�����h�ɖ߂�
	SetBlendState(BLEND_MODE_ALPHABLEND);

	for (int i = 0; i < PARTICLE_BUFFER; i++)
	{
		if (m_pParticle[i]->GetSwich())
		{
			for (int j = 0; j < MAX_PARTICLE; j++)
			{
				m_pParticle[i][j].Draw();

			}
		}
	}


	// Z��r�L��
	SetDepthEnable(TRUE);

	// ���C�e�B���O��L����
	SetLightEnable(TRUE);

}

void ParticlManager::CallParticle(XMFLOAT3 pos, float size, int num, int texID, int pattern)
{
	for (int i = 0; i < PARTICLE_BUFFER; i++)
	{
		if (!m_pParticle[i]->GetSwich())
		{
			for (int j = 0; j < num; j++)
			{

				m_pParticle[i][j].SetSwich(TRUE);
				m_pParticle[i][j].SetPosBase(pos);
				//g_pParticle[i][j].SetPos(pos);
				m_pParticle[i][j].SetTexno(texID);
				m_pParticle[i][j].SetSize(size);
				m_pParticle[i][j].SetPattern(pattern);
				m_pParticle[i][j].SpriteAnim.SetUse(TRUE);
				m_pParticle[i][j].SetAnimeTime(rand() % 5 + 20);
			}

			break;
		}

	}

}
