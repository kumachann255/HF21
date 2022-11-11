#pragma once
#include "main.h"
#include "object.h"

class Drum3D : public Object
{
private:
	float m_speed = 0.0f;
	const float m_speedMax = 0.07f;
	bool m_move = false;
	int m_color = 0;
	float m_result = 0.0f;

public:
	Drum3D();

	void SetSpeed(float speed) { m_speed = speed; }
	float GetSpeed(void) { return m_speed; }

	void SetMove(bool date) { m_move = date; }
	bool GetMove(void) { return m_move; }

	int GetColor(void) { return m_color; }

	void Update(void);

	void Stop(void);

	void SpinStart(void);

	void SetResult(void);

	~Drum3D() { delete m_prefab; };
};