//=============================================================================
//
// チュートリアルの処理 [tutorial.h]
// Author : 柏村大地
//
//=============================================================================
#pragma once
#include "Scene.h"
#include "UIManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define STAGE_01_TEX_MAX			(3)				// テクスチャの数

class Tutorial : public Scene
{
private:
	BOOL m_isInit = FALSE;

public:
	Tutorial(God * god);
	~Tutorial();
	void Init();
	void Update();
	void Draw();
	void NextScene();
	void InitDate();

	void SetInit(BOOL data) { m_isInit = data; };
};

