#pragma once
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "sprite.h"
#include "UI.h"

#define BONUS_TIMER_TEXTURE_MAX		(1)		// テクスチャの数
#define BONUS_TIMER_TEXTURE_WIDTH	(80.0f)	// キャラサイズ
#define BONUS_TIMER_TEXTURE_HEIGHT	(160.0f)	// 



class BonusTimer
{
private:
	ID3D11Buffer				*m_VertexBuffer = nullptr;		// 頂点情報
	ID3D11ShaderResourceView	*m_Texture[BONUS_TIMER_TEXTURE_MAX] = { NULL };	// テクスチャ情報

	char *m_TexturName[BONUS_TIMER_TEXTURE_MAX] = {
		"data/TEXTURE/tex_bonus_slotfont16x32.png",
	};

	BOOL m_Use;					// TRUE:使っている  FALSE:未使用
	float m_w, m_h;				// 幅と高さ
	XMFLOAT3 m_Pos;				// ポリゴンの座標
	int m_TexNo;				// テクスチャ番号

	float m_time;				// 時間


public:
	BonusTimer();
	~BonusTimer();

	void Update(void);
	void Draw(void);

	void SetTime(float time);

};