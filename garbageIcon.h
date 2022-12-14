#pragma once
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "sprite.h"
#include "UI.h"


#define GARBAGE_TEXTURE_MAX		(1)		// �e�N�X�`���̐�
#define GARBAGE_TEXTURE_WIDTH	(150.0f)	// �L�����T�C�Y
#define GARBAGE_TEXTURE_HEIGHT	(80.0f)	// 
#define GARBAGE_TEXTURE_DISTANCE	(30.0f)	// �L�����T�C�Y


class GarbageIcon
{
private:
	ID3D11Buffer				*m_VertexBuffer = nullptr;		// ���_���
	ID3D11ShaderResourceView	*m_Texture[GARBAGE_TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

	char *m_TexturName[GARBAGE_TEXTURE_MAX] = {
		"data/TEXTURE/tex_gomi_icon.png",
	};

	int m_iconNum = 20;
	float m_w, m_h;				// ���ƍ���
	XMFLOAT3 m_Pos;				// �|���S���̍��W
	int m_TexNo;				// �e�N�X�`���ԍ�


public:
	GarbageIcon();
	~GarbageIcon();

	void Update();
	void Draw();

	void SetIconNum(int num) { m_iconNum = num; };
};