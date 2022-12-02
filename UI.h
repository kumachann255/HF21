//=============================================================================
//
// UI処理 [UI.h]
// Author : 
//
//=============================================================================
#pragma once
#include "main.h"


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
enum{
	texType_normal,
	texType_fade,
	texType_cutIn_right,
	texType_cutIn_left,
	texType_cutIn_up,
	texType_cutIn_under,
	texType_zoomIn,
	texType_zoomIn_rot,
};

#define UI_ACTION_TIME	(80)
#define UI_CUTIN_DISTANCE_X	(80.0f)
#define UI_CUTIN_DISTANCE_Y	(40.0f)
#define UI_ROT_SPEED	(0.2f)

class UITexData
{
private:
	ID3D11Buffer *m_VertexBuffer = nullptr;	// 頂点バッファ
	ID3D11ShaderResourceView	*m_Texture =  nullptr;	// テクスチャ情報
	char *m_TextureName = nullptr;

public:
	UITexData();
	UITexData(char *textureName);
	~UITexData();

	HRESULT Create(char *textureName);
	ID3D11Buffer **GetpVertexBuffer(void) { return &m_VertexBuffer; }
	ID3D11Buffer *GetVertexBuffer(void) { return m_VertexBuffer; }
	ID3D11ShaderResourceView **GetTexture(void) { return &m_Texture; }
	void SetTextureName(char *textureName) {m_TextureName = textureName;}
};


class UIObject
{
private:
	BOOL		m_isUse = FALSE;	
	XMFLOAT3	m_pos   = { 0.0f,0.0f,0.0f };
	float		m_rot     = 0.0f;		// 回転角度
	float		m_fWidth  = 50.0f;		// 幅
	float		m_fHeight = 50.0f;		// 高さ
	int			m_TexNo   = 0;			// テクスチャ番号
	XMFLOAT4	m_color  = { 1.0f,1.0f,1.0f,1.0f };

	float		m_fWidthMax = 50.0f;		// 幅
	float		m_fHeightMax = 50.0f;		// 高さ

	int m_timeCnt = 0;		// 時間カウント
	int m_timeLimit = 0;	// リミット時間

	int m_texType = 0;
	float m_vec = 1.0f;

	int m_actionTime = UI_ACTION_TIME;
	int m_count = 0;


protected:
	UITexData  *m_UITexData;

public:
	UIObject();
	UIObject(XMFLOAT3 pos, float width, float height ,int timeLimit)
		:m_pos(pos), m_fWidth(width), m_fWidthMax(width), m_fHeight(height), m_fHeightMax(height), m_timeLimit(timeLimit * 60)
	{
		m_UITexData = new UITexData;
		m_isUse = TRUE;
	}


	virtual ~UIObject();

	XMFLOAT3 GetPos(void) { return m_pos; }
	float GetRot(void) { return m_rot; }
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	int GetTimeCnt(void) { return m_timeCnt/60; }	//秒数を返す
	UITexData *GetUITexData(void) { return m_UITexData; }
	BOOL GetUse(void) { return m_isUse; }

	void SetPos(XMFLOAT3 pos) {  m_pos = pos; }
	void SetRot(float rot) {  m_rot = rot; }
	void SetWidth(float width) { m_fWidth = m_fWidthMax = width; }
	void SetHeight(float height) { m_fHeight = m_fHeightMax = height; }
	void SetTexNo(int texNo) { m_TexNo = texNo; }
	void SetTime(int time) { m_timeLimit = time; }
	void SetTexType(int type) { m_texType = type; }
	void SetUse(BOOL data) { m_isUse = data; }

	void ResetTex(void) { m_timeCnt = 0; 
	m_fHeight = m_fHeightMax;
	m_fWidth = m_fWidthMax;
	m_color.w = 1.0f;
	m_rot = 0.0f;
	}
	void Update(void);
	void Draw(void);

	void UpdateNomal(void);
	void UpdateFade(void);
	void UpdateCutIn(void);
	void UpdateZoomIn(void);
};