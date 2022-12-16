#include "switch.h"

Switch::Switch()
{
	ID3D11Device *pDevice = GetDevice();

	//�e�N�X�`������
	for (int i = 0; i < SWITCH_TEXTURE_MAX; i++)
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
	m_w = SWITCH_TEXTURE_WIDTH;
	m_h = SWITCH_TEXTURE_HEIGHT;
	m_Pos = m_PosEffect = { 760.0f, 490.0f, 0.0f };

	for (int i = 0; i < 3; i++)
	{
		m_texNum[i] = 0;
	}
}

Switch::~Switch()
{
}

void Switch::Update()
{
	if (!m_isEffect) return;

	m_count++;
	if (m_count > SWITCH_EFFECT_LIFE) m_isEffect = FALSE;
}

void Switch::Draw()
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

	if (m_isEffect)
	{
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[2]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(m_VertexBuffer, m_PosEffect.x, m_PosEffect.y, m_w * 3.0f, m_h * 3.0f, 0.0f, 0.0f, 1.0f, 1.0f,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}

	for (int i = 0; i < 3; i++)
	{
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[m_texNum[i]]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(m_VertexBuffer, m_Pos.x - SWITCH_DISTANCE * i, m_Pos.y, m_w, m_h, 0.0f, 0.0f, 1.0f, 1.0f,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}

	// ���C�e�B���O��L����
	SetLightEnable(TRUE);

	// Z��r����
	SetDepthEnable(TRUE);
}

void Switch::SwitchON(int num)
{
	m_isEffect = TRUE;
	m_texNum[num] = 1;
	m_count = 0;
	m_PosEffect.x = m_Pos.x - SWITCH_DISTANCE * num;
}

void Switch::SwitchOFF(void)
{
	for (int i = 0; i < 3; i++)
	{
		m_texNum[i] = 0;
	}
}
