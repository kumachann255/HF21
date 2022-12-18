//=============================================================================
//
// �G�ߊǗ����� [SkyManager.h]
// Author : 
//
//=============================================================================
#pragma once
#include "Sky.h"
#include "GodObject.h"
#include "fade.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define SEASON_MAX	(4)


enum
{
	SEASON_MODE_SPRING,		// �t
	SEASON_MODE_SUMMER,		// ��
	SEASON_MODE_AUTUMN,		// �H
	SEASON_MODE_WINTER,		// �~
	SEASON_MODE_MAX,
};

enum SKYBG_MODE
{
	SKYBG_MODE_Spring,
	SKYBG_MODE_Summer,
	SKYBG_MODE_autom,
	SKYBG_MODE_winter,
	SKYBG_MODE_Shining,
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



//*****************************************************************************
// �N���X��`
//*****************************************************************************
class SkyManager :public GodObject
{

private:
	Sky *m_seasons[BUFFER_MAX] = { nullptr };
	ID3D11ShaderResourceView	*m_Texture[SKYBG_MODE_MAX] = { nullptr };
	int m_swich = 0;
	float m_time = 0;
	float m_alfa = 1.0f;
	XMFLOAT4 m_color = { 1.0f,1.0f,1.0f,1.0f };
	FADE m_fade = FADE_NONE;			// �t�F�[�h�̏��
	BOOL g_FadeOut_EndFlag = FALSE;
	BOOL g_FadeOut_StartFlag = FALSE;
	int m_seasonNum = 0;
public:
	SkyManager(God *god);
	~SkyManager();

	void Update(void);
	void Draw(SKYBG_MODE swich);
	void Draw(void);
	void Fade(void);
	void SetFade(FADE fade) { m_fade = fade; }
	void SetFadeOut_EndFlag(BOOL flag) { g_FadeOut_EndFlag = flag; }
	void SetFadeOut_StartFlag(BOOL flag) { g_FadeOut_StartFlag = flag; }
	BOOL GetFadeOut_EndFlag(void) { return g_FadeOut_EndFlag; }
	BOOL GetFadeOut_StartFlag(void) { return g_FadeOut_StartFlag; }
	float GetAlfa(void) { return m_alfa; }
};
