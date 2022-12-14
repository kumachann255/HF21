#pragma once
#include "main.h"
#include "GodObject.h"
#include "UIManager.h"

enum {
	trandition_white,
	ui_waku_full,

	telop_bonusChance,
	telop_bonusChanceFalse,

	telop_1,
	telop_2,
	telop_3,

	telop_evolution,
	telop_wing,
	telop_breast,
	telop_thigh,

	telop_guidance,
	telop_rainbowTime,
	telop_rainbowEnd,
	telop_rainbowTimeMakure,

	trandition_whiteFull,
	trandition_crow,

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
};


#define TELOP_TEXTURE_MAX	(telop_max)

static char *g_TexturName[TELOP_TEXTURE_MAX] = {
	"data/TEXTURE/tex_whiteBox.png",
	"data/TEXTURE/tex_waku_full.png",
	"data/TEXTURE/telop_bonusChance.png",
	"data/TEXTURE/tex_bonusFalse.png",

	"data/TEXTURE/tex_num_1.png",
	"data/TEXTURE/tex_num_2.png",
	"data/TEXTURE/tex_num_3.png",

	"data/TEXTURE/tex_evolution.png",
	"data/TEXTURE/tex_chicken_wings_false.png",
	"data/TEXTURE/tex_chicken_breast_false.png",
	"data/TEXTURE/tex_chicken_thigh_false.png",

	"data/TEXTURE/tex_guidance.png",
	"data/TEXTURE/tex_rainbowTime.png",
	"data/TEXTURE/tex_rainbowEnd.png",
	"data/TEXTURE/tex_rainbowTimeMakure.png",

	"data/TEXTURE/tex_whiteBox.png",
	"data/TEXTURE/tex_transition_crow.png",
};


class TexManager : public GodObject
{
private:
	UIManager *m_pUiManager = nullptr;

public:
	TexManager(God *god);
	~TexManager() {};

	void Update();
	void Draw();

	UIManager *GetUIManager() { return m_pUiManager; }
};