//=============================================================================
//
// �V�[���̏��� [Scene.h]
// Author : ������n
//
//=============================================================================
#pragma once
#include "main.h"
#include "GodObject.h"

//*****************************************************************************
// �}�N����`
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

