#pragma once
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "sprite.h"
#include "UI.h"


#define PROTEIN_TEXTURE_MAX		(1)		// テクスチャの数
#define PROTEIN_TEXTURE_WIDTH	(80.0f)	// キャラサイズ
#define PROTEIN_TEXTURE_HEIGHT	(100.0f)	// 
#define PROTEIN_TEXTURE_DISTANCE	(PROTEIN_TEXTURE_WIDTH)	// キャラサイズ


class ProteinIcon
{
private:
	ID3D11Buffer				*m_VertexBuffer = nullptr;		// 頂点情報
	ID3D11ShaderResourceView	*m_Texture[PROTEIN_TEXTURE_MAX] = { NULL };	// テクスチャ情報

	char *m_TexturName[PROTEIN_TEXTURE_MAX] = {
		"data/TEXTURE/tex_protein_icon.png",
	};

	int m_iconNum = 0;
	float m_w, m_h;				// 幅と高さ
	XMFLOAT3 m_Pos;				// ポリゴンの座標
	int m_TexNo;				// テクスチャ番号


public:
	ProteinIcon();
	~ProteinIcon();

	void Update();
	void Draw();

	void SetIconNum(int num);
};