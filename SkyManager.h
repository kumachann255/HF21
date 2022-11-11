//=============================================================================
//
// 季節管理処理 [SkyManager.h]
// Author : 
//
//=============================================================================
#pragma once
#include "main.h"
#include "Sky.h"
#include "object.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define SEASON_MAX	(5)

enum SEASON_MODE
{
	SEASON_MODE_SPRING,		// 春
	SEASON_MODE_SUMMER,		// 夏
	SEASON_MODE_AUTUMN,		// 秋
	SEASON_MODE_WINTER,		// 冬
	SEASON_MODE_RAIN,		// 雨
	SEASON_MODE_MAX,
};

enum BUFFER_MODE
{
	BUFFER_FRONT,		// フロントバッファー
	BUFFER_BACK,		// バックバッファー
	BUFFER_MAX,
};

static std::string g_ModelName[SEASON_MODE_MAX] = {
	"model_sky_spring_01.obj",
};

static char *g_TextureName[SEASON_MODE_MAX] =
{
	"data/TEXTURE/sky000.jpg",
	"data/TEXTURE/tex_skyStar_01.png",
	"data/TEXTURE/sky002.jpg",
	"data/TEXTURE/tex_skyKumori_01.jpg",
	"data/TEXTURE/tex_skyNami_01.jpg",
};


//*****************************************************************************
// クラス定義
//*****************************************************************************
class SkyManager
{

private:
	Sky *m_seasons[BUFFER_MAX] = { nullptr };
	ID3D11ShaderResourceView	*m_Texture[SEASON_MODE_MAX] = { nullptr };
	int m_swich = 0;
	float m_time = 0;
	XMFLOAT4 m_color = { 1.0f,1.0f,1.0f,1.0f };
public:
	SkyManager();
	~SkyManager();

	void Update(void);
	void Draw(void);
	void Create(SEASON_MODE mode);
};
