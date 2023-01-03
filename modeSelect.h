#pragma once
//=============================================================================
//
// モードセレクトの処理 [modeSelect.h]
// Author : 熊澤義弘
//
//=============================================================================
#pragma once
#include "Scene.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "sprite.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define MODESELECT_TEXTURE_MAX			(4)

enum{
	modeSelect_brack,
	modeSelect_question,
	modeSelect_keybord,
	modeSelect_pad,
};

class ModeSelect : public Scene
{
private:
	BOOL m_isInit = FALSE;

	ID3D11Buffer				*m_VertexBuffer = nullptr;		// 頂点情報
	ID3D11ShaderResourceView	*m_Texture[MODESELECT_TEXTURE_MAX] = { NULL };	// テクスチャ情報

	char *m_TexturName[MODESELECT_TEXTURE_MAX] = {
		"data/TEXTURE/tex_modeSelect_black.png",
		"data/TEXTURE/tex_modeSelect_question.png",
		"data/TEXTURE/tex_modeSelect_keybord.png",
		"data/TEXTURE/tex_modeSelect_pad.png",
	};

	BOOL m_isKeyBord = TRUE;					// TRUE:使っている  FALSE:未使用
	float m_w, m_h;				// 幅と高さ
	XMFLOAT3 m_Pos;				// ポリゴンの座標

public:
	ModeSelect(God * god);
	~ModeSelect();
	void Init();
	void Update();
	void Draw();
};

BOOL GetPlayerType(void);
