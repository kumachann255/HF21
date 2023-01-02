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

	void AddSeason(void) { 
		m_wakuType += 2;
		if (m_wakuType > ui_waku_full_winter_bonus) m_wakuType = ui_waku_full_spring;
	};

	UIManager *GetUIManager() { return m_pUiManager; }
};