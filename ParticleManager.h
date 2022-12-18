#pragma once

#include "particle.h"

class ParticlManager
{
private:
	PARTICLE	*m_pParticle[PARTICLE_BUFFER];
public:
	ParticlManager();
	~ParticlManager();
	void Update();
	void Draw();
	void CallParticle(XMFLOAT3 pos, float size, int num, int texID, int pattern);
};

