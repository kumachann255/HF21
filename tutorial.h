//=============================================================================
//
// �`���[�g���A���̏��� [tutorial.h]
// Author : ������n
//
//=============================================================================
#pragma once
#include "Scene.h"
#include "UIManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define STAGE_01_TEX_MAX			(3)				// �e�N�X�`���̐�

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
};

