#include "tutorialBG.h"
#include "modeSelect.h"

TutorialBG::TutorialBG()
{
	ID3D11Device *pDevice = GetDevice();

	//�e�N�X�`������
	for (int i = 0; i < TUTORIALBG_TEXTURE_MAX; i++)
	{
		m_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			m_TexturName[i],
			NULL,
			NULL,
			&m_Texture[i],
			NULL);

		m_Use[i] = FALSE;
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
	m_Use[0] = TRUE;
	m_w = 960.0f;
	m_h = 540.0f;
	m_Pos = { m_w / 2, m_h / 2, 0.0f };

}

void TutorialBG::Update()
{
}

void TutorialBG::Draw()
{
	// 2D�̕���`�悷�鏈��
	// Z��r����i���Ƃ��Ԃ��Ă��܂�����j
	SetDepthEnable(FALSE);

	// ���C�e�B���O�𖳌�
	SetLightEnable(FALSE);

	// FALSE��������
	SetAlphaTestEnable(FALSE);

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

	for (int i = 0; i < TUTORIALBG_TEXTURE_MAX - 1; i++)
	{
		if (!m_Use[i]) continue;

		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[i]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(m_VertexBuffer, m_Pos.x, m_Pos.y, m_w, m_h, 0.0f, 0.0f, 1.0f, 1.0f,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}

	// �X�L�b�v�{�^���̕`��
	// �e�N�X�`���ݒ�
	if (GetPlayerType())
	{	// �L�[�{�[�h
		GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[tutorial_skip]);
	}
	else
	{	// �p�b�h
		GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[tutorial_skip_pad]);
	}

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSpriteColor(m_VertexBuffer, m_Pos.x, m_Pos.y, m_w, m_h, 0.0f, 0.0f, 1.0f, 1.0f,
		XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

	// FALSE��������
	SetAlphaTestEnable(TRUE);

	// ���C�e�B���O��L����
	SetLightEnable(TRUE);

	// Z��r����
	SetDepthEnable(TRUE);

}

void TutorialBG::SetTex(int num, BOOL data)
{
	m_Use[num] = data;
}

void TutorialBG::Init()
{
	for (int i = 0; i < TUTORIALBG_TEXTURE_MAX; i++)
	{
		m_Use[i] = FALSE;
	}
	m_Use[0] = TRUE;
}
