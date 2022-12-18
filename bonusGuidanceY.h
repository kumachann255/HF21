#pragma once
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "sprite.h"
#include "UI.h"

#define GUIDANCE_TEXTURE_MAX		(2)		// �e�N�X�`���̐�
#define GUIDANCE_TEXTURE_WIDTH		(160.0f)	// �L�����T�C�Y
#define GUIDANCE_TEXTURE_HEIGHT		(540.0f)	// 

#define GUIDANCE_SPEED				(0.001f)


class BonusGuidance
{
private:
	ID3D11Buffer				*m_VertexBuffer = nullptr;		// ���_���
	ID3D11ShaderResourceView	*m_Texture[GUIDANCE_TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

	char *m_TexturName[GUIDANCE_TEXTURE_MAX] = {
		"data/TEXTURE/tex_guidance_y0.png",
		"data/TEXTURE/tex_guidance_y1.png",
	};

	BOOL m_Use[2];					// TRUE:�g���Ă���  FALSE:���g�p
	float m_w[2], m_h[2];				// ���ƍ���
	XMFLOAT3 m_Pos[2];				// �|���S���̍��W

	XMFLOAT2 m_UV[2];

public:
	BonusGuidance();
	~BonusGuidance();

	void Update(void);
	void Draw(void);
};