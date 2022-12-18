//=============================================================================
//
// 季節管理処理 [SkyManager.cpp]
// Author : 柏村大地
//
//=============================================================================
#include "SkyManager.h"
#include "input.h"
#include "debugproc.h"
#include "debugproc.h"
#include "calendar_num.h"

static char *g_TextureName[SKYBG_MODE_MAX] =
{
	"data/TEXTURE/SKY/spring.jpg",
	"data/TEXTURE/SKY/summer.jpg",
	"data/TEXTURE/SKY/autom.jpg",
	"data/TEXTURE/SKY/winter.jpg",
	"data/TEXTURE/SKY/tex_skyNami_01.jpg",
};

//=============================================================================
// コンストラクタ
//=============================================================================
SkyManager::SkyManager(God *god) :GodObject(god)
{

	// テクスチャ生成
	for (int i = 0; i < SKYBG_MODE_MAX; i++)
	{
		D3DX11CreateShaderResourceViewFromFile(GetDevice(),
			g_TextureName[i],
			nullptr,
			nullptr,
			&m_Texture[i],
			nullptr);
	}

	m_seasons[BUFFER_FRONT] = new Sky;
	m_seasons[BUFFER_FRONT]->GetPrefab()->SetModel(g_ModelName[SEASON_MODE_SPRING]);
	m_seasons[BUFFER_FRONT]->SetIsUse(TRUE);
	m_seasons[BUFFER_FRONT]->GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[SEASON_MODE_SPRING];

	m_seasons[BUFFER_BACK] = new Sky;
	m_seasons[BUFFER_BACK]->GetPrefab()->SetModel(g_ModelName[SEASON_MODE_SPRING]);
	m_seasons[BUFFER_BACK]->SetIsUse(TRUE);
	m_seasons[BUFFER_BACK]->GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[SEASON_MODE_SPRING];

}

//=============================================================================
// デストラクター
//=============================================================================
SkyManager::~SkyManager()
{
	for (int i = 0; i < BUFFER_MAX; i++)
	{
		if (m_seasons[i])
		{
			delete m_seasons[i];
		}

	}

	for (int i = 0; i < SKYBG_MODE_MAX; i++)
	{
		if (m_Texture[i])
		{// テクスチャの解放
			m_Texture[i]->Release();
			m_Texture[i] = nullptr;
		}
	}

}

//=============================================================================
// 更新処理
//=============================================================================
void SkyManager::Update(void)
{
	Fade();

	for (int i = 0; i < BUFFER_MAX; i++)
	{
		if (m_seasons[i])	m_seasons[i]->Update();

	}

	float calendarCnt = GetGod()->GetCalendarNum()->GetCount();
	int seasonNum = GetGod()->GetCalendarNum()->GetMonth();
	BOOL swichfFlag = GetGod()->GetCalendarNum()->GetSwichfFlag();

	if (swichfFlag)
	{
		SetFade(FADE_OUT);
	}

}


//=============================================================================
// 描画処理
//=============================================================================
void SkyManager::Draw(SKYBG_MODE swich)
{
	m_swich = swich;

	switch (m_swich)
	{
	case SEASON_MODE_SPRING:
		m_seasons[BUFFER_BACK]->GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[SEASON_MODE_SPRING];
		break;

	case SEASON_MODE_SUMMER:
		m_seasons[BUFFER_BACK]->GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[SEASON_MODE_SUMMER];
		break;

	case SEASON_MODE_AUTUMN:
		m_seasons[BUFFER_BACK]->GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[SEASON_MODE_AUTUMN];
		break;

	case SEASON_MODE_WINTER:
		m_seasons[BUFFER_BACK]->GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[SEASON_MODE_WINTER];
		break;

	}


	m_seasons[BUFFER_BACK]->Draw();

}

void SkyManager::Draw(void)
{
	m_seasons[BUFFER_FRONT]->Draw();
}

void SkyManager::Fade(void)
{
	SetFadeOut_EndFlag(FALSE);
	SetFadeOut_StartFlag(FALSE);

	if (m_fade != FADE_NONE)
	{// フェード処理中
		if (m_fade == FADE_OUT)
		{
			m_alfa -= 0.04f;

			if (m_alfa <= 0.0f)
			{
				// フェードイン処理に切り替え
				m_alfa = 0.0f;

				SetFade(FADE_IN);

				m_seasonNum++;
				m_seasonNum %= SEASON_MODE_MAX;
				m_seasons[BUFFER_FRONT]->GetPrefab()->GetModel()->SubsetArray->Material.Texture = m_Texture[m_seasonNum];

			}

			SetFadeOut_StartFlag(TRUE);

		}
		else if (m_fade == FADE_IN)
		{
			m_alfa += 0.04f;

			if (m_alfa >= 1.0f)
			{
				// フェード処理終了
				m_alfa = 1.0f;

				SetFade(FADE_NONE);

				SetFadeOut_EndFlag(TRUE);
			}

		}

		m_color.w = m_alfa;
		m_seasons[BUFFER_FRONT]->GetPrefab()->SetColor(m_color);

	}


}
