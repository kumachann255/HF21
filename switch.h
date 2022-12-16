#pragma once
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "sprite.h"
#include "UI.h"


#define SWITCH_TEXTURE_MAX			(3)			// �e�N�X�`���̐�
#define SWITCH_TEXTURE_WIDTH		(100.0f)	// �L�����T�C�Y
#define SWITCH_TEXTURE_HEIGHT		(50.0f)	// 

#define SWITCH_DISTANCE				(280.0f)

#define SWITCH_EFFECT_LIFE			(3)


class Switch
{
private:
	ID3D11Buffer				*m_VertexBuffer = nullptr;		// ���_���
	ID3D11ShaderResourceView	*m_Texture[SWITCH_TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

	char *m_TexturName[SWITCH_TEXTURE_MAX] = {
		"data/TEXTURE/tex_switch_off.png",
		"data/TEXTURE/tex_switch_on.png",
		"data/TEXTURE/tex_switch_effect.png",
	};

	float m_w, m_h;				// ���ƍ���
	XMFLOAT3 m_Pos;				// �|���S���̍��W
	XMFLOAT3 m_PosEffect;		// �|���S���̍��W

	BOOL m_isEffect = FALSE;
	int m_texNum[3];
	int m_count = 0;

public:
	Switch();
	~Switch();

	void Update();
	void Draw();

	void SwitchON(int num);
	void SwitchOFF(void);
};