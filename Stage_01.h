//=============================================================================
//
// �X�e�[�W�P�̏��� [Stage_01.h]
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

class Stage_01 : public Scene
{
private:
	UIManager m_UIManager;

public:
	Stage_01(God * god);
	~Stage_01();
	void Init();
	void Update();
	void Draw();
	void NextScene();
};

