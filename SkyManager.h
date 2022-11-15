//=============================================================================
//
// �G�ߊǗ����� [SkyManager.h]
// Author : 
//
//=============================================================================
#pragma once
#include "Sky.h"
#include "GodObject.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SEASON_MAX	(5)


enum SEASON_MODE
{
	SEASON_MODE_SPRING,		// �t
	SEASON_MODE_SUMMER,		// ��
	SEASON_MODE_AUTUMN,		// �H
	SEASON_MODE_WINTER,		// �~
	SEASON_MODE_RAIN,		// �J
	SEASON_MODE_MAX,
};

enum SKYBG_MODE
{
	SKYBG_MODE_Kemuri,		// ��
	SKYBG_MODE_Aozora,		// ��
	SKYBG_MODE_Utyuu,		// �F��
	SKYBG_MODE_Kumori,		// �܂�
	SKYBG_MODE_Shining,		// �V���C�j���O
	SKYBG_MODE_MAX,
};

enum BUFFER_MODE
{
	BUFFER_FRONT,		// �t�����g�o�b�t�@�[
	BUFFER_BACK,		// �o�b�N�o�b�t�@�[
	BUFFER_MAX,
};

static std::string g_ModelName[SEASON_MODE_MAX] = {
	"model_sky_spring_01.obj",
};

static char *g_TextureName[SEASON_MODE_MAX] =
{
	"data/TEXTURE/SKY/tex_skyKumori_01.jpg",
	"data/TEXTURE/SKY/sky001.jpg",
	"data/TEXTURE/SKY/tex_skyStar_01.png",
	"data/TEXTURE/SKY/sky002.jpg",
	"data/TEXTURE/SKY/tex_skyNami_01.jpg",
};


//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SkyManager:public GodObject
{

private:
	Sky *m_seasons[BUFFER_MAX] = { nullptr };
	ID3D11ShaderResourceView	*m_Texture[SEASON_MODE_MAX] = { nullptr };
	int m_swich = 0;
	float m_time = 0;
	XMFLOAT4 m_color = { 1.0f,1.0f,1.0f,1.0f };
public:
	SkyManager(God *god);
	~SkyManager();

	void Update(void);
	void Draw(SKYBG_MODE swich);
};
