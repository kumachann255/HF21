//=============================================================================
//
// タイトル画面処理 [Title.h]
// Author : 
//
//=============================================================================
#pragma once
#include "Scene.h"
#include "UI.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEX_MAX					(3)				// テクスチャの数


class TitleUI
{
private:
	UIObject *m_UIObject[TEX_MAX];


public:
	TitleUI();
	~TitleUI();

	UIObject *GetUIObject(void){ return m_UIObject[0]; }
};



class Title : public Scene
{
private:
	TitleUI *m_TitleUI;

public:
	Title(God * god);
	~Title();
	void Init();
	void Update();
	void Draw();
	void NextScene();

};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);


