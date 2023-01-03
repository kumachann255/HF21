#pragma once
//=============================================================================
//
// ���[�h�Z���N�g�̏��� [modeSelect.h]
// Author : �F�V�`�O
//
//=============================================================================
#pragma once
#include "Scene.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "sprite.h"

//*****************************************************************************
// �}�N����`
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

	ID3D11Buffer				*m_VertexBuffer = nullptr;		// ���_���
	ID3D11ShaderResourceView	*m_Texture[MODESELECT_TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

	char *m_TexturName[MODESELECT_TEXTURE_MAX] = {
		"data/TEXTURE/tex_modeSelect_black.png",
		"data/TEXTURE/tex_modeSelect_question.png",
		"data/TEXTURE/tex_modeSelect_keybord.png",
		"data/TEXTURE/tex_modeSelect_pad.png",
	};

	BOOL m_isKeyBord = TRUE;					// TRUE:�g���Ă���  FALSE:���g�p
	float m_w, m_h;				// ���ƍ���
	XMFLOAT3 m_Pos;				// �|���S���̍��W

public:
	ModeSelect(God * god);
	~ModeSelect();
	void Init();
	void Update();
	void Draw();
};

BOOL GetPlayerType(void);
