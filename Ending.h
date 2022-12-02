//=============================================================================
//
// ステージ１の処理 [Stage_01.h]
// Author : 柏村大地
//
//=============================================================================
#pragma once
#include "Scene.h"
#include "UIManager.h"
#include "AnimationManager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define ENDING_TEX_MAX			(3)				// テクスチャの数

class Ending : public Scene
{
private:
	UIManager m_UIManager;

public:
	Ending(God * god);
	~Ending();
	void Init();
	void Update();
	void Draw();
	void NextScene();
};

