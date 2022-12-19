#pragma once
#include "main.h"
#include "GodObject.h"
#include "slot.h"
#include "FlyingCrowManager.h"
#include "Morphing.h"
#include "bonusSlot.h"
#include <time.h>
#include "bonusTimer.h"
#include "bonusBGh.h"
#include "FLUID3D_GPU.h"
#include "bonusGuidanceY.h"

#define MAX_BONUS_TIME		(20.0f)
#define MAX_TIMEUP_WAIT		(300)

class BonusSlotManager : GodObject
{
private:
	BonusSlot *m_pSlot = nullptr;
	BonusBG *m_pBG = nullptr;
	BonusGuidance *m_pGuidance = nullptr;
	BonusTimer *m_timer = nullptr;

	BOOL m_isTimeMove = FALSE;
	clock_t m_start;
	float m_now = 0.0f;
	XMFLOAT3 m_telopPos  = { 480.0f, 180.0f, 0.0f };
	XMFLOAT3 m_telopPos2 = { 400.0f, 460.0f, 0.0f };
	XMFLOAT3 m_telopPos3 = { 744.0f, 350.0f, 0.0f };
	XMFLOAT3 m_telopPos4 = { 480.0f, 300.0f, 0.0f };
	XMFLOAT3 m_telopPos5 = { 480.0f, 270.0f, 0.0f };
	XMFLOAT3 m_transitionPos = { -TRANSITION_WIDTH , 270.0f, 0.0f };
	XMFLOAT3 m_transitionPos2 = { SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 2, 0.0f };
	//FLUID3D_GPU* m_pSolverGPU;

	int m_timeUpWait = 0;

	int m_countDownCount = 0;


public:
	BonusSlotManager(God *god);

	~BonusSlotManager() { 
		delete m_pSlot; 	
		delete m_pBG;
		delete m_pGuidance;
		delete m_timer;
//		delete m_pSolverGPU;
	};

	void Update();
	void Draw();

	void SetTime(void);
	void StopTime(void) { m_isTimeMove = FALSE; };

	void Init();
};