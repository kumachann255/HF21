#pragma once
#include "main.h"
#include "GodObject.h"
#include "slot.h"
#include "FlyingCrowManager.h"
#include "Morphing.h"
#include "bonusSlot.h"
#include <time.h>
#include "bonusTimer.h"

#define MAX_BONUS_TIME		(10.0f)

class BonusSlotManager : GodObject
{
private:
	BonusSlot *m_pSlot = nullptr;
	BOOL m_isTimeMove = FALSE;
	clock_t m_start;
	float m_now = 0.0f;
	XMFLOAT3 m_telopPos = { 480.0f, 300.0f, 0.0f };
	BonusTimer *m_timer = nullptr;

	int m_countDownCount = 0;


public:
	BonusSlotManager(God *god);

	~BonusSlotManager() { delete m_pSlot; };

	void Update();
	void Draw();

	void SetTime(void);
};