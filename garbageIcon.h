#pragma once
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "sprite.h"
#include "UI.h"
#include "debugproc.h"



#define GARBAGE_TEXTURE_MAX		(2)		// テクスチャの数
#define GARBAGE_TEXTURE_WIDTH	(38.0f)	// キャラサイズ
#define GARBAGE_TEXTURE_HEIGHT	(20.0f)	// 
#define GARBAGE_TEXTURE_DISTANCE	(33.0f)	// キャラサイズ
#define MAX_GARBAGE				(20)
#define SCL_VALUE_GARBAGE		(1.15f)


class GarbageIcon
{
private:
	ID3D11Buffer				*m_VertexBuffer = nullptr;		// 頂点情報
	ID3D11ShaderResourceView	*m_Texture[GARBAGE_TEXTURE_MAX] = { NULL };	// テクスチャ情報

	char *m_TexturName[GARBAGE_TEXTURE_MAX] = {
		"data/TEXTURE/tex_tention.png",
		"data/TEXTURE/tex_tention_waku.png",
	};

	int m_iconNum = MAX_GARBAGE;
	float m_w, m_h;				// 幅と高さ
	XMFLOAT3 m_Pos;				// ポリゴンの座標
	int m_TexNo;				// テクスチャ番号
	XMFLOAT4 m_startColor, m_endColor;


public:
	GarbageIcon();
	~GarbageIcon();

	void Update();
	void Draw();

	void AddIconNum(void) { m_iconNum++; };
	void SetIconNum(int num) { m_iconNum = num; };
};