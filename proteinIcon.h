#pragma once
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "sprite.h"
#include "UI.h"


#define PROTEIN_TEXTURE_MAX		(1)		// �e�N�X�`���̐�
#define PROTEIN_TEXTURE_WIDTH	(80.0f)	// �L�����T�C�Y
#define PROTEIN_TEXTURE_HEIGHT	(100.0f)	// 
#define PROTEIN_TEXTURE_DISTANCE	(PROTEIN_TEXTURE_WIDTH)	// �L�����T�C�Y


class ProteinIcon
{
private:
	ID3D11Buffer				*m_VertexBuffer = nullptr;		// ���_���
	ID3D11ShaderResourceView	*m_Texture[PROTEIN_TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

	char *m_TexturName[PROTEIN_TEXTURE_MAX] = {
		"data/TEXTURE/tex_protein_icon.png",
	};

	int m_iconNum = 0;
	float m_w, m_h;				// ���ƍ���
	XMFLOAT3 m_Pos;				// �|���S���̍��W
	int m_TexNo;				// �e�N�X�`���ԍ�


public:
	ProteinIcon();
	~ProteinIcon();

	void Update();
	void Draw();

	void SetIconNum(int num);
};