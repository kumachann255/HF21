#pragma once
#include "main.h"
#include "GodObject.h"
#include "UIManager.h"

enum {
	hit_effect_red,
	hit_effect_orange,

	ui_waku_full_spring,
	ui_waku_full_spring_bonus,
	ui_waku_full_summer,
	ui_waku_full_summer_bonus,
	ui_waku_full_autumn,
	ui_waku_full_autumn_bonus,
	ui_waku_full_winter,
	ui_waku_full_winter_bonus,

	telop_bonusChance,
	telop_bonusChanceFalse,

	telop_1,
	telop_2,
	telop_3,
	telop_start,

	telop_evolution,
	telop_wing,
	telop_breast,
	telop_thigh,

	telop_guidance,
	telop_rainbowHit,
	telop_rainbowTime,
	telop_rainbowEnd,
	telop_rainbowTimeMakure,

	telop_timeUp,

	trandition_white,
	trandition_whiteFull,
	trandition_crow,

	concentration_line0,
	concentration_line1,


	tutorial_00,
	tutorial_01,
	tutorial_02,
	tutorial_03,
	tutorial_04,
	tutorial_05,
	tutorial_06,
	tutorial_07,
	tutorial_08,
	tutorial_09,
	tutorial_10,
	tutorial_11,
	tutorial_12,
	tutorial_13,
	tutorial_14,
	tutorial_15,
	tutorial_16,
	tutorial_17,
	tutorial_18,
	tutorial_19,
	tutorial_20,
	tutorial_21,
	tutorial_22,
	tutorial_23,
	tutorial_24,
	
	telop_max,
};

enum {
	texType_normal,
	texType_fade,
	texType_cutIn_right,
	texType_cutIn_left,
	texType_cutIn_up,
	texType_cutIn_up_Update,
	texType_cutIn_under,
	texType_cutIn_under_Update,
	texType_zoomIn,
	texType_zoomIn_Update,
	texType_zoomIn_rot,
	texType_tansition,
	texType_endless,
	texType_line0,
	texType_line1,
	texType_spring,
	texType_spin_clockwise,
	texType_spin_anticlockwise
};


#define TELOP_TEXTURE_MAX	(telop_max)

static char *g_TexturName[TELOP_TEXTURE_MAX] = {
	"data/TEXTURE/tex_hit_effect_red.png",
	"data/TEXTURE/tex_hit_effect_orange.png",

	"data/TEXTURE/tex_waku_full_spring.png",
	"data/TEXTURE/tex_waku_full_spring_bonus.png",
	"data/TEXTURE/tex_waku_full_summer.png",
	"data/TEXTURE/tex_waku_full_summer_bonus.png",
	"data/TEXTURE/tex_waku_full_autumn.png",
	"data/TEXTURE/tex_waku_full_autumn_bonus.png",
	"data/TEXTURE/tex_waku_full_winter.png",
	"data/TEXTURE/tex_waku_full_winter_bonus.png",

	"data/TEXTURE/telop_bonusChance.png",
	"data/TEXTURE/tex_bonusFalse.png",

	"data/TEXTURE/tex_num_1.png",
	"data/TEXTURE/tex_num_2.png",
	"data/TEXTURE/tex_num_3.png",
	"data/TEXTURE/tex_start.png",

	"data/TEXTURE/tex_evolution.png",
	"data/TEXTURE/tex_chicken_wings_false.png",
	"data/TEXTURE/tex_chicken_breast_false.png",
	"data/TEXTURE/tex_chicken_thigh_false.png",

	"data/TEXTURE/tex_guidance.png",
	"data/TEXTURE/tex_bonusHit.png",
	"data/TEXTURE/tex_rainbowTime.png",
	"data/TEXTURE/tex_rainbowEnd.png",
	"data/TEXTURE/tex_rainbowTimeMakure.png",

	"data/TEXTURE/tex_timeUp.png",

	"data/TEXTURE/tex_whiteBox.png",
	"data/TEXTURE/tex_whiteBox.png",
	"data/TEXTURE/tex_transition_crow.png",

	"data/TEXTURE/tex_concentrationLine0.png",
	"data/TEXTURE/tex_concentrationLine1.png",

	"data/TEXTURE/tex_tutorial_00.png",
	"data/TEXTURE/tex_tutorial_01.png",
	"data/TEXTURE/tex_tutorial_02.png",
	"data/TEXTURE/tex_tutorial_03.png",
	"data/TEXTURE/tex_tutorial_04.png",
	"data/TEXTURE/tex_tutorial_05.png",
	"data/TEXTURE/tex_tutorial_06.png",
	"data/TEXTURE/tex_tutorial_07.png",
	"data/TEXTURE/tex_tutorial_08.png",
	"data/TEXTURE/tex_tutorial_09.png",
	"data/TEXTURE/tex_tutorial_10.png",
	"data/TEXTURE/tex_tutorial_11.png",
	"data/TEXTURE/tex_tutorial_12.png",
	"data/TEXTURE/tex_tutorial_13.png",
	"data/TEXTURE/tex_tutorial_14.png",
	"data/TEXTURE/tex_tutorial_15.png",
	"data/TEXTURE/tex_tutorial_16.png",
	"data/TEXTURE/tex_tutorial_17.png",
	"data/TEXTURE/tex_tutorial_18.png",
	"data/TEXTURE/tex_tutorial_19.png",
	"data/TEXTURE/tex_tutorial_20.png",
	"data/TEXTURE/tex_tutorial_21.png",
	"data/TEXTURE/tex_tutorial_22.png",
	"data/TEXTURE/tex_tutorial_23.png",
	"data/TEXTURE/tex_tutorial_24.png",

};


class TexManager : public GodObject
{
private:
	UIManager *m_pUiManager = nullptr;
	int m_wakuType = ui_waku_full_spring;

public:
	TexManager(God *god);
	~TexManager() {};

	void Update();
	void Draw();
	void Init(int type);

	void AddSeason(void) { 
		m_wakuType += 2;
		if (m_wakuType > ui_waku_full_winter_bonus) m_wakuType = ui_waku_full_spring;
	};

	UIManager *GetUIManager() { return m_pUiManager; }
};