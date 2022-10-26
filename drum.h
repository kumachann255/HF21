#pragma once
#include "rotator.h"
#include "main.h"

#define TEXTURE_WIDTH_COLOR			(70.0f)			// ƒƒSƒTƒCƒY
#define TEXTURE_HEIGHT_COLOR		(70.0f)			// 
#define START_POS_Y					(280.0f)

enum {
	drum_red,
	drum_blue,
	drum_yellow,
};

class Drum : public Rotator
{
private:
	int m_type = drum_red;
	bool m_move = false;
	float m_speed;
	bool m_center = false;
	const float m_startPosY = START_POS_Y;
	const float m_endPosY = START_POS_Y + TEXTURE_HEIGHT_COLOR * 3.0f;
	const float m_speedMax = 5.0f;

public:
	XMFLOAT2 m_Pos;

	Drum() : m_Pos(0.0f, m_startPosY), m_speed(0.0f) {}

	void SetType(int type)
	{
		m_type = type;
	}

	int GetType(void) { return m_type; }

	void SetMove(bool data)
	{
		m_move = data;
	}

	bool GetMove(void) { return m_move; }

	bool GetCenter(void) { return m_center; }

	void Action(void) override {
		m_speed += 0.1f;
		if (m_speed > m_speedMax) m_speed = m_speedMax;

		m_Pos.y += m_speed;

		if (m_Pos.y > m_endPosY)
		{
			m_Pos.y -= TEXTURE_HEIGHT_COLOR * 3.0f;
		}

		m_center = false;
	}

	void SetStopDrum(void)
	{
		m_speed = 0.0f;

		if ((m_Pos.y - m_startPosY < TEXTURE_HEIGHT_COLOR) && (m_Pos.y - m_startPosY > 0))
		{
			m_Pos.y += ((m_startPosY + TEXTURE_HEIGHT_COLOR * 0.5f) - m_Pos.y) * 0.2f;
		}
		if ((m_Pos.y - (m_startPosY + TEXTURE_HEIGHT_COLOR) < TEXTURE_HEIGHT_COLOR) && (m_Pos.y - (m_startPosY + TEXTURE_HEIGHT_COLOR) > 0))
		{
			m_Pos.y += ((m_startPosY + TEXTURE_HEIGHT_COLOR * 1.5f) - m_Pos.y) * 0.2f;
			m_center = true;
		}
		else if ((m_Pos.y - (m_startPosY + TEXTURE_HEIGHT_COLOR * 2.0f) < TEXTURE_HEIGHT_COLOR) && (m_Pos.y - (m_startPosY + TEXTURE_HEIGHT_COLOR * 2.0f) > 0))
		{
			m_Pos.y += ((m_startPosY + TEXTURE_HEIGHT_COLOR * 2.5f) - m_Pos.y) * 0.2f;
		}
	}
};


HRESULT InitDrum(void);
void UninitDrum(void);
void UpdateDrum(void);
void DrawDrum(void);

XMFLOAT4 GetColor(void);
