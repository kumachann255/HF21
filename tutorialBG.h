#pragma once
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "sprite.h"
#include "UI.h"


enum {
	tutorial_full,
	tutorial_left,
	tutorial_rightDoun,
	tutorial_rightUp,
	tutorial_garbage,
	tutorial_slot,
	tutorial_slot_pad,
	tutorial_arrow_tension,
	tutorial_arrow_protein,
	tutorial_arrow_calendar,
	tutorial_skip,
	tutorial_skip_pad,
	tutorialBG_max,
};

#define TUTORIALBG_TEXTURE_MAX			(tutorialBG_max)


class TutorialBG
{
private:
	ID3D11Buffer				*m_VertexBuffer = nullptr;		// 頂点情報
	ID3D11ShaderResourceView	*m_Texture[TUTORIALBG_TEXTURE_MAX] = { NULL };	// テクスチャ情報

	char *m_TexturName[TUTORIALBG_TEXTURE_MAX] = {
		"data/TEXTURE/tex_tutorial_BG00.png",
		"data/TEXTURE/tex_tutorial_BG01.png",
		"data/TEXTURE/tex_tutorial_BG02.png",
		"data/TEXTURE/tex_tutorial_BG03.png",
		"data/TEXTURE/tex_tutorial_garbage.png",
		"data/TEXTURE/tex_tutorial_slot.png",
		"data/TEXTURE/tex_tutorial_slot_pad.png",
		"data/TEXTURE/tex_tutorial_arrow_tension.png",
		"data/TEXTURE/tex_tutorial_arrow_protein.png",
		"data/TEXTURE/tex_tutorial_arrow_calendar.png",
		"data/TEXTURE/tex_tutorial_skip.png",
		"data/TEXTURE/tex_tutorial_skip_pad.png",
	};

	BOOL m_Use[TUTORIALBG_TEXTURE_MAX];					// TRUE:使っている  FALSE:未使用
	float m_w, m_h;				// 幅と高さ
	XMFLOAT3 m_Pos;				// ポリゴンの座標

public:
	TutorialBG();
	~TutorialBG() {};

	void Update();
	void Draw();

	void SetTex(int num, BOOL data);
	void Init();

};