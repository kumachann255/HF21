//=============================================================================
//
// �X�e�[�W�P�̏��� [Stage_01.h]
// Author : ������n
//
//=============================================================================
#pragma once
#include "Scene.h"
#include "UIManager.h"
#include "AnimationManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ENDING_TEX_MAX			(3)				// �e�N�X�`���̐�

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

