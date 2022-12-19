#pragma once
#include "roller.h"
#include "ParticleManager.h"

enum
{
	ROLLER_SPRING,
	ROLLER_SUMMER,
	ROLLER_AUTOM,
	ROLLER_WINTER,
	ROLLER_MAX,
};

#define	SWICH_TIME		(30)
#define	CALENDAR_SWITCH_TIME		(SWICH_TIME / 3 * 60)

class RollerManager :public GodObject
{
private:
	Roller *pRoller[ROLLER_MAX] = { nullptr,nullptr,nullptr,nullptr };
	ParticlManager *pParticlManager = nullptr;
	int SwichCnt = 0;
	int texNum = 0;

public:
	RollerManager(God *god);
	~RollerManager();

	void Update();
	void Draw();

	Roller *GetRoller(void) { return pRoller[0]; }
	int GetSwichCnt(void) { return SwichCnt; }

	void Init();
};

