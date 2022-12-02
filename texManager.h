#pragma once
#include "main.h"
#include "GodObject.h"
#include "UIManager.h"


#define TELOP_TEXTURE_MAX	(3)

static char *g_TexturName[TELOP_TEXTURE_MAX] = {
	"data/TEXTURE/bg000.jpg",
	"data/TEXTURE/title_logo.png",
	"data/TEXTURE/effect000.jpg",
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