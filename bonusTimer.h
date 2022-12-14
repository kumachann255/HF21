#pragma once
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "sprite.h"
#include "UI.h"

#define BONUS_TIMER_TEXTURE_MAX		(1)		// �e�N�X�`���̐�
#define BONUS_TIMER_TEXTURE_WIDTH	(80.0f)	// �L�����T�C�Y
#define BONUS_TIMER_TEXTURE_HEIGHT	(160.0f)	// 



class BonusTimer
{
private:
	ID3D11Buffer				*m_VertexBuffer = nullptr;		// ���_���
	ID3D11ShaderResourceView	*m_Texture[BONUS_TIMER_TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

	char *m_TexturName[BONUS_TIMER_TEXTURE_MAX] = {
		"data/TEXTURE/tex_bonus_slotfont16x32.png",
	};

	BOOL m_Use;					// TRUE:�g���Ă���  FALSE:���g�p
	float m_w, m_h;				// ���ƍ���
	XMFLOAT3 m_Pos;				// �|���S���̍��W
	int m_TexNo;				// �e�N�X�`���ԍ�

	float m_time;				// ����


public:
	BonusTimer();
	~BonusTimer();

	void Update(void);
	void Draw(void);

	void SetTime(float time);

};