#include "garbageIcon.h"

GarbageIcon::GarbageIcon()
{
	ID3D11Device *pDevice = GetDevice();

	//�e�N�X�`������
	for (int i = 0; i < GARBAGE_TEXTURE_MAX; i++)
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
	m_w = GARBAGE_TEXTURE_WIDTH;
	m_h = GARBAGE_TEXTURE_HEIGHT;
	m_Pos = { 95.0f, 493.0f, 0.0f };
	m_TexNo = 0;

	m_startColor = { 0.854f, 0.854f, 0.0f, 1.0f };
	m_endColor = { 1.0f, 0.282f, 0.333f, 1.0f };
}

GarbageIcon::~GarbageIcon()
{
}

void GarbageIcon::Update()
{
}

void GarbageIcon::Draw()
{
	// 2D�̕���`�悷�鏈��
	// Z��r�Ȃ�
	SetDepthEnable(FALSE);

	// ���C�e�B���O�𖳌�
	SetLightEnable(FALSE);

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

	XMFLOAT4 color;
	float p;
	float sclValue = 1.0f;

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[0]);

	for (int i = 0; i < m_iconNum; i++)
	{
		p = (float)i / (float)MAX_GARBAGE;
		color.x = m_startColor.x + (m_endColor.x - m_startColor.x) * p;
		color.y = m_startColor.y + (m_endColor.y - m_startColor.y) * p;
		color.z = m_startColor.z + (m_endColor.z - m_startColor.z) * p;
		color.w = 1.0f;

		if (i > 12)
		{
			sclValue *= SCL_VALUE_GARBAGE;
		}
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(m_VertexBuffer, m_Pos.x + i * GARBAGE_TEXTURE_DISTANCE, m_Pos.y - (m_h * sclValue - m_h) / 2.0f, m_w, m_h * sclValue, 0.0f, 0.0f, 1.0f, 1.0f,
			color);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[1]);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(m_VertexBuffer, 350.0f, 485.0f, 670.0f, 100.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);


	// ���C�e�B���O��L����
	SetLightEnable(TRUE);

	// Z��r����
	SetDepthEnable(TRUE);
}
