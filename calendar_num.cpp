#include "calendar_num.h"

CalendarNum::CalendarNum(God *god) :GodObject(god)
{
	ID3D11Device *pDevice = GetDevice();

	//�e�N�X�`������
	for (int i = 0; i < CALENDAR_TEXTURE_MAX; i++)
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
	m_w[0] = CALENDAR_WAKU_TEXTURE_WIDTH;
	m_h[0] = CALENDAR_WAKU_TEXTURE_HEIGHT;
	m_Pos[0] = { 850.0f, 80.0f, 0.0f };

	m_w[1] = CALENDAR_TEXTURE_WIDTH;
	m_h[1] = CALENDAR_TEXTURE_HEIGHT;
	m_Pos[1] = { 850.0f, 85.0f, 0.0f };
}

CalendarNum::~CalendarNum()
{
}

void CalendarNum::Update()
{
	//if (m_month <= month_max) 
	{
		m_count += SOEED_CALENDAR;
	}

	// �����X�V
	if (m_count >= DIStANCE_CALENDAR)
	{
		AddMonth();
		m_count = 0.0f;

		if (m_month % 3 == 0)
		{
			m_swichfFlag = TRUE;

		}
	}
	else
	{
		m_swichfFlag = FALSE;

	}

	if (m_uvStartY < m_month * DIStANCE_CALENDAR)
	{
		m_uvStartY += SOEED_CALENDAR;
		//m_uvEndY += SOEED_CALENDAR;


	}
}

void CalendarNum::Draw()
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

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[0]);

	{
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(m_VertexBuffer, m_Pos[0].x, m_Pos[0].y, m_w[0], m_h[0], 0.0f, 0.0f, 1.0f, 1.0f,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[1]);

	{
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(m_VertexBuffer, m_Pos[1].x, m_Pos[1].y, m_w[1], m_h[1], 0.0f, m_uvStartY, 1.0f, m_uvEndY,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}

	// ���C�e�B���O��L����
	SetLightEnable(TRUE);

	// Z��r����
	SetDepthEnable(TRUE);
}
