#pragma once
#include "bonusTimer.h"

#define RAINBOE_TIMER_TEXTURE_WIDTH		(100)	// �L�����T�C�Y
#define RAINBOE_TIMER_TEXTURE_HEIGHT	(100)	// 

class RainbowTimer
{
private:
	ID3D11Buffer				*m_VertexBuffer = nullptr;		// ���_���
	ID3D11ShaderResourceView	*m_Texture[BONUS_TIMER_TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

	char *m_TexturName[BONUS_TIMER_TEXTURE_MAX] = {
		"data/TEXTURE/tex_rainbow_slotfont16x32.png",
		"data/TEXTURE/tex_num_priod.png",
	};

	BOOL m_Use;					// TRUE:�g���Ă���  FALSE:���g�p
	float m_w, m_h;				// ���ƍ���
	XMFLOAT3 m_Pos;				// �|���S���̍��W
	int m_TexNo;				// �e�N�X�`���ԍ�
	float a = 0.0f;

	float m_time;				// ����

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