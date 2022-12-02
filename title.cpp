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
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX		(6)		// �e�N�X�`���̐�
#define DEBUGPOS_ADD	(1.0f)	// �f�o�b�O�pPOS�̉����Z�p

//*****************************************************************************
// �O���[�o���ϐ�
static ID3D11Buffer				*g_VertexBuffer = NULL;		// ���_���
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };	// �e�N�X�`�����

static char *g_TexturName[TEXTURE_MAX] = {
	"data/TEXTURE/title_exit02.png",
	"data/TEXTURE/title_gamestart02.png",
	"data/TEXTURE/title_curtainR01.png",
	"data/TEXTURE/title_curtainL01.png",
	"data/TEXTURE/title_tent.png",
	"data/TEXTURE/title_finger.png",
};

static BOOL						g_Load = FALSE;

// �^�C�g���I�u�W�F�N�g�̃C���X�^���X
s_Title title[TEXTURE_MAX];

/*

title[0] == �㖋
title[1] == EXIT�o�[
title[2] == GAME_START�o�[

*/

//=============================================================================
// �R���X�g���N�^�[ ���V�[���̃R���X�g���N�^�[�ɓn���Ă�����
//=============================================================================
Title::Title(God *god) : Scene(god)
{
	InitTitle();
}

//=============================================================================
// �f�X�g���N�^�[
//=============================================================================
Title::~Title()
{
	UninitTitle();
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
	UpdateTitle();

	switch (m_modeSw)
	{
	case FIRST_CLOSE:
		FirstClose();
		break;

	case OPEN_CURTAIN:
		OpenCurtain(&title[2].g_Pos.x, &title[3].g_Pos.x);
		break;

	case CHOICE:
		Choice(&title[0].g_Pos.x, &title[1].g_Pos.x, &title[5].g_Pos.x);
		break;

	case GAME_START:
		break;

	case CLOSE_CURTAIN:
		CloseCurtain(&title[2].g_Pos.x, &title[3].g_Pos.x);
		break;

	case EXIT_CLOSE:
		break;
	}


#ifdef _DEBUG	// �f�o�b�O����\������

	// �@�f�o�b�O�Ώۂ̐؂�ւ�
	ChangeNum(&m_DebugNum);

	// �A2D�摜�ʒu�m�F
	DebugPrint(title[m_DebugNum].g_Pos.x, title[m_DebugNum].g_Pos.y);

	// �B2D�摜�ʒu�ύX
	PosCustom(&title[m_DebugNum].g_Pos.x, &title[m_DebugNum].g_Pos.y); // �z��̗v�f���Ƀf�o�b�N�ԍ������鎖�Łi�f�o�b�N�Ώ�==�f�o�b�N�ԍ��j�Ƃ���

	/* �@�A�A�A�B�̗��ꂪ�d�v�IChangeNum()�֐��Ń����o�ϐ���m_DebugNum�ɃA�N�Z�X���ăf�o�b�N�Ώۂ����߂āA����𔽉f�����Ă���ʒu�m�F�A�ʒu�m�F�����Ă���*/

	// �V�[���؂�ւ��`�F�b�N
	NextScene();

#endif


}

//=============================================================================
// �`�揈��
//=============================================================================
void Title::Draw(void)
{
	DrawTitle();
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

//=============================================================================
// �A�j���[�V�����؂�ւ������i�n�܂�j
//=============================================================================
int Title::SetMode(int mode)
{
	m_modeSw = mode;

	return m_modeSw;
}

void Title::FirstClose(void)
{
	if (GetKeyboardTrigger(DIK_SPACE))
	{
		m_modeSw = SetMode(OPEN_CURTAIN); // 1 == OPEN_CURTAIN
	}
}

void Title::OpenCurtain(float *curtainR, float *curtainL)
{
	*curtainR += 1.0f;
	if (*curtainR > 1200.0f)
	{
		*curtainR = 1200.0f;
		m_modeSw = SetMode(CHOICE); // 2 == CHOICE
	}

	*curtainL -= 1.0f;
	if (*curtainL < -240.0f)
	{
		*curtainL = -240.0f;
	}
}


void Title::Choice(float *posExitX, float *posGameX, float *posChoiceX)
{
	if (*posChoiceX == *posExitX + 13.0f)
	{
		if (GetKeyboardTrigger(DIK_RIGHT))
		{
			*posChoiceX = *posGameX + 12.0f;
		}
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			m_modeSw = SetMode(CLOSE_CURTAIN); // 4 == CLOSE_CURTAIN
		}
	}

	if (*posChoiceX == *posGameX + 12.0f)
	{
		if (GetKeyboardTrigger(DIK_LEFT))
		{
			*posChoiceX = *posExitX + 13.0f;
		}
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			m_modeSw = SetMode(GAME_START); // 3 == GAME_START
		}
	}
}

void Title::CloseCurtain(float * curtainR, float * curtainL)
{
	*curtainR -= 1.0f;
	if (*curtainR < 720.0f)
	{ // �܂�؂�����FADEOUT����
		*curtainR = 720.0f;
		SetFade(FADE_OUT);
	}

	*curtainL += 1.0f;
	if (*curtainL > 240.0f)
	{
		*curtainL = 240.0f;
	}
}

//=============================================================================
// �A�j���[�V�����؂�ւ������i�I���j
//=============================================================================

//=============================================================================
// �f�o�b�N�@�\�S��(�n�܂�)
//=============================================================================

// �f�o�b�O�̏��̕\��
void Title::DebugPrint(float posX, float posY) // �\���������f�o�b�O�Ώۂ̍��W�̈�����2�����
{
	PrintDebugProc("�f�o�b�O�Ώۂ̐؂�ւ� : SPACE�L�[\n");
	PrintDebugProc("�f�o�b�O�Ώۂ̏�ړ� : ���L�[ , �f�o�b�O�Ώۂ̉��ړ� : ���L�[\n");
	PrintDebugProc("�f�o�b�O�Ώۂ̉E�ړ� : ���L�[ , �f�o�b�O�Ώۂ̍��ړ� : ���L�[\n");
	PrintDebugProc("�f�o�b�O�Ώۂ̈ړ��ʕύX�{�^�� : C�L�[\n");
	PrintDebugProc("�f�o�b�N�Ώ� : title[%d] \n", m_DebugNum);
	PrintDebugProc("�f�o�b�N�|�W�V���� : PosX : %f, DebugPosY : %f\n", posX, posY);
}

// �f�o�b�O�Ώۂ̈ʒu�ύX
void Title::PosCustom(float *posX, float *posY) // �ړ��������f�o�b�O�Ώۂ̍��W�̈�����2�i�|�C���^�j�����
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
			*posY -= DEBUGPOS_ADD;
		}
		// ������Ă���ԁAY�������Ɉړ�
		if (GetKeyboardTrigger(DIK_DOWN))
		{
			*posY += DEBUGPOS_ADD;
		}
		// ������Ă���ԁAX�E�����ɉ��Z
		if (GetKeyboardTrigger(DIK_RIGHT))
		{
			*posX += DEBUGPOS_ADD;
		}
		// ������Ă���ԁAX�������ɉ��Z
		if (GetKeyboardTrigger(DIK_LEFT))
		{
			*posX -= DEBUGPOS_ADD;
		}
		break;

	case false:
		// ������Ă���ԁAY������Ɉړ�
		if (GetKeyboardPress(DIK_UP))
		{
			*posY -= DEBUGPOS_ADD;
		}
		// ������Ă���ԁAY�������Ɉړ�
		if (GetKeyboardPress(DIK_DOWN))
		{
			*posY += DEBUGPOS_ADD;
		}
		// ������Ă���ԁAX�E�����ɉ��Z
		if (GetKeyboardPress(DIK_RIGHT))
		{
			*posX += DEBUGPOS_ADD;
		}
		// ������Ă���ԁAX�������ɉ��Z
		if (GetKeyboardPress(DIK_LEFT))
		{
			*posX -= DEBUGPOS_ADD;
		}
	}
}

// �f�o�b�O�Ώۂ̐؂�ւ�
int Title::ChangeNum(int *Num) // �f�o�b�O�Ώۂ̐؂�ւ��i�f�o�b�N�ԍ���ΏۃI�u�W�F�N�g�̔z��̈����ɓ���鎖�Ő؂�ւ����s����悤�ɂ���j
{
	int r;

	r = *Num;

	if (GetKeyboardTrigger(DIK_SPACE))
	{
		r += 1;

		if (r > TEXTURE_MAX - 1)
		{
			r = 0;
		}
	}

	*Num = r;

	return *Num;
}

//=============================================================================
// �f�o�b�N�@�\�S��(�I���)
//=============================================================================

//=============================================================================
// ����������
//=============================================================================
HRESULT InitTitle(void)
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
	title[0].g_Use = TRUE;
	title[0].g_w = 128;
	title[0].g_h = 44;
	title[0].g_Pos = XMFLOAT3(220.0f, 330.0f, 0.0f);
	title[0].g_TexNo = 3;
	title[0].alpha = 1.0f;
	title[0].flag_alpha = TRUE;

	// �ϐ��̏�����(GAME_START�o�[)
	title[1].g_Use = TRUE;
	title[1].g_w = 182;
	title[1].g_h = 44;
	title[1].g_Pos = XMFLOAT3(740.0f, 330.0f, 0.0f);
	title[1].g_TexNo = 4;
	title[1].alpha = 1.0f;
	title[1].flag_alpha = TRUE;

	// �ϐ��̏�����(�E�J�[�e��)
	title[2].g_Use = TRUE;
	title[2].g_w = 480;
	title[2].g_h = 540;
	title[2].g_Pos = XMFLOAT3(720.0f, SCREEN_CENTER_Y, 0.0f); // �J���~�߂�1200.0f
	title[2].g_TexNo = 1;
	title[2].alpha = 1.0f;
	title[2].flag_alpha = TRUE;

	// �ϐ��̏�����(���J�[�e��)
	title[3].g_Use = TRUE;
	title[3].g_w = 480;
	title[3].g_h = 540;
	title[3].g_Pos = XMFLOAT3(240.0f, SCREEN_CENTER_Y, 0.0f); // �J���~�߂�-240.0f
	title[3].g_TexNo = 2;
	title[3].alpha = 1.0f;
	title[3].flag_alpha = TRUE;

	// �ϐ��̏�����(��)
	title[4].g_Use = TRUE;
	title[4].g_w = 1024;
	title[4].g_h = 540;
	title[4].g_Pos = XMFLOAT3(480.0f, 260.0f, 0.0f);
	title[4].g_TexNo = 0;
	title[4].alpha = 1.0f;
	title[4].flag_alpha = TRUE;

	// �ϐ��̏�����(�J�[�\��)
	title[5].g_Use = TRUE;
	title[5].g_w = 110;
	title[5].g_h = 90;
	title[5].g_Pos = title[0].g_Pos;
	title[5].g_Pos.x += 13.0f; // ������EXITPos.X
	title[5].g_Pos.y += 40.0f; // ������EXITPos.Y
	//title[5].g_Pos.x += 12.0f; // ������GAME_STARTPos.X
	//title[5].g_Pos.y += 40.0f; // ������GAME_STARTPos.Y
	title[5].g_TexNo = 5;
	title[5].alpha = 1.0f;
	title[5].flag_alpha = TRUE;


	//// �ϐ��̏�����(EXIT�o�[)
	//maku.g_Use = TRUE;
	//maku.g_w = 960;
	//maku.g_h = 128;
	//maku.g_Pos = XMFLOAT3(480.0f, 64.0f, 0.0f);
	//maku.g_TexNo = 0;

	//maku.alpha = 1.0f;
	//maku.flag_alpha = TRUE;

	//// �ϐ��̏�����(GAME_START�o�[)
	//maku.g_Use = TRUE;
	//maku.g_w = 960;
	//maku.g_h = 128;
	//maku.g_Pos = XMFLOAT3(480.0f, 64.0f, 0.0f);
	//maku.g_TexNo = 0;

	//maku.alpha = 1.0f;
	//maku.flag_alpha = TRUE;

	//// �ϐ��̏�����(�J�[�\��)
	//maku.g_Use = TRUE;
	//maku.g_w = 960;
	//maku.g_h = 128;
	//maku.g_Pos = XMFLOAT3(480.0f, 64.0f, 0.0f);
	//maku.g_TexNo = 0;

	//maku.alpha = 1.0f;
	//maku.flag_alpha = TRUE;


	// BGM�Đ�
	PlaySound(SOUND_LABEL_BGM_sample000);

	g_Load = TRUE;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitTitle(void)
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
void UpdateTitle(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawTitle(void)
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

	// �^�C�g���̔w�i��`��
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[i]);

		// �P���̃|���S���̒��_�ƃe�N�X�`�����W��ݒ�
		SetSprite(g_VertexBuffer, title[i].g_Pos.x, title[i].g_Pos.y, title[i].g_w, title[i].g_h, 0.0f, 0.0f, 1.0f, 1.0f);

		// �|���S���`��
		GetDeviceContext()->Draw(4, 0);
	}

}


