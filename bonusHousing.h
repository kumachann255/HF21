#pragma once
#include "main.h"
#include "object.h"
#include "Morphing.h"
#include "housing.h"

#define MAX_HOUSING_MOVE	(3)	
#define MAX_HOUSING_CLEAR_WAIT	(180)
#define HOUSING_COLOR_SPEED	(0.01f)
#define MAX_HOUSING_COLOR_SPEED	(0.1f)


class BonusHousing : public Object, Morphing
{
private:
	BOOL m_isMove = FALSE;
	BOOL m_isVibration = FALSE;
	BOOL m_isEnd = FALSE;
	float m_vec = 1.0f;

	XMFLOAT4 m_ansColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	XMFLOAT4 m_resultColor[3];

	float m_colorTime = 0.0f;
	int m_resultNum = 0;
	int m_colorType = 0;

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

	void SetColor(XMFLOAT4 color);
	void ResetColor(void);
};