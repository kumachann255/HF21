#include "modeSelect.h"
#include "sound.h"
#include "input.h"
#include "fade.h"

BOOL g_keybord = TRUE;

ModeSelect::ModeSelect(God * god) :Scene(god)
{
	ID3D11Device *pDevice = GetDevice();

	//�e�N�X�`������
	for (int i = 0; i < MODESELECT_TEXTURE_MAX; i++)
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
	m_isKeyBord = TRUE;
	m_w = 960.0f;
	m_h = 540.0f;
	m_Pos = { m_w / 2, m_h / 2, 0.0f };
}

ModeSelect::~ModeSelect()
{
}

void ModeSelect::Init()
{
}

void ModeSelect::Update()
{
	if ((GetKeyboardTrigger(DIK_RIGHT)) || IsButtonTriggered(0, BUTTON_RIGHT) || (GetKeyboardTrigger(DIK_LEFT)) || IsButtonTriggered(0, BUTTON_LEFT))
	{
		if (m_isKeyBord) m_isKeyBord = FALSE;
		else m_isKeyBord = TRUE;

		// �T�E���h�炷
		PlaySound(SOUND_LABEL_SE_se_modeSelect_trance);
	}

	if (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_B))
	{
		SetFade(FADE_OUT, TUTORIAL_ID);

		// �T�E���h�炷
		PlaySound(SOUND_LABEL_SE_se_modeSelect_enter);
	}

	g_keybord = m_isKeyBord;
}

void ModeSelect::Draw()
{
	SetViewPort(TYPE_FULL_SCREEN);
	SetCameraAT(XMFLOAT3(0.0f, 0.0f, 0.0f));
	SetCamera();

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

	for (int i = 0; i < modeSelect_keybord; i++)
	{
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[i]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColor(m_VertexBuffer, m_Pos.x, m_Pos.y, m_w, m_h, 0.0f, 0.0f, 1.0f, 1.0f,
			XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}

	int texNum = modeSelect_keybord;
	if (!m_isKeyBord) texNum = modeSelect_pad;

	// �X�L�b�v�{�^���̕`��
	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture[texNum]);

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

BOOL GetPlayerType(void)
{
	return g_keybord;
}