#include "RollerManager.h"
#include "input.h"
#include "particle.h"
#include "sound.h"
#include "texManager.h"
#include "QuestBoardManager.h"
#include "slotManager.h"
#include "calendar_num.h"
#include "debugproc.h"
#include "SkyManager.h"

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

	//SwichCnt++;

	//if (SwichCnt % CALENDAR_SWITCH_TIME == 0)
	//{
	//	GetGod()->GetCalendarNum()->AddMonth();
	//}


	int seasonNum = GetGod()->GetCalendarNum()->GetMonth();
	BOOL fadeOut_EndFlag = GetGod()->GetSkyManager()->GetFadeOut_EndFlag();
	BOOL fadeOut_StartFlag = GetGod()->GetSkyManager()->GetFadeOut_StartFlag();
	XMFLOAT3 pos = { 0.0f,30.0f,0.0f };

	if (fadeOut_StartFlag)
	{
		CallParticle(pos, 80.0f, 30, EFFECT_REFLECTION, MOVE_PATTERN_UP);
	}


	// 春になる
	if (seasonNum >= month_4 && seasonNum <= month_6 && fadeOut_EndFlag)
	{

		pRoller[ROLLER_SPRING]->SetIsUse(TRUE);
		pRoller[ROLLER_SUMMER]->SetIsUse(FALSE);
		pRoller[ROLLER_AUTOM]->SetIsUse(FALSE);
		pRoller[ROLLER_WINTER]->SetIsUse(FALSE);

		GetGod()->GetTexManager()->AddSeason();
		//this->GetGod()->GetSlotManager()->GetSlot()->GetHousing()->NestSeason();

	}

	// 夏になる
	if (seasonNum >= month_7 && seasonNum <= month_9 && fadeOut_EndFlag)
	{

		pRoller[ROLLER_SPRING]->SetIsUse(FALSE);
		pRoller[ROLLER_SUMMER]->SetIsUse(TRUE);
		pRoller[ROLLER_AUTOM]->SetIsUse(FALSE);
		pRoller[ROLLER_WINTER]->SetIsUse(FALSE);

		GetGod()->GetTexManager()->AddSeason();
		PlaySound(SOUND_LABEL_SE_se_map_change); // マップ変化
		//this->GetGod()->GetSlotManager()->GetSlot()->GetHousing()->NestSeason();
	}

	// 秋になる
	if (seasonNum >= month_10 && seasonNum <= month_12 && fadeOut_EndFlag)
	{

		pRoller[ROLLER_SPRING]->SetIsUse(FALSE);
		pRoller[ROLLER_SUMMER]->SetIsUse(FALSE);
		pRoller[ROLLER_AUTOM]->SetIsUse(TRUE);
		pRoller[ROLLER_WINTER]->SetIsUse(FALSE);

		GetGod()->GetTexManager()->AddSeason();
		//this->GetGod()->GetSlotManager()->GetSlot()->GetHousing()->NestSeason();
		PlaySound(SOUND_LABEL_SE_se_map_change); // マップ変化
	}

	// 冬になる
	if (seasonNum >= month_1 && seasonNum <= month_3 && fadeOut_EndFlag)
	{

		pRoller[ROLLER_SPRING]->SetIsUse(FALSE);
		pRoller[ROLLER_SUMMER]->SetIsUse(FALSE);
		pRoller[ROLLER_AUTOM]->SetIsUse(FALSE);
		pRoller[ROLLER_WINTER]->SetIsUse(TRUE);

		GetGod()->GetTexManager()->AddSeason();
		//this->GetGod()->GetSlotManager()->GetSlot()->GetHousing()->NestSeason();
		PlaySound(SOUND_LABEL_SE_se_map_change); // マップ変化
	}

}

void RollerManager::Draw()
{
	for (int i = 0; i < ROLLER_MAX; i++)
	{
		pRoller[i]->Draw();
	}
}
