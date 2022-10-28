#pragma once
#include "main.h"
#include "object.h"

#define RAND_CONTROLPOS_X_MAX		(70)
#define RAND_CONTROLPOS_Y_MAX		(200)

class FlyingCrow :public Object
{
private:
	XMFLOAT4 m_color;			// 色
	XMFLOAT3 m_startPos = {200.0f, 30.0f, -150.0f};		// 始発地
	XMFLOAT3 m_targetPos;		// 目的地

	XMFLOAT3 m_controlPosA = { 0.0f, 40.0f, -150.0f };		// 制御点A
	XMFLOAT3 m_controlPosB = { -180.0f, 30.0f, -100.0f };		// 制御点B

	float m_time = 0.0f;


public:
	FlyingCrow(){}
	FlyingCrow(XMFLOAT4 color, XMFLOAT3 targetPos) : m_color(color) , m_targetPos(targetPos) {
		// ここで制御点のランダム化を行う
		//m_controlPosA.x += (float)(rand() % RAND_CONTROLPOS_X_MAX - RAND_CONTROLPOS_X_MAX);
		//m_controlPosA.y += (float)(rand() % RAND_CONTROLPOS_Y_MAX - RAND_CONTROLPOS_Y_MAX);
		m_controlPosB.x += (float)(rand() % RAND_CONTROLPOS_X_MAX - RAND_CONTROLPOS_X_MAX / 2);
		m_controlPosB.y += (float)(rand() % RAND_CONTROLPOS_Y_MAX - RAND_CONTROLPOS_Y_MAX / 2);
	}

	void SetColor(XMFLOAT4 color) { m_color = color; }
	void SetTargetPos(XMFLOAT3 targetPos) { m_targetPos = targetPos; }

	XMFLOAT4 GetColor(void) { return m_color; }
	XMFLOAT3 GetTargetPos(void) { return m_targetPos; }

	float GetTime(void) { return m_time; }


	void DeleteFlyingCrow(void)
	{
	}

	~FlyingCrow() {}

	void Update(void) override;

};