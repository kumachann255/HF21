#pragma once
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "sprite.h"
#include "UI.h"

#define GUIDANCE_TEXTURE_MAX		(2)		// テクスチャの数
#define GUIDANCE_TEXTURE_WIDTH		(160.0f)	// キャラサイズ
#define GUIDANCE_TEXTURE_HEIGHT		(540.0f)	// 

#define GUIDANCE_SPEED				(0.001f)


class BonusGuidance
{
private:
	ID3D11Buffer				*m_VertexBuffer = nullptr;		// 頂点情報
	ID3D11ShaderResourceView	*m_Texture[GUIDANCE_TEXTURE_MAX] = { NULL };	// テクスチャ情報

	char *m_TexturName[GUIDANCE_TEXTURE_MAX] = {
		"data/TEXTURE/tex_guidance_y0.png",
		"data/TEXTURE/tex_guidance_y1.png",
	};

	BOOL m_Use[2];					// TRUE:使っている  FALSE:未使用
	float m_w[2], m_h[2];				// 幅と高さ
	XMFLOAT3 m_Pos[2];				// ポリゴンの座標

	XMFLOAT2 m_UV[2];

public:
	BonusGuidance();
	~BonusGuidance();

	void Update(void);
	void Draw(void);
};