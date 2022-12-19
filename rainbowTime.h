#pragma once
#include "bonusTimer.h"

#define RAINBOE_TIMER_TEXTURE_WIDTH		(100)	// キャラサイズ
#define RAINBOE_TIMER_TEXTURE_HEIGHT	(100)	// 

class RainbowTimer
{
private:
	ID3D11Buffer				*m_VertexBuffer = nullptr;		// 頂点情報
	ID3D11ShaderResourceView	*m_Texture[BONUS_TIMER_TEXTURE_MAX] = { NULL };	// テクスチャ情報

	char *m_TexturName[BONUS_TIMER_TEXTURE_MAX] = {
		"data/TEXTURE/tex_rainbow_slotfont16x32.png",
		"data/TEXTURE/tex_num_priod.png",
	};

	BOOL m_Use;					// TRUE:使っている  FALSE:未使用
	float m_w, m_h;				// 幅と高さ
	XMFLOAT3 m_Pos;				// ポリゴンの座標
	int m_TexNo;				// テクスチャ番号
	float a = 0.0f;

	float m_time;				// 時間

public:
	RainbowTimer();
	~RainbowTimer() {};

	void Update();
	void Draw();

	void SetTime(float time);

	void SetUse(BOOL data) { 
		m_Use = data; 
		if (data) a = 1.0f;
	};
	BOOL GetUse(void) { return m_Use; };
};