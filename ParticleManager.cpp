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
	// ライティングを無効に
	SetLightEnable(FALSE);

	// Z比較無し
	SetDepthEnable(FALSE);

	// 通常ブレンドに戻す
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


	// Z比較有効
	SetDepthEnable(TRUE);

	// ライティングを有効に
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
