#include "ParticleManager.h"

ParticlManager::ParticlManager()
{
	m_pParticle = new PARTICLE[MAX_PARTICLE];
}

ParticlManager::~ParticlManager()
{
	delete[] m_pParticle;
}

void ParticlManager::Update()
{
	for (int j = 0; j < MAX_PARTICLE; j++)
	{
		m_pParticle[j].Update();
		m_pParticle[j].m_pSpriteAnim->Update(m_pParticle[j].GetAnimeTime());

	}
}

void ParticlManager::Draw(int vNum)
{
	// ���C�e�B���O�𖳌���
	SetLightEnable(FALSE);

	// Z��r����
	SetDepthEnable(FALSE);

	// �ʏ�u�����h�ɖ߂�
	SetBlendState(BLEND_MODE_ALPHABLEND);

	for (int j = 0; j < MAX_PARTICLE; j++)
	{
		m_pParticle[j].Draw(vNum);
	}

	// Z��r�L��
	SetDepthEnable(TRUE);

	// ���C�e�B���O��L����
	SetLightEnable(TRUE);

}

void ParticlManager::CallParticle(XMFLOAT3 pos, float size, int num, int texID, int pattern,int time)
{
	for (int i = 0; i < num; i++)
	{
		if (!m_pParticle[i].GetSwich())
		{
			m_pParticle[i].SetSwich(TRUE);
			m_pParticle[i].SetPosBase(pos);
			m_pParticle[i].SetTexno(texID);
			m_pParticle[i].SetSize(size);
			m_pParticle[i].SetPattern(pattern);
			m_pParticle[i].m_pSpriteAnim->SetUse(TRUE);
			m_pParticle[i].SetAnimeTime(rand() % 5 + time);

		}

	}

}
