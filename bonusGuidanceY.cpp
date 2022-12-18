#include "bonusGuidanceY.h"

BonusGuidance::BonusGuidance()
{
	ID3D11Device *pDevice = GetDevice();

	//�e�N�X�`������
	for (int i = 0; i < GUIDANCE_TEXTURE_MAX; i++)
	{
		m_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			m_TexturName[i],
			NULL,
			NULL,
			&m_Texture[i],
			NULL);
	}


	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);


	// �v���C���[�̏�����
	for (int i = 0; i < GUIDANCE_TEXTURE_MAX; i++)
	{
		m_Use[i] = TRUE;
		m_w[i] = GUIDANCE_TEXTURE_WIDTH;
		m_h[i] = GUIDANCE_TEXTURE_HEIGHT;
		m_Pos[i] = { 90.0f + (960.0f - 90.0f * 2) * i, 270.0f, 0.0f };
		m_UV[i] = { 0.0f, 0.0f };
	}
}

BonusGuidance::~BonusGuidance()
{
}

void BonusGuidance::Update(void)
{
	for (int i = 0; i < GUIDANCE_TEXTURE_MAX; i++)
	{
		m_UV[i].y += 0.001f - (GUIDANCE_SPEED * 2 * i);
		if (m_UV[i].y > 1.0f) m_UV[i].y = 0.0f;
		else if (m_UV[i].y < 0.0f) m_UV[i].y = 1.0f;
	}
}

void BonusGuidance::Draw(void)
{
	// 2D�̕���`�悷�鏈��
	// Z��r����i���Ƃ��Ԃ��Ă��܂�����j
	SetDepthEnable(FALSE);

	// ���C�e�B���O�𖳌�
	SetLightEnable(FALSE);

	SetAlphaTestEnable(TRUE);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	for (int i = 0; i < GUIDANCE_TEXTURE_MAX; i++)
	{
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[i]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(m_VertexBuffer, m_Pos[i].x, m_Pos[i].y, m_w[i], m_h[i], 0.0f, m_UV[i].y, 1.0f, 1.5f,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}

	// ���C�e�B���O��L����
	SetLightEnable(TRUE);

	// Z��r����
	SetDepthEnable(TRUE);
}
