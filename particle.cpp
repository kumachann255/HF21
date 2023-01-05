//=============================================================================
//
// �p�[�e�B�N������ [particle.cpp]
// Author : 
//
//=============================================================================
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "model.h"
#include "particle.h"
#include "debugproc.h"
#include "RollerManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_MAX			(10)			// �e�N�X�`���̐�
#define VERTEX_MAX			(5)			

#define	PARTICLE_SIZE_X		(30.0f)		// ���_�T�C�Y
#define	PARTICLE_SIZE_Y		(30.0f)		// ���_�T�C�Y
#define	VALUE_MOVE_PARTICLE	(10.0f)		// �ړ����x


#define TEXTURE_PATTERN_DIVIDE_X	    (10)		                                            // �A�j���p�^�[���̃e�N�X�`�����������iX)
#define TEXTURE_PATTERN_DIVIDE_Y	    (1)		                                                // �A�j���p�^�[���̃e�N�X�`�����������iY)
#define ANIM_PATTERN_NUM			    (TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y) 	// �A�j���[�V�����p�^�[����
#define ANIM_WAIT					    (5)													   // �A�j���[�V�����̐؂�ւ��Wait�l

#define WIND_SPD				(1.0f)
#define WIND_SPD_Y				(0.5f)
#define FALL_SPD				(2.0f)
#define	PARTICLE_RANGE			(800)		// ���_�T�C�Y
#define	PARTICLE_RANGE_HALF		(400)		// ���_�T�C�Y

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexParticle(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static ID3D11Buffer				*g_VertexBuffer[VERTEX_MAX] = { NULL };
static ID3D11ShaderResourceView	*g_Texture[TEXTURE_MAX] = { NULL };
static int g_VertexCount;

static char *m_TextureName[TEXTURE_MAX] =
{
	"data/TEXTURE/EFFECT/sakura.png",
	"data/TEXTURE/EFFECT/leaf.png",
	"data/TEXTURE/EFFECT/momiji.png",
	"data/TEXTURE/EFFECT/snow.png",
	"data/TEXTURE/EFFECT/effect_bom.png",
	"data/TEXTURE/EFFECT/effect_kemuri.png",
	"data/TEXTURE/EFFECT/effect_kemuri2.png",
	"data/TEXTURE/EFFECT/effect_light.png",
	"data/TEXTURE/EFFECT/effect_reflection.png",
	"data/TEXTURE/EFFECT/effect_nigiwai.png",
};

//=============================================================================
// ����������
//=============================================================================
HRESULT InitParticle(void)
{
	g_VertexCount = 0;

	// ���_���̍쐬
	MakeVertexParticle();


	// �e�N�X�`������
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		g_Texture[i] = NULL;
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			m_TextureName[i],
			NULL,
			NULL,
			&g_Texture[i],
			NULL);
	}

	return S_OK;

}

//=============================================================================
// �I������
//=============================================================================
void UninitParticle(void)
{
	//�e�N�X�`���̉��
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		if (g_Texture[i] != NULL)
		{
			g_Texture[i]->Release();
			g_Texture[i] = NULL;
		}
	}

	for (int i = 0; i < VERTEX_MAX; i++)
	{
		// ���_�o�b�t�@�̉��
		if (g_VertexBuffer[i] != NULL)
		{
			g_VertexBuffer[i]->Release();
			g_VertexBuffer[i] = NULL;
		}
	}

}


//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexParticle(void)
{
	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;



	for (int i = 0; i < VERTEX_MAX; i++)
	{
		GetDevice()->CreateBuffer(&bd, NULL, &g_VertexBuffer[i]);

		{//���_�o�b�t�@�̒��g�𖄂߂�
			D3D11_MAPPED_SUBRESOURCE msr;
			GetDeviceContext()->Map(g_VertexBuffer[i], 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

			// ���_���W�̐ݒ�
			vertex[0].Position = XMFLOAT3(-PARTICLE_SIZE_X, PARTICLE_SIZE_Y, 0.0f);
			vertex[1].Position = XMFLOAT3(PARTICLE_SIZE_X, PARTICLE_SIZE_Y, 0.0f);
			vertex[2].Position = XMFLOAT3(-PARTICLE_SIZE_X, -PARTICLE_SIZE_Y, 0.0f);
			vertex[3].Position = XMFLOAT3(PARTICLE_SIZE_X, -PARTICLE_SIZE_Y, 0.0f);

			// �@���̐ݒ�
			vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
			vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
			vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
			vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			// ���ˌ��̐ݒ�
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			vertex[0].TexCoord = { 0.0f, 0.0f };
			vertex[1].TexCoord = { 1.0f, 0.0f };
			vertex[2].TexCoord = { 0.0f, 1.0f };
			vertex[3].TexCoord = { 1.0f, 1.0f };

			GetDeviceContext()->Unmap(g_VertexBuffer[i], 0);
		}
	}


	return S_OK;
}


//=============================================================================
// �@�@�@�@�@�@�@�@�@�@�@�@�N���X�֐��̒�`
//=============================================================================

// �R���X�g���N�^�[
PARTICLE::PARTICLE()
{
	// �p�[�e�B�N�����[�N�̏�����
	m_posBase = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_scale = XMFLOAT3(1.0f, 1.0f, 1.0f);
	m_move = XMFLOAT3(1.0f, 1.0f, 1.0f);

	ZeroMemory(&m_material, sizeof(m_material));
	m_material.Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

	m_fSizeX = PARTICLE_SIZE_X;
	m_fSizeY = PARTICLE_SIZE_Y;
	m_nLife = 100;
	m_bUse = FALSE;
	m_bSwich = FALSE;
	m_nTexno = EFFECT_REFLECTION;
	m_Pattern = MOVE_PATTERN_UP;
	m_nextAnime = 10;

	m_pSpriteAnim = new SPRITE_ANIMATION();

}

// �f�X�g���N�^�[
PARTICLE::~PARTICLE()
{
	delete m_pSpriteAnim;

}

void PARTICLE::Update(void)
{
	if (!m_bSwich) return;

	XMFLOAT3 move;
	float fAngle, fLength;
	int nLife;
	float fWidthBase = 10.0f;

	switch (m_Pattern)
	{
	case MOVE_PATTERN_UP:


		fAngle = (float)(rand() % 628 - 314) / 100.0f;
		fLength = rand() % (int)(10.0f * 200) / 100.0f - 10.0f;
		move.x = sinf(fAngle) * fLength;
		move.y = rand() % 300 / 200.0f;
		move.z = cosf(fAngle) * fLength;

		nLife = rand() % 100 + 50;

		// �r���{�[�h�̐ݒ�
		SetParticle(m_posBase, move, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), m_fSizeX, m_fSizeY, nLife);

		break;

	case MOVE_PATTERN_UP_SMALL:


		fAngle = (float)(rand() % 628 - 314) * 0.01f;
		fLength = rand() % (int)(300) * 0.01f;
		move.x = sinf(fAngle) * fLength;
		move.y = (float)(rand() % 300 - 150) * 0.01f;
		move.z = cosf(fAngle) * fLength;

		nLife = rand() % 100 + 50;

		// �r���{�[�h�̐ݒ�
		SetParticle(m_posBase, move, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), m_fSizeX, m_fSizeY, nLife);

		break;

	case MOVE_PATTERN_STOP:

		move.x = 0.0f;
		move.y = 0.0f;
		move.z = 0.0f;

		nLife = rand() % 100 + 50;

		// �r���{�[�h�̐ݒ�
		SetParticle(m_posBase, move, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), m_fSizeX, m_fSizeY, nLife);

		break;

	case MOVE_PATTERN_DOWNRIGHT:

		m_windtime += 0.001f;
		if (m_windtime > XM_2PI) m_windtime -= XM_2PI;	// m_windtime���I�[�o�[�t���[���Ȃ��悤�Ƀ��[�v������

		m_wind = { WIND_SPD * cosf(m_windtime), WIND_SPD_Y * sinf(m_windtime * 10.0f), WIND_SPD * sinf(m_windtime) };

		fLength = (float)(rand() % 200) * 0.01f;

		move.x = m_wind.x + fLength;
		move.y = m_wind.y - FALL_SPD + fLength;
		move.z = m_wind.z ;


		nLife = rand() % 1000 + 50;

		// �r���{�[�h�̐ݒ�
		SetParticle(m_posBase, move, XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), m_fSizeX, m_fSizeY, nLife);

		break;

	}


	// �g�p����Ă�����A�ʒu�ƃ��C�t���X�V
	if (m_bUse)
	{
		AddPos(m_move);

		m_nLife--;

		if (m_nLife <= 0 || m_pSpriteAnim->GetUse() == FALSE)
		{
			m_bUse = FALSE;
			m_bSwich = FALSE;
			m_pSpriteAnim->SetUse(FALSE);
			m_pSpriteAnim->Init();
			m_move.x = 0.0f;
			m_move.y = 0.0f;
			m_move.z = 0.0f;
			m_pos = m_posBase;

		}
	}

}

void PARTICLE::Draw(int vNum)
{

	if (m_bUse)
	{

		XMMATRIX mtxScl, mtxTranslate, mtxWorld, mtxView;
		CAMERA *cam = GetCamera();

		// ���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		GetDeviceContext()->IASetVertexBuffers(0, 1, &g_VertexBuffer[vNum], &stride, &offset);

		// �v���~�e�B�u�g�|���W�ݒ�
		GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		// �e�N�X�`���ݒ�
		GetDeviceContext()->PSSetShaderResources(0, 1, &g_Texture[m_nTexno]);

		{//���_�o�b�t�@�̒��g�𖄂߂�
			D3D11_MAPPED_SUBRESOURCE msr;
			GetDeviceContext()->Map(g_VertexBuffer[vNum], 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

			// ���_���W�̐ݒ�
			vertex[0].Position = XMFLOAT3(-m_fSizeX, m_fSizeY, 0.0f);
			vertex[1].Position = XMFLOAT3(m_fSizeX, m_fSizeY, 0.0f);
			vertex[2].Position = XMFLOAT3(-m_fSizeX, -m_fSizeY, 0.0f);
			vertex[3].Position = XMFLOAT3(m_fSizeX, -m_fSizeY, 0.0f);

			// �@���̐ݒ�
			vertex[0].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
			vertex[1].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
			vertex[2].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);
			vertex[3].Normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

			// ���ˌ��̐ݒ�
			vertex[0].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].Diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);


			XMFLOAT2 tpos = m_pSpriteAnim->GetTexPos();
			XMFLOAT2 twidth = m_pSpriteAnim->GetTexWidth();

			// �e�N�X�`�����W�̐ݒ�
			vertex[0].TexCoord = XMFLOAT2(tpos.x, tpos.y);
			vertex[1].TexCoord = XMFLOAT2(tpos.x + twidth.x, tpos.y);
			vertex[2].TexCoord = XMFLOAT2(tpos.x, tpos.y + twidth.y);
			vertex[3].TexCoord = XMFLOAT2(tpos.x + twidth.x, tpos.y + twidth.y);

			GetDeviceContext()->Unmap(g_VertexBuffer[vNum], 0);
		}


		// ���[���h�}�g���b�N�X�̏�����
		mtxWorld = XMMatrixIdentity();

		// �r���[�}�g���b�N�X���擾
		mtxView = XMLoadFloat4x4(&cam->mtxView);

		// �r���{�[�h����(����������)
		mtxWorld.r[0].m128_f32[0] = mtxView.r[0].m128_f32[0];
		mtxWorld.r[0].m128_f32[1] = mtxView.r[1].m128_f32[0];
		mtxWorld.r[0].m128_f32[2] = mtxView.r[2].m128_f32[0];

		mtxWorld.r[1].m128_f32[0] = mtxView.r[0].m128_f32[1];
		mtxWorld.r[1].m128_f32[1] = mtxView.r[1].m128_f32[1];
		mtxWorld.r[1].m128_f32[2] = mtxView.r[2].m128_f32[1];

		mtxWorld.r[2].m128_f32[0] = mtxView.r[0].m128_f32[2];
		mtxWorld.r[2].m128_f32[1] = mtxView.r[1].m128_f32[2];
		mtxWorld.r[2].m128_f32[2] = mtxView.r[2].m128_f32[2];

		// �X�P�[���𔽉f
		mtxScl = XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		SetWorldMatrix(&mtxWorld);

		// �}�e���A���ݒ�
		SetMaterial(m_material);

		// �|���S���̕`��
		GetDeviceContext()->Draw(4, 0);
	}

}


void PARTICLE::SetParticle(XMFLOAT3 pos, XMFLOAT3 move, XMFLOAT4 col, float fSizeX, float fSizeY, int nLife)
{
	if (!m_bUse)
	{

		switch (m_Pattern)
		{
		case MOVE_PATTERN_UP:

			m_pos = pos;
			m_rot = { 0.0f, 0.0f, 0.0f };
			m_scale = { 1.0f, 1.0f, 1.0f };
			m_move = move;
			m_material.Diffuse = col;
			m_fSizeX = fSizeX;
			m_fSizeY = fSizeY;
			m_nLife = nLife;
			m_bUse = TRUE;
			m_bSwich = TRUE;
			break;

		case MOVE_PATTERN_UP_SMALL:


			m_pos = pos;
			m_rot = { 0.0f, 0.0f, 0.0f };
			m_scale = { 1.0f, 1.0f, 1.0f };
			m_move = move;
			m_material.Diffuse = col;
			m_fSizeX = fSizeX;
			m_fSizeY = fSizeY;
			m_nLife = nLife;
			m_bUse = TRUE;
			m_bSwich = TRUE;

			break;

		case MOVE_PATTERN_STOP:

			m_pos = pos;
			m_rot = { 0.0f, 0.0f, GetRollerRotX()};
			m_scale = { 1.0f, 1.0f, 1.0f };
			m_move = move;
			m_material.Diffuse = col;
			m_fSizeX = fSizeX;
			m_fSizeY = fSizeY;
			m_nLife = nLife;
			m_bUse = TRUE;
			m_bSwich = TRUE;

			break;

		case MOVE_PATTERN_DOWNRIGHT:

			m_pos = { rand() % PARTICLE_RANGE - PARTICLE_RANGE_HALF + 0.0f , 300.0f, rand() % PARTICLE_RANGE - PARTICLE_RANGE_HALF + 0.0f };
			m_rot = { 0.0f, 0.0f, 0.0f };
			m_scale = { 1.0f, 1.0f, 1.0f };
			m_move = move;
			m_material.Diffuse = col;
			m_fSizeX = fSizeX;
			m_fSizeY = fSizeY;
			m_nLife = nLife;
			m_bUse = TRUE;
			m_bSwich = TRUE;

			break;

		}

	}
}

void SPRITE_ANIMATION::Update(int time)
{

	if (m_use == TRUE)
	{
		m_tw = 1.0f / TEXTURE_PATTERN_DIVIDE_X;       // �e�N�X�`���̕�
		m_th = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;       // �e�N�X�`���̍���
		m_tx = m_tw * m_uwnum;
		m_ty = m_th;

		m_countAnim++;

		if (m_countAnim > time)
		{
			m_countAnim = 0.0f;

			if (m_uwnum < TEXTURE_PATTERN_DIVIDE_X - 1)
			{
				m_uwnum++;
			}
			else
			{
				SetUse(FALSE);
				m_uwnum = 0;

			}
		}
	}

	if (!m_use)
	{
		m_uwnum = 0;
	}


}



////=============================================================================
//// �p�[�e�B�N���̌Ăяo��
//// <����>
//// XMFLOAT3 pos   : �������W 
//// float    size  : �傫��
//// int      num   : ����������p�[�e�B�N���̐��@���}�N����` MAX_PARTICLE �𒴂��Ȃ��悤�ɁI
//// int      texID : �e�N�X�`���[ID
////
//// 
////=============================================================================
//void CallParticle(XMFLOAT3 pos, float size, int num, int texID, int pattern)
//{
//
//	for (int i = 0; i < PARTICLE_BUFFER; i++)
//	{
//		if (!g_pParticle[i]->GetSwich())
//		{
//			for (int j = 0; j < num; j++)
//			{
//
//				//float fSize = (float)(rand() % 6 + 1) * 0.05f * size;	// 0.05f~0.30f
//
//				g_pParticle[i][j].SetSwich(TRUE);
//				g_pParticle[i][j].SetPosBase(pos);
//				g_pParticle[i][j].SetPos(pos);
//				g_pParticle[i][j].SetTexno(texID);
//				g_pParticle[i][j].SetSize(size);
//				g_pParticle[i][j].SetPattern(pattern);
//				g_pParticle[i][j].SpriteAnim.SetUse(TRUE);
//				g_pParticle[i][j].SetAnimeTime(rand() % 5 + 10);
//			}
//
//			break;
//		}
//
//	}
//
//}
