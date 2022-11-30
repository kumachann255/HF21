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

	int m_timeCnt = 0;		// 時間カウント
	int m_timeLimit = 0;	// リミット時間

protected:
	UITexData  *m_UITexData;

public:
	UIObject();
	UIObject(XMFLOAT3 pos, float width, float height ,int timeLimit)
		:m_pos(pos), m_fWidth(width), m_fHeight(height), m_timeLimit(timeLimit * 60)
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

	void SetPos(XMFLOAT3 pos) {  m_pos = pos; }
	void SetRot(float rot) {  m_rot = rot; }
	void SetWidth(float width) { m_fWidth = width; }
	void SetHeight(float height) { m_fHeight = height; }
	void SetTexNo(int texNo) { m_TexNo = texNo; }


	void Update(void);
	void Draw(void);


};