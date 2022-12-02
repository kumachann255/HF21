#pragma once
#include "main.h"
#include "object.h"
#include "Morphing.h"
#include "housing.h"

#define MAX_HOUSING_MOVE	(3)	
#define MAX_HOUSING_CLEAR_WAIT	(180)

class BonusHousing : public Object, Morphing
{
private:
	BOOL m_isMove = FALSE;
	BOOL m_isVibration = FALSE;
	BOOL m_isEnd = FALSE;
	float m_vec = 1.0f;

	int m_loopNum = 0;

	int m_waitTime = 0;

public:
	BonusHousing();
	~BonusHousing() { delete m_prefab; };

	void Update();

	void SetGoMorphing();

	void ResetMorphing();

	BOOL GetEnd(void) { return m_isEnd; };
	void SetEnt(BOOL data) { m_isEnd = data; }
};