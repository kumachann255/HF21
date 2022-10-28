//=============================================================================
//
// �����_�����O���� [renderer.h]
// Author : 
//
//=============================================================================
#pragma once


//*********************************************************
// �}�N����`
//*********************************************************
#define LIGHT_MAX		(5)

enum LIGHT_TYPE
{
	LIGHT_TYPE_NONE,		//���C�g����
	LIGHT_TYPE_DIRECTIONAL,	//�f�B���N�V���i�����C�g
	LIGHT_TYPE_POINT,		//�|�C���g���C�g

	LIGHT_TYPE_NUM
};

enum BLEND_MODE
{
	BLEND_MODE_NONE,		//�u�����h����
	BLEND_MODE_ALPHABLEND,	//���u�����h
	BLEND_MODE_ADD,			//���Z�u�����h
	BLEND_MODE_SUBTRACT,	//���Z�u�����h

	BLEDD_MODE_NUM
};

enum CULL_MODE
{
	CULL_MODE_NONE,			//�J�����O����
	CULL_MODE_FRONT,		//�\�̃|���S����`�悵�Ȃ�(CW)
	CULL_MODE_BACK,			//���̃|���S����`�悵�Ȃ�(CCW)

	CULL_MODE_NUM
};

enum SHADER_MODE
{
	SHADER_MODE_DEFAULT,		// �f�t�H���g
	SHADER_MODE_PHONG,			// �t�H���V�F�[�f�B���O
	SHADER_MODE_DISSOLVE,		// �f�B�]���u
	SHADER_MODE_TOON,			// �g�D�[���V�F�[�f�B���O

	SHADER_MODE_MAX,
};

//*********************************************************
// �\����
//*********************************************************

// ���_�\����
struct VERTEX_3D
{
    XMFLOAT3	Position;
    XMFLOAT3	Normal;
    XMFLOAT4	Diffuse;
    XMFLOAT2	TexCoord;
};

// �}�e���A���\����
struct MATERIAL
{
	XMFLOAT4	Ambient;
	XMFLOAT4	Diffuse;
	XMFLOAT4	Specular;
	XMFLOAT4	Emission;
	float		Shininess;
	int			noTexSampling;
};

// ���C�g�\����
struct LIGHT {
	XMFLOAT3	Direction;	// ���C�g�̕���
	XMFLOAT3	Position;	// ���C�g�̈ʒu
	XMFLOAT4	Diffuse;	// �g�U���̐F
	XMFLOAT4	Ambient;	// �����̐F
	float		Attenuation;// ������
	int			Type;		// ���C�g��ʁE�L���t���O
	int			Enable;		// ���C�g��ʁE�L���t���O
};

// �t�H�O�\����
struct FOG {
	float		FogStart;	// �t�H�O�̊J�n����
	float		FogEnd;		// �t�H�O�̍ő勗��
	XMFLOAT4	FogColor;	// �t�H�O�̐F
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitRenderer(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void UninitRenderer(void);

void Clear(void);
void Present(void);

ID3D11Device *GetDevice( void );
ID3D11DeviceContext *GetDeviceContext( void );

void SetDepthEnable( BOOL Enable );
void SetBlendState(BLEND_MODE bm);
void SetCullingMode(CULL_MODE cm);
void SetAlphaTestEnable(BOOL flag);

void SetWorldViewProjection2D( void );
void SetWorldMatrix( XMMATRIX *WorldMatrix );
void SetViewMatrix( XMMATRIX *ViewMatrix );
void SetProjectionMatrix( XMMATRIX *ProjectionMatrix );

void SetMaterial( MATERIAL material );

void SetLightEnable(BOOL flag);
void SetLight(int index, LIGHT* light);

void SetFogEnable(BOOL flag);
void SetFog(FOG* fog);

void DebugTextOut(char* text, int x, int y);

void SetFuchi(int flag);
void SetShaderCamera(XMFLOAT3 pos);

//=============================================================================
// ���[���h�}�g���N�X�𐶐����擾����
//=============================================================================
XMMATRIX GetWorldMatrix(XMFLOAT3 pos, XMFLOAT3 rot, XMFLOAT3 scl);

//=============================================================================
// hlsl�t�@�C����ǂݍ��݃V�F�[�_�[���쐬����֐�
//�y�֐����g�p����Ƃ�(�o�[�e�b�N�X�V�F�[�_�[�̏ꍇ)�z
// hr = MakeShader(g_D3DDevice, "shader.hlsl", "VertexShaderPolygon", "vs_4_0", (void**)&g_VertexShader, &pVSBlob);
//=============================================================================
HRESULT MakeShader(ID3D11Device* pDevice, LPSTR szFileName, LPSTR szFuncName, LPSTR szProfileName, void** ppShader, ID3DBlob** ppBlob);

//=============================================================================
// �V�F�[�_�[�؂�ւ�
//=============================================================================
void SetShader(SHADER_MODE mode);

