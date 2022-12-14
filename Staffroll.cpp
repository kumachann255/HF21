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

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX				(1)		// �e�N�X�`���̐�
#define DEBUGPOS_PRESS_ADD		(5.0f)	// �f�o�b�O�pPOS�̉����Z�pPRESS
#define DEBUGPOS_TRIGGER_ADD	(1.0f)	// �f�o�b�O�pPOS�̉����Z�pTRIGGER
#define SCROLL_VALUE			(2.5f)	// �X�N���[���p�����l

//*****************************************************************************
// �O���[�o���ϐ�
static ID3D11Buffer				*g_VertexBuffer = NULL;		// ���_���
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char *g_TexturName[TEXTURE_MAX] = {
	"data/TEXTURE/scroll.png",
};

static BOOL						g_Load = FALSE;

// �X�^�b�t���[���I�u�W�F�N�g�̃C���X�^���X
s_StaffRoll staffRoll;

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

}

//=============================================================================
// �X�V����
//=============================================================================
void StaffRoll::Update(void)
{
	UpdateStaffRoll();
	Scroll(&staffRoll.g_Pos.y);

#ifdef _DEBUG	// �f�o�b�O����\������


	// 2D�摜�ʒu�m�F
	DebugPrint(staffRoll.g_Pos.y);

	// 2D�摜�ʒu�ύX
	PosCustom(&staffRoll.g_Pos.y); // �z��̗v�f���Ƀf�o�b�N�ԍ������鎖�Łi�f�o�b�N�Ώ�==�f�o�b�N�ԍ��j�Ƃ���

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
	DrawStaffRoll();
}

//=============================================================================
// �V�[���J�ڏ���
//=============================================================================
void StaffRoll::NextScene(void)
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

void StaffRoll::Scroll(float *posY)
{
	*posY -= SCROLL_VALUE;
	if (*posY < -1460.0f)
	{
		*posY = -1460.0f;
		SetFade(FADE_OUT);
	}
}

//=============================================================================
// �f�o�b�N�@�\�S��(�n�܂�)
//=============================================================================

// �f�o�b�O�̏��̕\��
void StaffRoll::DebugPrint(float posY) // �\���������f�o�b�O�Ώۂ̍��W�̈�����2�����
{
	PrintDebugProc("�f�o�b�O�Ώۂ̏�ړ� : ���L�[ , �f�o�b�O�Ώۂ̉��ړ� : ���L�[\n");
	PrintDebugProc("�f�o�b�N�|�W�V���� DebugPosY : %f\n", posY);
}

// �f�o�b�O�Ώۂ̈ʒu�ύX
void StaffRoll::PosCustom(float *posY) // �ړ��������f�o�b�O�Ώۂ̍��W�̈�����2�i�|�C���^�j�����
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
		break;
	}
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
			g_TexturName[i],
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

	// �ϐ��̏�����(EXIT�o�[)
	staffRoll.g_Use = TRUE;
	staffRoll.g_w = SCREEN_WIDTH;
	staffRoll.g_h = 4000;
	staffRoll.g_Pos = XMFLOAT3(SCREEN_CENTER_X, 2000.0f, 0.0f); // END��-1460.0f
	staffRoll.g_TexNo = 0;

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

//=============================================================================
// �X�V����
//=============================================================================
void UpdateStaffRoll(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawStaffRoll(void)
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

	// �e�N�X�`���ݒ�
	GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[0]);

	// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
	SetSprite(g_VertexBuffer, staffRoll.g_Pos.x, staffRoll.g_Pos.y, staffRoll.g_w, staffRoll.g_h, 0.0f, 0.0f, 1.0f, 1.0f);

	// �|���S���`��
	GetDeviceContext()->Draw(4, 0);

}