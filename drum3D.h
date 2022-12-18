#pragma once
#include "main.h"
#include "object.h"

#define MAX_RESULT_NORMAL	 (9)
#define MAX_RESULT_BONUS	 (5)
#define RADIAN9 (6.14f / MAX_RESULT_NORMAL)
#define RADIAN10 (6.14f / MAX_RESULT_BONUS)
#define MAX_SPEED_NORMAL	(0.07f)
#define MAX_SPEED_BONUS		(0.02f)
#define SPEED_UP_VALUE		(0.0015f)

#define OFFSET	(0.25f)

enum {
	drum3D_red,
	drum3D_blue,
	drum3D_yellow,
	drum3D_max,
};

enum {
	drum3D_x10,
	drum3D_x50,
	drum3D_x30,
	drum3D_x100,
};

//// ドラムが10角形の場合
//enum {
//	bonus_drum3D_purple,
//	bonus_drum3D_red,
//	bonus_drum3D_yellow,
//	bonus_drum3D_green,
//	bonus_drum3D_blue,
//	bonus_drum3D_max,
//};

// ドラムが5角形の場合
enum {
	bonus_drum3D_blue,
	bonus_drum3D_purple,
	bonus_drum3D_red,
	bonus_drum3D_yellow,
	bonus_drum3D_green,
	bonus_drum3D_max,
};



class Drum3D : public Object
{
private:
	float m_speed = 0.0f;
	bool m_move = false;
	int m_color = 0;
	float m_result = 0.0f;
	float m_resultRadian = RADIAN9;
//	float m_resultRadianOffset = RADIAN9;

protected:
	int m_resultMax = MAX_RESULT_NORMAL;
	float m_offset = OFFSET;
	int m_colorMax = drum3D_max;
	float m_speedMax = MAX_SPEED_NORMAL;
	float m_speedUpValue = SPEED_UP_VALUE;


public:
	Drum3D();

	void SetSpeed(float speed) { m_speed = speed; }
	float GetSpeed(void) { return m_speed; }

	void SetMove(bool date) { m_move = date; }
	bool GetMove(void) { return m_move; }

	void SetNormal(void);
	void SetBonus(void);

	int GetColor(void) { return m_color; }

	void Update(void);

	void Stop(void);

	void SpinStart(void);

	void SetResult(void);

	void SetRainbowModel(void);
	void SetRainbowModelL(void);

	void ResetRainbowModel(void);
	void ResetRainbowModelL(void);


	~Drum3D() { delete m_prefab; };
};