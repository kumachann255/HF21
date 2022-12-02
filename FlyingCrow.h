#pragma once
#include "main.h"
#include "object.h"

#define RAND_CONTROLPOS_X_MAX		(200)
#define RAND_CONTROLPOS_Y_MAX		(500)

#define MAX_FLYINGCROW_SCL			(0.3f)
#define VALUE_FLYINGCROW_SCL		(0.005f)

#define FLYINGCROW_SPEED_MAX		(8)

class FlyingCrow :public Object
{
private:
	XMFLOAT4 m_color;	// 色
	XMFLOAT3 m_startPos  = { 150.0f, 80.0f, -350.0f};		// 始発地
	XMFLOAT3 m_targetPos = { 0.0f, 0.0f, 0.0f };

	XMFLOAT3 m_controlPosA = { -40.0f, 100.0f, -350.0f };	// 制御点A
	XMFLOAT3 m_controlPosB = { -180.0f, 60.0f, -275.0f };	// 制御点B

	float m_time = 0.0f;
	float m_speed = 0.0f;

	float m_sclDownValue = 0.0f;

	XMFLOAT2 m_offset = { 0.0f, 0.0f };

public:
	FlyingCrow() { 
		m_prefab = new Prefab;
		m_offset.x = (float)(rand() % 10 - 5);
		m_offset.y = (float)(rand() % 15 - 5) + 40.0f;
	}
	FlyingCrow(XMFLOAT4 color, XMFLOAT3 targetPos) : m_color(color) , m_targetPos(targetPos) {
		// ここで制御点のランダム化を行う
		//m_controlPosA.x += (float)(rand() % RAND_CONTROLPOS_X_MAX - RAND_CONTROLPOS_X_MAX);
		//m_controlPosA.y += (float)(rand() % RAND_CONTROLPOS_Y_MAX - RAND_CONTROLPOS_Y_MAX);
		m_controlPosB.x += (float)(rand() % RAND_CONTROLPOS_X_MAX - RAND_CONTROLPOS_X_MAX / 2);
		m_controlPosB.y += (float)(rand() % RAND_CONTROLPOS_Y_MAX - RAND_CONTROLPOS_Y_MAX / 2);
		m_speed = (float)(rand() % FLYINGCROW_SPEED_MAX + 10) * 0.001f;
		m_prefab = new Prefab;
	}

	~FlyingCrow() { delete m_prefab; }

	void SetColor(XMFLOAT4 color) { m_color = color; }
	void SetTargetPos(XMFLOAT3 targetPos) { m_targetPos = targetPos; }

	void SetControlPos(void) { 
		m_controlPosB.x += (float)(rand() % RAND_CONTROLPOS_X_MAX - RAND_CONTROLPOS_X_MAX / 2);
		m_controlPosB.y += (float)(rand() % RAND_CONTROLPOS_Y_MAX - RAND_CONTROLPOS_Y_MAX / 2);
	}
	void ResetControlPos(void) { 
		m_controlPosB = { -180.0f, 60.0f, -275.0f };
	}

	void SetTime(float time) { m_time = time; }
	void SetSpeed(float speed) { m_speed = speed; }

	XMFLOAT4 GetColor(void) { return m_color; }
	XMFLOAT3 GetTargetPos(void) { return m_targetPos; }
	float GetSpeed(void) { return m_speed; }
	float GetTime(void) { return m_time; }

	void DeleteFlyingCrow(void){};

	void Update(void) override;

	void SetOffset(XMFLOAT2 data) { m_offset = data; };
	XMFLOAT2 GetOffset(void) { return m_offset; }

};