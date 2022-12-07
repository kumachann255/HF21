#pragma once
#include "roller.h"

enum
{
	ROLLER_SPRING,
	ROLLER_SUMMER,
	ROLLER_AUTOM,
	ROLLER_WINTER,
	ROLLER_MAX,
};


class RollerManager :public GodObject
{
private:
	Roller *pRoller[ROLLER_MAX] = { nullptr,nullptr,nullptr,nullptr };
	int SwichCnt = 0;

public:
	RollerManager(God *god);
	~RollerManager();

	void Update();
	void Draw();

	Roller *GetRoller(void) { return pRoller[0]; }
	int GetSwichCnt(void) { return SwichCnt; }
};

