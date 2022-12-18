#pragma once
#include "main.h"
#include "object.h"

#define COLOR_SPEED	(0.01f)
#define MAX_COLOR_SPEED	(0.1f)
#define MAX_COLOR	(6)
#define SPEED_COLOR		(0.01f)


class Housing : public Object
{
private:
	XMFLOAT4 m_ansColor = { 1.0f, 1.0f, 1.0f, 1.0f };
	XMFLOAT4 m_resultColor[MAX_COLOR];
	XMFLOAT4 m_resetColor[4];
	float m_colorTime = 0.0f;
	int m_resultNum = MAX_COLOR;
	int m_colorType = 0;
	float m_time = 0.0f;
	int m_nowSeason = 0;
	XMFLOAT4 m_resetColorTemp;

	BOOL m_isRainbow = FALSE;

public:
	Housing();
	~Housing() { delete m_prefab; };

	void Update(void);
	void SetRainbow(BOOL data) { m_isRainbow = data; };
	BOOL GetRainbow(void) { return m_isRainbow; };

	void ResetColor(void) { m_prefab->SetColor(m_resetColorTemp); }
	void NestSeason(void);
};