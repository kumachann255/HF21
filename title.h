//=============================================================================
//
// �^�C�g����ʏ��� [Title.h]
// Author : 
//
//=============================================================================
#pragma once
#include "Scene.h"
#include "UI.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEX_MAX					(3)				// �e�N�X�`���̐�


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
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);


