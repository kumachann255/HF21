#pragma once
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "sprite.h"
#include "UI.h"


#define GARBAGE_TEXTURE_MAX		(1)		// テクスチャの数
#define GARBAGE_TEXTURE_WIDTH	(150.0f)	// キャラサイズ
#define GARBAGE_TEXTURE_HEIGHT	(80.0f)	// 
#define GARBAGE_TEXTURE_DISTANCE	(30.0f)	// キャラサイズ


class GarbageIcon
{
private:
	ID3D11Buffer				*m_VertexBuffer = nullptr;		// 頂点情報
	ID3D11ShaderResourceView	*m_Texture[GARBAGE_TEXTURE_MAX] = { NULL };	// テクスチャ情報

	char *m_TexturName[GARBAGE_TEXTURE_MAX] = {
		"data/TEXTURE/tex_gomi_icon.png",
	};

	int m_iconNum = 20;
	float m_w, m_h;				// 幅と高さ
	XMFLOAT3 m_Pos;				// ポリゴンの座標
	int m_TexNo;				// テクスチャ番号


public:
	GarbageIcon();
	~GarbageIcon();

	void Update();
	void Draw();

	void SetIconNum(int num) { m_iconNum = num; };
};