#pragma once
#include "main.h"
#include "GodObject.h"
#include "UIManager.h"

enum {
	telop_bonusChance,
	telop_1,
	telop_2,
	telop_3,
	telop_max,
};

enum {
	texType_normal,
	texType_fade,
	texType_cutIn_right,
	texType_cutIn_left,
	texType_cutIn_up,
	texType_cutIn_under,
	texType_zoomIn,
	texType_zoomIn_rot,
};


#define TELOP_TEXTURE_MAX	(telop_max)

static char *g_TexturName[TELOP_TEXTURE_MAX] = {
	"data/TEXTURE/telop_bonusChance.png",
	"data/TEXTURE/tex_num_1.png",
	"data/TEXTURE/tex_num_2.png",
	"data/TEXTURE/tex_num_3.png",
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