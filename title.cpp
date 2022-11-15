//=============================================================================
//
// �^�C�g����ʏ��� [Title.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "camera.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "sound.h"
#include "sprite.h"
#include "Title.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_WIDTH				(SCREEN_WIDTH)	// �w�i�T�C�Y
#define TEXTURE_HEIGHT				(SCREEN_HEIGHT)	// 

#define TEXTURE_WIDTH_LOGO			(480)			// ���S�T�C�Y
#define TEXTURE_HEIGHT_LOGO			(80)			// 

enum
{
	TITLE_TEX_BG,
	TITLE_TEX_MAX
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

static char *g_TexturName[TEX_MAX] = {
	"data/TEXTURE/bg000.jpg",
	"data/TEXTURE/title_logo.png",
	"data/TEXTURE/effect000.jpg",
};


//=============================================================================
// �R���X�g���N�^�[
//=============================================================================
TitleUI::TitleUI()
{

	m_UIObject[TITLE_TEX_BG] = new UIObject;
	m_UIObject[TITLE_TEX_BG]->GetUITexData()->SetTextureName(g_TexturName[TITLE_TEX_BG]);
	m_UIObject[TITLE_TEX_BG]->GetUITexData()->Create();

	XMFLOAT3 pos = { TEXTURE_WIDTH / 2,TEXTURE_HEIGHT / 2,0.0f };
	m_UIObject[TITLE_TEX_BG]->SetPos(pos);
	m_UIObject[TITLE_TEX_BG]->SetWidth(TEXTURE_WIDTH);
	m_UIObject[TITLE_TEX_BG]->SetHeight(TEXTURE_HEIGHT);

}

//=============================================================================
// �f�X�g���N�^�[
//=============================================================================
TitleUI::~TitleUI()
{
	delete m_UIObject[0];
}


//*****************************************************************************
//*****************************************************************************




//=============================================================================
// �R���X�g���N�^�[ ���V�[���̃R���X�g���N�^�[�ɓn���Ă�����
//=============================================================================
Title::Title(God *god) : Scene(god)
{
	m_TitleUI = new TitleUI;
}

//=============================================================================
// �f�X�g���N�^�[
//=============================================================================
Title::~Title()
{
	delete m_TitleUI;
}

//=============================================================================
// ����������
//=============================================================================
void Title::Init(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void Title::Update(void)
{

	// �V�[���؂�ւ��`�F�b�N
	NextScene();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Title::Draw(void)
{
	// �r���[�|�[�g�̐؂芷��
	SetViewPort(TYPE_FULL_SCREEN);

	// 2D�̕���`�悷�鏈��
	// Z��r�Ȃ�
	SetDepthEnable(FALSE);

	// ���C�e�B���O�𖳌�
	SetLightEnable(FALSE);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, 
		m_TitleUI->GetUIObject()->GetUITexData()->GetpVertexBuffer(),
		&stride, &offset);

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
		GetDeviceContext()->PSSetShaderResources(0, 1,
			m_TitleUI->GetUIObject()->GetUITexData()->GetTexture()
		);

		SetSprite(m_TitleUI->GetUIObject()->GetUITexData()->GetVertexBuffer(),
			m_TitleUI->GetUIObject()->GetPos().x,
			m_TitleUI->GetUIObject()->GetPos().y,
			m_TitleUI->GetUIObject()->GetWidth(),
			m_TitleUI->GetUIObject()->GetHeight(),
			0.0f, 0.0f, 1.0f, 1.0f);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		//SetSpriteColorRotation(m_UITexData->GetVertexBuffer(),
		//	GetPos().x, GetPos().y, GetWidth(), GetHeight(),
		//	0.0f, 0.0f, 1.0f, 1.0f,
		//	GetColor(), GetRot());

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}

	// ���C�e�B���O��L����
	SetLightEnable(TRUE);

	// Z��r����
	SetDepthEnable(TRUE);
}

//=============================================================================
// �V�[���J�ڏ���
//=============================================================================
void Title::NextScene(void)
{
	// �t�F�[�h�A�E�g���J�n������
	if (GetKeyboardTrigger(DIK_1))
	{
		SetFade(FADE_OUT);
	}

	// �t�F�[�h�A�E�g���I�������V�[����؂�ւ���
	if (GetFadeOut_EndFlag())
	{
		GetGod()->ChangeScene(STAGE_01ID);

	}

}
