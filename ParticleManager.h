#pragma once

#include "particle.h"

class ParticlManager
{
private:
	PARTICLE	*m_pParticle = nullptr;
public:
	ParticlManager();
	~ParticlManager();
	void Update();
	void Draw(int vNum);
	void CallParticle(XMFLOAT3 pos, float size, int num, int texID, int pattern,int time);
};

