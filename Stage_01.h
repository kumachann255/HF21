//=============================================================================
//
// ステージ１の処理 [Stage_01.h]
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

class Stage_01 : public Scene
{
private:
	BOOL m_isInit = FALSE;

public:
	Stage_01(God * god);
	~Stage_01();
	void Init();
	void Update();
	void Draw();
	void NextScene();
	void InitDate();

	void SetInit(BOOL data) { m_isInit = data; };
};

