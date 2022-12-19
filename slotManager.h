#pragma once
#include "main.h"
#include "GodObject.h"
#include "slot.h"
#include "FlyingCrowManager.h"
#include "bonusSlot.h"
#include "QuestBoardManager.h"
#include "rainbowTime.h"
#include <time.h>

enum
{
	No_slot,
	No_FlyingCrow,
};

#define MAX_RAINBOW_TIME			(20.0f)
#define MAX_RAINBOW_TIMEUP_WAIT		(120)
#define MAX_RAINBOW_STRAT_WAIT		(120)

class SlotManager : GodObject
{
private:
	Slot *m_pSlot = nullptr;
	FlyingCrowManager *m_pFlyingCrowManager = nullptr;
	RainbowTimer *m_pRainbowTimer = nullptr;

	BOOL m_isRainbow = FALSE;
	clock_t m_start;
	float m_now = 0.0f;
	int m_timeUpWait = 0;
	int m_rainbowStartWait = 0;

public:
	SlotManager(God *god);
	~SlotManager();

	void Update();

	void Draw(int type);

	void SetRainbow(BOOL data) { m_isRainbow = data; };
	BOOL GetRainbow(void) { return m_isRainbow; };

	void SetRainbowMode(void);
	void ResetRainbowMode(void);

	Slot *GetSlot(void) { return m_pSlot; };

	void Init();
};







