#pragma once
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "camera.h"
#include "sprite.h"
#include "UI.h"
#include "GodObject.h"

#define CALENDAR_TEXTURE_MAX		(2)		// テクスチャの数
#define CALENDAR_TEXTURE_WIDTH		(120.0f)	// キャラサイズ
#define CALENDAR_TEXTURE_HEIGHT		(60.0f)	// 

#define CALENDAR_WAKU_TEXTURE_WIDTH	 (CALENDAR_TEXTURE_WIDTH + 30.0f)	// キャラサイズ
#define CALENDAR_WAKU_TEXTURE_HEIGHT (CALENDAR_TEXTURE_HEIGHT + 30.0f)	// 

#define MAX_CALENDAR_NUM			(12.0f)
#define SOEED_CALENDAR				(0.0003f)
#define DIStANCE_CALENDAR			(1.0f / MAX_CALENDAR_NUM)

enum {
	month_4,
	month_5,
	month_6,
	month_7,
	month_8,
	month_9,
	month_10,
	month_11,
	month_12,
	month_1,
	month_2,
	month_3,
	month_max,
};


class CalendarNum :public GodObject
{
private:
	ID3D11Buffer				*m_VertexBuffer = nullptr;		// 頂点情報
	ID3D11ShaderResourceView	*m_Texture[CALENDAR_TEXTURE_MAX] = { NULL };	// テクスチャ情報

	char *m_TexturName[CALENDAR_TEXTURE_MAX] = {
		"data/TEXTURE/tex_calendar_waku.png",
		"data/TEXTURE/tex_calendar_num.png",
	};

	float m_w[2], m_h[2];				// 幅と高さ
	XMFLOAT3 m_Pos[2];				// ポリゴンの座標

	int m_month = month_4;
	float m_uvStartY = 0.0f;
	float m_uvEndY = 1.0f / MAX_CALENDAR_NUM;
	float m_count = 0.0f;
	BOOL m_swichfFlag = FALSE;

public:
	CalendarNum(God *god);
	~CalendarNum();

	void Update();
	void Draw();

	void AddMonth(void) { m_month = (m_month + 1) % month_max; }
	int GetMonth(void) { return m_month; }
	BOOL GetSwichfFlag(void) { return m_swichfFlag; }
	float GetCount(void) { return m_count; }

};