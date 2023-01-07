//=============================================================================
//
// �X�^�b�t���[����ʏ��� [Staffroll.cpp]
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
#include "Staffroll.h"
#include "debugproc.h"
#include "texManager.h"
#include "QuestBoardManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX				(14)		// �e�N�X�`���̐�
#define DEBUGPOS_PRESS_ADD		(5.0f)	// �f�o�b�O�pPOS�̉����Z�pPRESS
#define DEBUGPOS_TRIGGER_ADD	(1.0f)	// �f�o�b�O�pPOS�̉����Z�pTRIGGER
#define SCROLL_VALUE			(2.0f)	// �X�N���[���p�����l

//*****************************************************************************
// �O���[�o���ϐ�
static ID3D11Buffer				*g_VertexBuffer = NULL;		// ���_���
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char *g_TexturName2[TEXTURE_MAX] = {
	"data/TEXTURE/STAFFROLL/endScroll.png",
	"data/TEXTURE/STAFFROLL/resultBG.png",
	"data/TEXTURE/STAFFROLL/seika.png",
	"data/TEXTURE/STAFFROLL/goldBar.png",
	"data/TEXTURE/STAFFROLL/silverBar.png",
	"data/TEXTURE/STAFFROLL/bronzeBar.png",
	"data/TEXTURE/STAFFROLL/blueBar.png",
	"data/TEXTURE/STAFFROLL/greenBar.png",
	"data/TEXTURE/STAFFROLL/goldRunk.png",
	"data/TEXTURE/STAFFROLL/silverRunk.png",
	"data/TEXTURE/STAFFROLL/bronzeRunk.png",
	"data/TEXTURE/STAFFROLL/blueRunk.png",
	"data/TEXTURE/STAFFROLL/greenRunk.png",
	"data/TEXTURE/STAFFROLL/factcheck_mark.png"

};

static BOOL						g_Load = FALSE;

// �X�^�b�t���[���I�u�W�F�N�g�̃C���X�^���X
s_StaffRoll staffRoll[STAFFROLL_MAX];
// �`�F�b�N�}�[�N�I�u�W�F�N�g�̃C���X�^���X
s_Check check[CHECK_MAX];


//=============================================================================
// �R���X�g���N�^�[ ���V�[���̃R���X�g���N�^�[�ɓn���Ă�����
//=============================================================================
StaffRoll::StaffRoll(God *god) : Scene(god)
{
	InitStaffRoll();
}

//=============================================================================
// �f�X�g���N�^�[
//=============================================================================
StaffRoll::~StaffRoll()
{
	UninitStaffRoll();
}

//=============================================================================
// ����������
//=============================================================================
void StaffRoll::Init(void)
{
	m_Mode = RESULT;
	m_ScrollSw = false;	// �X�N���[���J�n�pSW
	m_DebugSwich = true;	// �f�o�b�O���[�h�؂�ւ��pSW
	m_DebugNum = 0;			// �f�o�b�O�p�ϐ�
	m_StopTime = 0;
	m_isTelop = false;		// �e���b�v���o�������ǂ���
	m_isWait = 0;
}

//=============================================================================
// �X�V����
//=============================================================================
void StaffRoll::Update(void)
{
	if (GetKeyboardTrigger(DIK_1))
	{
		SetFade(FADE_OUT, TITLE_ID);
	}


	// �m���}�̃e���b�v�\��
	if (!m_isTelop)
	{
		m_isTelop = true;
		GetGod()->GetTexManager()->GetUIManager()->SetTexture(
			result_clear, texType_cutIn_left, XMFLOAT3(600.0f, 400.0f, 0.0f), 4);

		GetGod()->GetTexManager()->GetUIManager()->SetTexture(
			result_false, texType_cutIn_left, XMFLOAT3(600.0f, 400.0f, 0.0f), 4);
	}

	switch (m_Mode)
	{
	case RESULT:
		// ��������(�{���͍ŏI�I��m_IconNum����ꂽ��)
		int sample_iconNum;
		sample_iconNum = GetPoint();

		if (sample_iconNum >= 15)
		{
			sample_iconNum = 15;
		}

		CheckIcon(&sample_iconNum);
		break;

	case GREEN:
		CheckMark(&check[0].checkTime, &check[0].g_Use);


		if (check[0].checkTime == 0)
		{
			//�J�n
			Slide(&staffRoll[7].g_Pos.x);
		}
		break;

	case BLUE:
		for (int i = 0; i < 2; i++)
		{
			CheckMark(&check[i].checkTime, &check[i].g_Use);
			// �P�c�̃`�F�b�N�ɍ��킹��
			if (check[1].checkTime == 0)
			{
				Slide(&staffRoll[6].g_Pos.x);
			}
		}
		break;

	case BRONSE:
		for (int i = 0; i < 3; i++)
		{
			CheckMark(&check[i].checkTime, &check[i].g_Use);
			// �P�c�̃`�F�b�N�ɍ��킹��
			if (check[2].checkTime == 0)
			{
				Slide(&staffRoll[5].g_Pos.x);
			}
		}

		break;

	case SILVER:
		for (int i = 0; i < 4; i++)
		{
			CheckMark(&check[i].checkTime, &check[i].g_Use);
			// �P�c�̃`�F�b�N�ɍ��킹��
			if (check[3].checkTime == 0)
			{
				Slide(&staffRoll[4].g_Pos.x);
			}
		}

		break;

	case GOLD:
		for (int i = 0; i < 5; i++)
		{
			CheckMark(&check[i].checkTime, &check[i].g_Use);
			// �P�c�̃`�F�b�N�ɍ��킹��
			if (check[4].checkTime == 0)
			{
				Slide(&staffRoll[3].g_Pos.x);
			}
		}

		break;

	case ENDROLL:
		switch (m_ScrollSw)
		{
		case true:
			Scroll(&staffRoll[0].g_Pos.y);
			break;

		case false:
			Stop();
		}
		break;
	}

	GetGod()->GetTexManager()->Update();

#ifdef _DEBUG	// �f�o�b�O����\������


	// �@�f�o�b�O�Ώۂ̐؂�ւ�
	ChangeNum(&m_DebugNum);

	// �A2D�摜�ʒu�m�F
	DebugPrint(staffRoll[m_DebugNum].g_Pos.x, staffRoll[m_DebugNum].g_Pos.y, staffRoll[m_DebugNum].g_w, staffRoll[m_DebugNum].g_h);

	// �B2D�摜�ʒu�ύX
	PosCustom(&staffRoll[m_DebugNum].g_Pos.x, &staffRoll[m_DebugNum].g_Pos.y); // �z��̗v�f���Ƀf�o�b�N�ԍ������鎖�Łi�f�o�b�N�Ώ�==�f�o�b�N�ԍ��j�Ƃ���

	// �C2D�摜�T�C�Y�ύX
	SizeCustom(&staffRoll[m_DebugNum].g_w, &staffRoll[m_DebugNum].g_h); // �z��̗v�f���Ƀf�o�b�N�ԍ������鎖�Łi�f�o�b�N�Ώ�==�f�o�b�N�ԍ��j�Ƃ���

	/* ���̗��ꂪ�d�v�IChangeNum()�֐��Ń����o�ϐ���m_DebugNum�ɃA�N�Z�X���ăf�o�b�N�Ώۂ����߂āA����𔽉f�����Ă���ʒu�m�F�A�ʒu�m�F�����Ă���*/

	// �V�[���؂�ւ��`�F�b�N
	NextScene();

#endif


}

//=============================================================================
// �`�揈��
//=============================================================================
void StaffRoll::Draw(void)
{
	SetViewPort(TYPE_FULL_SCREEN);

	// ���C�g��L����
	SetLightEnable(FALSE);

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer, &stride, &offset);

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();

	// �v���~�e�B�u�g�|���W�ݒ�
	GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	switch (m_Mode)
	{
	case RESULT:
		/* �w�i */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[1].g_Pos.x, staffRoll[1].g_Pos.y, staffRoll[1].g_w, staffRoll[1].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* ����Bar */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[2]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[2].g_Pos.x, staffRoll[2].g_Pos.y, staffRoll[2].g_w, staffRoll[2].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NGold */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[8]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[8].g_Pos.x, staffRoll[8].g_Pos.y, staffRoll[8].g_w, staffRoll[8].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NSilver */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[9]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[9].g_Pos.x, staffRoll[9].g_Pos.y, staffRoll[9].g_w, staffRoll[9].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NBlonze */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[10]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[10].g_Pos.x, staffRoll[10].g_Pos.y, staffRoll[10].g_w, staffRoll[10].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NBlue */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[11]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[11].g_Pos.x, staffRoll[11].g_Pos.y, staffRoll[11].g_w, staffRoll[11].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NGreen */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[12]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[12].g_Pos.x, staffRoll[12].g_Pos.y, staffRoll[12].g_w, staffRoll[12].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		break;

	case GREEN:
		/* �w�i */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[1].g_Pos.x, staffRoll[1].g_Pos.y, staffRoll[1].g_w, staffRoll[1].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* ����Bar */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[2]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[2].g_Pos.x, staffRoll[2].g_Pos.y, staffRoll[2].g_w, staffRoll[2].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NGold */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[8]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[8].g_Pos.x, staffRoll[8].g_Pos.y, staffRoll[8].g_w, staffRoll[8].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NSilver */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[9]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[9].g_Pos.x, staffRoll[9].g_Pos.y, staffRoll[9].g_w, staffRoll[9].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NBlonze */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[10]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[10].g_Pos.x, staffRoll[10].g_Pos.y, staffRoll[10].g_w, staffRoll[10].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NBlue */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[11]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[11].g_Pos.x, staffRoll[11].g_Pos.y, staffRoll[11].g_w, staffRoll[11].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NGreen */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[12]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[12].g_Pos.x, staffRoll[12].g_Pos.y, staffRoll[12].g_w, staffRoll[12].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		if (check[0].g_Use == TRUE)
		{
			/* �`�F�b�N�}�[�N */
			// �e�N�X�`���ݒ�
			GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[13]);
			// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
			SetSprite(g_VertexBuffer, check[0].g_Pos.x, check[0].g_Pos.y, check[0].g_w, check[0].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
			// �|���S���`��
			GetDeviceContext()->Draw(4, 0);
		}

		/* �����NBar */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[7]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[7].g_Pos.x, staffRoll[7].g_Pos.y, staffRoll[7].g_w, staffRoll[7].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		break;

	case BLUE:
		/* �w�i */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[1].g_Pos.x, staffRoll[1].g_Pos.y, staffRoll[1].g_w, staffRoll[1].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* ����Bar */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[2]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[2].g_Pos.x, staffRoll[2].g_Pos.y, staffRoll[2].g_w, staffRoll[2].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NGold */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[8]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[8].g_Pos.x, staffRoll[8].g_Pos.y, staffRoll[8].g_w, staffRoll[8].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NSilver */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[9]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[9].g_Pos.x, staffRoll[9].g_Pos.y, staffRoll[9].g_w, staffRoll[9].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NBlonze */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[10]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[10].g_Pos.x, staffRoll[10].g_Pos.y, staffRoll[10].g_w, staffRoll[10].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NBlue */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[11]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[11].g_Pos.x, staffRoll[11].g_Pos.y, staffRoll[11].g_w, staffRoll[11].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NGreen */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[12]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[12].g_Pos.x, staffRoll[12].g_Pos.y, staffRoll[12].g_w, staffRoll[12].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		for (int i = 0; i < 2; i++)
		{
			if (check[i].g_Use == TRUE)
			{
				/* �`�F�b�N�}�[�N */
				// �e�N�X�`���ݒ�
				GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[13]);
				// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
				SetSprite(g_VertexBuffer, check[i].g_Pos.x, check[i].g_Pos.y, check[i].g_w, check[i].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
				// �|���S���`��
				GetDeviceContext()->Draw(4, 0);
			}
		}

		/* �����NBar */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[6]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[6].g_Pos.x, staffRoll[6].g_Pos.y, staffRoll[6].g_w, staffRoll[6].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		break;

	case BRONSE:
		/* �w�i */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[1].g_Pos.x, staffRoll[1].g_Pos.y, staffRoll[1].g_w, staffRoll[1].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* ����Bar */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[2]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[2].g_Pos.x, staffRoll[2].g_Pos.y, staffRoll[2].g_w, staffRoll[2].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NGold */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[8]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[8].g_Pos.x, staffRoll[8].g_Pos.y, staffRoll[8].g_w, staffRoll[8].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NSilver */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[9]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[9].g_Pos.x, staffRoll[9].g_Pos.y, staffRoll[9].g_w, staffRoll[9].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NBlonze */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[10]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[10].g_Pos.x, staffRoll[10].g_Pos.y, staffRoll[10].g_w, staffRoll[10].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NBlue */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[11]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[11].g_Pos.x, staffRoll[11].g_Pos.y, staffRoll[11].g_w, staffRoll[11].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NGreen */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[12]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[12].g_Pos.x, staffRoll[12].g_Pos.y, staffRoll[12].g_w, staffRoll[12].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		for (int i = 0; i < 3; i++)
		{
			if (check[i].g_Use == TRUE)
			{
				/* �`�F�b�N�}�[�N */
				// �e�N�X�`���ݒ�
				GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[13]);
				// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
				SetSprite(g_VertexBuffer, check[i].g_Pos.x, check[i].g_Pos.y, check[i].g_w, check[i].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
				// �|���S���`��
				GetDeviceContext()->Draw(4, 0);
			}
		}

		/* �����NBar */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[5]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[5].g_Pos.x, staffRoll[5].g_Pos.y, staffRoll[5].g_w, staffRoll[5].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);


		break;

	case SILVER:
		/* �w�i */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[1].g_Pos.x, staffRoll[1].g_Pos.y, staffRoll[1].g_w, staffRoll[1].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* ����Bar */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[2]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[2].g_Pos.x, staffRoll[2].g_Pos.y, staffRoll[2].g_w, staffRoll[2].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NGold */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[8]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[8].g_Pos.x, staffRoll[8].g_Pos.y, staffRoll[8].g_w, staffRoll[8].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NSilver */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[9]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[9].g_Pos.x, staffRoll[9].g_Pos.y, staffRoll[9].g_w, staffRoll[9].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NBlonze */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[10]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[10].g_Pos.x, staffRoll[10].g_Pos.y, staffRoll[10].g_w, staffRoll[10].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NBlue */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[11]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[11].g_Pos.x, staffRoll[11].g_Pos.y, staffRoll[11].g_w, staffRoll[11].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NGreen */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[12]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[12].g_Pos.x, staffRoll[12].g_Pos.y, staffRoll[12].g_w, staffRoll[12].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		for (int i = 0; i < 4; i++)
		{
			if (check[i].g_Use == TRUE)
			{
				/* �`�F�b�N�}�[�N */
				// �e�N�X�`���ݒ�
				GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[13]);
				// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
				SetSprite(g_VertexBuffer, check[i].g_Pos.x, check[i].g_Pos.y, check[i].g_w, check[i].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
				// �|���S���`��
				GetDeviceContext()->Draw(4, 0);
			}
		}

		/* �����NBar */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[4]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[4].g_Pos.x, staffRoll[4].g_Pos.y, staffRoll[4].g_w, staffRoll[4].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		break;

	case GOLD:
		/* �w�i */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[1]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[1].g_Pos.x, staffRoll[1].g_Pos.y, staffRoll[1].g_w, staffRoll[1].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* ����Bar */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[2]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[2].g_Pos.x, staffRoll[2].g_Pos.y, staffRoll[2].g_w, staffRoll[2].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NGold */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[8]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[8].g_Pos.x, staffRoll[8].g_Pos.y, staffRoll[8].g_w, staffRoll[8].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NSilver */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[9]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[9].g_Pos.x, staffRoll[9].g_Pos.y, staffRoll[9].g_w, staffRoll[9].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NBlonze */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[10]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[10].g_Pos.x, staffRoll[10].g_Pos.y, staffRoll[10].g_w, staffRoll[10].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NBlue */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[11]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[11].g_Pos.x, staffRoll[11].g_Pos.y, staffRoll[11].g_w, staffRoll[11].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		/* �����NGreen */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[12]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[12].g_Pos.x, staffRoll[12].g_Pos.y, staffRoll[12].g_w, staffRoll[12].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		for (int i = 0; i < 5; i++)
		{
			if (check[i].g_Use == TRUE)
			{
				/* �`�F�b�N�}�[�N */
				// �e�N�X�`���ݒ�
				GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[13]);
				// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
				SetSprite(g_VertexBuffer, check[i].g_Pos.x, check[i].g_Pos.y, check[i].g_w, check[i].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
				// �|���S���`��
				GetDeviceContext()->Draw(4, 0);
			}
		}

		/* �����NBar */
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[3]);
		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[3].g_Pos.x, staffRoll[3].g_Pos.y, staffRoll[3].g_w, staffRoll[3].g_h, 0.0f, 0.0f, 1.0f, 1.0f);
		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);

		GetGod()->GetTexManager()->Draw();

		break;

	case ENDROLL:
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[0]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, staffRoll[0].g_Pos.x, staffRoll[0].g_Pos.y, staffRoll[0].g_w, staffRoll[0].g_h, 0.0f, 0.0f, 1.0f, 1.0f);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
		break;
	}
}

//=============================================================================
// �V�[���J�ڏ���
//=============================================================================
void StaffRoll::NextScene(void)
{
	// �v���[�����\�p
	// #ifdef _DEBUG	// �f�o�b�O����\������
		// �t�F�[�h�A�E�g���J�n������
	if (GetKeyboardTrigger(DIK_1) || IsButtonTriggered(0, BUTTON_START))
	{
		SetFade(FADE_OUT, TITLE_ID);
	}
	// #endif
		
	//// �t�F�[�h�A�E�g���I�������
	//if (GetFadeOut_EndFlag())
	//{

	//}
}

void StaffRoll::Stop(void)
{
	m_StopTime++;
	if (m_StopTime == MAX_STOPTIME)
	{
		m_ScrollSw = true;
		m_StopTime = 0;
	}
}

void StaffRoll::Scroll(float *posY)
{
	*posY -= SCROLL_VALUE;
	if (*posY < -1460.0f)
	{
		*posY = -1460.0f;
		SetFade(FADE_OUT, TITLE_ID);
	}
}

//=============================================================================
// �f�o�b�N�@�\�S��(�n�܂�)
//=============================================================================

int StaffRoll::ChangeNum(int * Num)
{
	int r;

	r = *Num;

	if (GetKeyboardTrigger(DIK_SPACE))
	{
		r += 1;

		if (r > STAFFROLL_MAX - 1)
		{
			r = 0;
		}
	}

	*Num = r;

	return *Num;
}

// �f�o�b�O�̏��̕\��
void StaffRoll::DebugPrint(float posX, float posY, float w, float h) // �\���������f�o�b�O�Ώۂ̍��W�̈�����2�����
{
	PrintDebugProc("checkTime : %d\n", check[0].checkTime);
	PrintDebugProc("m_Mode : %d\n", m_Mode);
	PrintDebugProc("�f�o�b�O�Ώۂ̐؂�ւ� : SPACE�L�[\n");
	PrintDebugProc("�f�o�b�O�Ώۂ̏�ړ� : ���L�[ , �f�o�b�O�Ώۂ̉��ړ� : ���L�[\n");
	PrintDebugProc("�f�o�b�O�Ώۂ̉E�ړ� : ���L�[ , �f�o�b�O�Ώۂ̍��ړ� : ���L�[\n");
	PrintDebugProc("�f�o�b�O�Ώۂ�X�����g�� : D�L�[ , �f�o�b�O�Ώۂ�X�������k : A�L�[\n");
	PrintDebugProc("�f�o�b�O�Ώۂ�Y�����g�� : W�L�[ , �f�o�b�O�Ώۂ�Y�������k : S�L�[\n");
	PrintDebugProc("�f�o�b�O�Ώۂ̈ړ��ʕύX�{�^�� : C�L�[\n");
	PrintDebugProc("�f�o�b�N�Ώ� : staffRoll[%d] \n", m_DebugNum);
	PrintDebugProc("�f�o�b�N�|�W�V���� : PosX : %f, DebugPosY : %f\n", posX, posY);
	PrintDebugProc("�f�o�b�N�T�C�Y : SizeWidth : %f, SizeHeight : %f\n", w, h);
}

// �f�o�b�O�Ώۂ̈ʒu�ύX
void StaffRoll::PosCustom(float *posX, float *posY) // �ړ��������f�o�b�O�Ώۂ̍��W�̈�����2�i�|�C���^�j�����
{
	if (GetKeyboardTrigger(DIK_C))
	{
		if (m_DebugSwich)
		{
			m_DebugSwich = false;
		}
		else
		{
			m_DebugSwich = true;
		}
	}

	switch (m_DebugSwich)
	{
	case true:
		// ������Ă���ԁAY������Ɉړ�
		if (GetKeyboardTrigger(DIK_UP))
		{
			*posY -= DEBUGPOS_TRIGGER_ADD;
		}
		// ������Ă���ԁAY�������Ɉړ�
		if (GetKeyboardTrigger(DIK_DOWN))
		{
			*posY += DEBUGPOS_TRIGGER_ADD;
		}
		// ������Ă���ԁAX�E�����ɉ��Z
		if (GetKeyboardTrigger(DIK_RIGHT))
		{
			*posX += DEBUGPOS_TRIGGER_ADD;
		}
		// ������Ă���ԁAX�������ɉ��Z
		if (GetKeyboardTrigger(DIK_LEFT))
		{
			*posX -= DEBUGPOS_TRIGGER_ADD;
		}
		break;

	case false:
		// ������Ă���ԁAY������Ɉړ�
		if (GetKeyboardPress(DIK_UP))
		{
			*posY -= DEBUGPOS_PRESS_ADD;
		}
		// ������Ă���ԁAY�������Ɉړ�
		if (GetKeyboardPress(DIK_DOWN))
		{
			*posY += DEBUGPOS_PRESS_ADD;
		}
		// ������Ă���ԁAX�E�����ɉ��Z
		if (GetKeyboardPress(DIK_RIGHT))
		{
			*posX += DEBUGPOS_PRESS_ADD;
		}
		// ������Ă���ԁAX�������ɉ��Z
		if (GetKeyboardPress(DIK_LEFT))
		{
			*posX -= DEBUGPOS_TRIGGER_ADD;
		}
	}
}

void StaffRoll::SizeCustom(float *width, float *height)
{
	switch (m_DebugSwich)
	{
	case true:
		// ������Ă���ԁAY�����Ɏ��k
		if (GetKeyboardTrigger(DIK_S))
		{
			*height -= DEBUGPOS_TRIGGER_ADD;
		}
		// ������Ă���ԁAY�����Ɋg��
		if (GetKeyboardTrigger(DIK_W))
		{
			*height += DEBUGPOS_TRIGGER_ADD;
		}
		// ������Ă���ԁAX�����Ɋg��
		if (GetKeyboardTrigger(DIK_D))
		{
			*width += DEBUGPOS_TRIGGER_ADD;
		}
		// ������Ă���ԁAX�����Ɏ��k
		if (GetKeyboardTrigger(DIK_A))
		{
			*width -= DEBUGPOS_TRIGGER_ADD;
		}
		break;

	case false:
		// ������Ă���ԁAY�����Ɏ��k
		if (GetKeyboardPress(DIK_S))
		{
			*height -= DEBUGPOS_PRESS_ADD;
		}
		// ������Ă���ԁAY�����Ɋg��
		if (GetKeyboardPress(DIK_W))
		{
			*height += DEBUGPOS_PRESS_ADD;
		}
		// ������Ă���ԁAX�����Ɋg��
		if (GetKeyboardPress(DIK_D))
		{
			*width += DEBUGPOS_PRESS_ADD;
		}
		// ������Ă���ԁAX�����Ɏ��k
		if (GetKeyboardPress(DIK_A))
		{
			*width -= DEBUGPOS_PRESS_ADD;
		}
	}

}

void StaffRoll::CheckIcon(int *m_icon)
{
	switch (*m_icon)
	{
	case 0:
		SetRank(GREEN);
		break;
	case 1:
		SetRank(GREEN);
		break;
	case 2:
		SetRank(GREEN);
		break;
	case 3:
		SetRank(GREEN);
		break;
	case 4:
		SetRank(GREEN);
		break;
	case 5:
		SetRank(GREEN);
		break;
	case 6:
		SetRank(BLUE);
		break;
	case 7:
		SetRank(BLUE);
		break;
	case 8:
		SetRank(BLUE);
		break;
	case 9:
		SetRank(BLUE);
		break;
	case 10:
		SetRank(BRONSE);
		break;
	case 11:
		SetRank(BRONSE);
		break;
	case 12:
		SetRank(BRONSE);
		break;
	case 13:
		SetRank(SILVER);
		break;
	case 14:
		SetRank(SILVER);
		break;
	case 15:
		SetRank(GOLD);
		break;
	}
}

void StaffRoll::CheckMark(int *time, BOOL *use)
{
	if (*time > 0)
	{
		*time = *time - 1;
		if (*time == 0)
		{
			*use = TRUE;
			*time = 0;
		}
	}
}

void StaffRoll::Slide(float *posX)
{
	*posX -= SCROLL_VALUE;
	if (*posX < SCREEN_CENTER_X)
	{
		*posX = SCREEN_CENTER_X;
		m_isWait++;
		
		if (m_isWait > 180)
		{
			m_Mode = ENDROLL;
		}
	}
}

void StaffRoll::SetRank(int mode)
{
	m_Mode = mode;
}


//=============================================================================
// �f�o�b�N�@�\�S��(�I���)
//=============================================================================

//=============================================================================
// ����������
//=============================================================================
HRESULT InitStaffRoll(void)
{
	ID3D11Device *pDevice = GetDevice();

	//�e�N�X�`������
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TexturName2[i],
			NULL,
			NULL,
			&g_Texture[i],
			NULL);
	}


	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer);

	// �ϐ��̏�����(SCROLL)
	staffRoll[0].g_Use = TRUE;
	staffRoll[0].g_w = SCREEN_WIDTH;
	staffRoll[0].g_h = 4000;
	staffRoll[0].g_Pos = XMFLOAT3(SCREEN_CENTER_X, 2000.0f, 0.0f); // END��-1460.0f
	staffRoll[0].g_TexNo = 0;

	// �ϐ��̏������i�w�i�j
	staffRoll[1].g_Use = TRUE;
	staffRoll[1].g_w = 980;
	staffRoll[1].g_h = 555;
	staffRoll[1].g_Pos = XMFLOAT3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	staffRoll[1].g_TexNo = 1;

	// �ϐ��̏������i����Bar�j
	staffRoll[2].g_Use = TRUE;
	staffRoll[2].g_w = 310;
	staffRoll[2].g_h = 125;
	staffRoll[2].g_Pos = XMFLOAT3(770.0f, 90.0f, 0.0f);
	staffRoll[2].g_TexNo = 2;

	// �ϐ��̏������i�����NBar�S�[���h�j
	staffRoll[3].g_Use = TRUE;
	staffRoll[3].g_w = 510;
	staffRoll[3].g_h = 130;
	staffRoll[3].g_Pos = XMFLOAT3(1500.0f, 235.0f, 0.0f);
	staffRoll[3].g_TexNo = 3;

	// �ϐ��̏������i�����NBar�V���o�[�j
	staffRoll[4].g_Use = TRUE;
	staffRoll[4].g_w = 510;
	staffRoll[4].g_h = 130;
	staffRoll[4].g_Pos = XMFLOAT3(1500.0f, 235.0f, 0.0f);
	staffRoll[4].g_TexNo = 4;

	// �ϐ��̏������i�����NBar�u�����Y�j
	staffRoll[5].g_Use = TRUE;
	staffRoll[5].g_w = 510;
	staffRoll[5].g_h = 130;
	staffRoll[5].g_Pos = XMFLOAT3(1500.0f, 235.0f, 0.0f);
	staffRoll[5].g_TexNo = 5;

	// �ϐ��̏������i�����NBar�u���[�j
	staffRoll[6].g_Use = TRUE;
	staffRoll[6].g_w = 510;
	staffRoll[6].g_h = 130;
	staffRoll[6].g_Pos = XMFLOAT3(1500.0f, 235.0f, 0.0f);
	staffRoll[6].g_TexNo = 6;

	// �ϐ��̏������i�����NBar�O���[���j
	staffRoll[7].g_Use = TRUE;
	staffRoll[7].g_w = 510;
	staffRoll[7].g_h = 130;
	staffRoll[7].g_Pos = XMFLOAT3(1500.0f, 235.0f, 0.0f);
	staffRoll[7].g_TexNo = 7;

	// �ϐ��̏������i�S�[���hRunk�j
	staffRoll[8].g_Use = TRUE;
	staffRoll[8].g_w = 180;
	staffRoll[8].g_h = 130;
	staffRoll[8].g_Pos = XMFLOAT3(810.0f, 445.0f, 0.0f);
	staffRoll[8].g_TexNo = 8;

	// �ϐ��̏������i�V���o�[Runk�j
	staffRoll[9].g_Use = TRUE;
	staffRoll[9].g_w = 180;
	staffRoll[9].g_h = 130;
	staffRoll[9].g_Pos = XMFLOAT3(630.0f, 385.0f, 0.0f);
	staffRoll[9].g_TexNo = 9;

	// �ϐ��̏������i�u�����YRunk�j
	staffRoll[10].g_Use = TRUE;
	staffRoll[10].g_w = 180;
	staffRoll[10].g_h = 130;
	staffRoll[10].g_Pos = XMFLOAT3(SCREEN_CENTER_X, 465.0f, 0.0f);
	staffRoll[10].g_TexNo = 10;

	// �ϐ��̏������i�u���[Runk�j
	staffRoll[11].g_Use = TRUE;
	staffRoll[11].g_w = 180;
	staffRoll[11].g_h = 130;
	staffRoll[11].g_Pos = XMFLOAT3(330.0f, 385.0f, 0.0f);
	staffRoll[11].g_TexNo = 11;

	// �ϐ��̏������i�O���[��Runk�j
	staffRoll[12].g_Use = TRUE;
	staffRoll[12].g_w = 180;
	staffRoll[12].g_h = 130;
	staffRoll[12].g_Pos = XMFLOAT3(150.0f, 445.0f, 0.0f);
	staffRoll[12].g_TexNo = 12;

	// �ϐ��̏������i�`�F�b�N�}�[�N�j
	for (int i = 0; i < CHECK_MAX; i++)
	{
		check[i].g_Use = FALSE;
		check[i].g_w = 180;
		check[i].g_h = 130;
		check[i].g_TexNo = 13;
	}

	check[0].g_Pos = XMFLOAT3(150.0f, 445.0f, 0.0f);
	check[1].g_Pos = XMFLOAT3(330.0f, 385.0f, 0.0f);
	check[2].g_Pos = XMFLOAT3(SCREEN_CENTER_X, 465.0f, 0.0f);
	check[3].g_Pos = XMFLOAT3(630.0f, 385.0f, 0.0f);
	check[4].g_Pos = XMFLOAT3(810.0f, 445.0f, 0.0f);

	check[0].checkTime = 75;
	check[1].checkTime = 150;
	check[2].checkTime = 225;
	check[3].checkTime = 300;
	check[4].checkTime = 375;

	// BGM�Đ�
	//PlaySound(SOUND_LABEL_BGM_sample000);

	g_Load = TRUE;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitStaffRoll(void)
{
	if (g_Load == FALSE) return;

	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}

	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Texture[i])
		{
			g_Texture[i]->Release();
			g_Texture[i] = NULL;
		}
	}

	g_Load = FALSE;
}