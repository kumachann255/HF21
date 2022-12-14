//=============================================================================
//
// シーンの処理 [Scene.h]
// Author : 柏村大地
//
//=============================================================================
#pragma once
#include "main.h"
#include "GodObject.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

class Scene : public GodObject
{

public:
	Scene(God * god);
	virtual~Scene();
	virtual void Init();
	virtual void Update();
	virtual void Draw();
	virtual void NextScene();
	virtual void SetInit(BOOL data);
};

