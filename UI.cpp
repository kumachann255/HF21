//=============================================================================
//
// UI���� [UI.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "sprite.h"
#include "UI.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// �R���X�g���N�^�[
//=============================================================================
UITexData::UITexData()
{
}

//=============================================================================
// �����t���R���X�g���N�^�[
//=============================================================================
UITexData::UITexData(char *textureName) : m_TextureName(textureName)
{
	//Create();
}

//=============================================================================
// �e�N�X�`���[��������
//=============================================================================
HRESULT UITexData::Create(char *textureName)
{
	m_TextureName = textureName;

	// �e�N�X�`������
	D3DX11CreateShaderResourceViewFromFile(GetDevice(),
		m_TextureName,
		NULL,
		NULL,
		&m_Texture,
		NULL);

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &m_VertexBuffer);



	return S_OK;
}

//=============================================================================
// �f�X�g���N�^�[
//=============================================================================
UITexData::~UITexData()
{

	if (m_VertexBuffer)
	{
		m_VertexBuffer->Release();
		m_VertexBuffer = NULL;
	}

	if (m_Texture)
	{
		m_Texture->Release();
		m_Texture = NULL;
	}

}



//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================
//=============================================================================


//=============================================================================
// �R���X�g���N�^�[
//=============================================================================
UIObject::UIObject()
{
	m_UITexData = new UITexData;
	m_isUse = TRUE;
}

//=============================================================================
// �f�X�g���N�^�[
//=============================================================================
UIObject::~UIObject()
{
	delete m_UITexData;
}

//=============================================================================
// �X�V����
//=============================================================================
void UIObject::Update(void)
{
	m_timeCnt++;

	if (m_timeCnt > m_timeLimit)
	{
		m_isUse = FALSE;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void UIObject::Draw(void)
{

	if (!m_isUse) return;

	SetViewPort(TYPE_FULL_SCREEN);

	// 2D�̕���`�悷�鏈��
	// Z��r�Ȃ�
	SetDepthEnable(FALSE);

	// ���C�e�B���O�𖳌�
	SetLightEnable(FALSE);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, m_UITexData->GetpVertexBuffer(), &stride, &offset);

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	// �^�C�g���̔w�i��`��
	{
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, m_UITexData->GetTexture());

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSpriteColorRotation(m_UITexData->GetVertexBuffer(),
			m_pos.x, m_pos.y, m_fWidth, m_fHeight,
			0.0f, 0.0f, 1.0f, 1.0f,
			m_color, m_rot);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}

	// ���C�e�B���O��L����
	SetLightEnable(TRUE);

	// Z��r����
	SetDepthEnable(TRUE);
}

