#include "RollerManager.h"
#include "input.h"
#include "particle.h"
#include "sound.h"
#include "texManager.h"
#include "QuestBoardManager.h"
#include "slotManager.h"

#define	SWICH_TIME		(30)
#define	CALENDAR_SWITCH_TIME		(SWICH_TIME / 3 * 60)

#define	PARTICLE_TIME	(40)	

static char *g_TextureName[ROLLER_MAX] =
{
	"model_map&obj_spring.obj",
	"model_map&obj_summer.obj",
	"model_map&obj_autumn.obj",
	"model_map&obj_winter.obj",
};


RollerManager::RollerManager(God *god) :GodObject(god)
{
	for (int i = 0; i < ROLLER_MAX; i++)
	{
		pRoller[i] = new Roller();

		pRoller[i]->GetPrefab()->SetModel(g_TextureName[i]);
		pRoller[i]->SetIsUse(FALSE);
	}

	pRoller[ROLLER_SPRING]->SetIsUse(TRUE);
}

RollerManager::~RollerManager()
{
	for (int i = 0; i < ROLLER_MAX; i++)
	{
		delete pRoller[i];
	}
}

void RollerManager::Update()
{
	for (int i = 0; i < ROLLER_MAX; i++)
	{
		pRoller[i]->Update();
	}

	SwichCnt++;

	XMFLOAT3 pos = { 0.0f,30.0f,-50.0f };

	if (SwichCnt % CALENDAR_SWITCH_TIME == 0)
	{
		this->GetGod()->GetQuestBoardManager()->GetCalendarNum()->AddMonth();
	}


	// 春になる
	if (SwichCnt == 1)
	{
		pRoller[ROLLER_SPRING]->SetIsUse(TRUE);
		pRoller[ROLLER_SUMMER]->SetIsUse(FALSE);
		pRoller[ROLLER_AUTOM]->SetIsUse(FALSE);
		pRoller[ROLLER_WINTER]->SetIsUse(FALSE);

		this->GetGod()->GetTexManager()->AddSeason();
		//this->GetGod()->GetSlotManager()->GetSlot()->GetHousing()->NestSeason();
	}

	if (SwichCnt == (60 * SWICH_TIME *1) - PARTICLE_TIME)
	{
		CallParticle(pos, 80.0f, 20, EFFECT_REFLECTION, MOVE_PATTERN_UP);
	}


	// 夏になる
	if (SwichCnt == 60 * SWICH_TIME *1)
	{
		pRoller[ROLLER_SPRING]->SetIsUse(FALSE);
		pRoller[ROLLER_SUMMER]->SetIsUse(TRUE);
		pRoller[ROLLER_AUTOM]->SetIsUse(FALSE);
		pRoller[ROLLER_WINTER]->SetIsUse(FALSE);
		CallParticle(pos, 80.0f, 20, EFFECT_REFLECTION, MOVE_PATTERN_UP);

		this->GetGod()->GetTexManager()->AddSeason();
		PlaySound(SOUND_LABEL_SE_se_map_change); // マップ変化
		this->GetGod()->GetSlotManager()->GetSlot()->GetHousing()->NestSeason();
	}

	if (SwichCnt == (60 * SWICH_TIME *2) - PARTICLE_TIME)
	{
		CallParticle(pos, 80.0f, 20, EFFECT_REFLECTION, MOVE_PATTERN_UP);
	}

	// 秋になる
	if (SwichCnt == 60 * SWICH_TIME * 2)
	{
		pRoller[ROLLER_SPRING]->SetIsUse(FALSE);
		pRoller[ROLLER_SUMMER]->SetIsUse(FALSE);
		pRoller[ROLLER_AUTOM]->SetIsUse(TRUE);
		pRoller[ROLLER_WINTER]->SetIsUse(FALSE);
		CallParticle(pos, 200.0f, 20, EFFECT_REFLECTION, MOVE_PATTERN_UP);

		this->GetGod()->GetTexManager()->AddSeason();
		this->GetGod()->GetSlotManager()->GetSlot()->GetHousing()->NestSeason();
		PlaySound(SOUND_LABEL_SE_se_map_change); // マップ変化
	}

	if (SwichCnt == (60 * SWICH_TIME *3) - PARTICLE_TIME)
	{
		CallParticle(pos, 80.0f, 20, EFFECT_REFLECTION, MOVE_PATTERN_UP);
	}

	// 冬になる
	if (SwichCnt == 60 * SWICH_TIME * 3)
	{
		pRoller[ROLLER_SPRING]->SetIsUse(FALSE);
		pRoller[ROLLER_SUMMER]->SetIsUse(FALSE);
		pRoller[ROLLER_AUTOM]->SetIsUse(FALSE);
		pRoller[ROLLER_WINTER]->SetIsUse(TRUE);
		CallParticle(pos, 80.0f, 20, EFFECT_REFLECTION, MOVE_PATTERN_UP);

		this->GetGod()->GetTexManager()->AddSeason();
		this->GetGod()->GetSlotManager()->GetSlot()->GetHousing()->NestSeason();
		PlaySound(SOUND_LABEL_SE_se_map_change); // マップ変化
	}


	if (SwichCnt == (60 * SWICH_TIME * 4) - PARTICLE_TIME)
	{
		CallParticle(pos, 80.0f, 20, EFFECT_REFLECTION, MOVE_PATTERN_UP);
	}


	if (SwichCnt == 60 * SWICH_TIME * 5)
	{
		SwichCnt = 0;
	}


}

void RollerManager::Draw()
{
	for (int i = 0; i < ROLLER_MAX; i++)
	{
		pRoller[i]->Draw();
	}
}
