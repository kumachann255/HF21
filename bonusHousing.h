#pragma once
#include "main.h"
#include "object.h"
#include "Morphing.h"
#include "housing.h"

#define MAX_HOUSING_MOVE	(3)	

class BonusHousing : public Object, Morphing
{
private:
	BOOL m_isMove = FALSE;
	BOOL m_isVibration = FALSE;
	float m_vec = 1.0f;

public:
	BonusHousing();
	~BonusHousing() { delete m_prefab; };

	void Update();

	void SetGoMorphing();

};