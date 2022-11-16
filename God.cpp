//=============================================================================
//
// �_�̏��� [God.cpp]
// Author : ������n
//
//=============================================================================
#include "God.h"
#include "debugproc.h"
#include "input.h"
#include "Title.h"
#include "Stage_01.h"
#include "SkyManager.h"
#include "Roller.h"
#include "QuestBoardManager.h"
#include "Slot.h"
#include "FlyingCrowManager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

// ���݂̃V�[��ID
static SCENE_ID g_curSceneId;

//=============================================================================
// �R���X�g���N�^�[
//=============================================================================
God::God()
{
	// ���߂̃V�[��ID��ݒ�
	g_curSceneId = STAGE_01ID;

	//�@�Ǘ�����V�[����o�ꂳ����
	Scenes[TITLE_ID] = new Title(this);
	Scenes[STAGE_01ID] = new Stage_01(this);


	// ���݂��̏������L�ł���悤�ɃC���X�^���X��
	m_pSkymanager = new SkyManager(this);
	m_pRoller = new Roller(this);
	m_pQuestBoardManager = new QuestBoardManager(this);
	m_pSlot = new Slot(this);
	m_pFlyingCrowManager = new FlyingCrowManager(this);

}

//=============================================================================
// �f�X�g���N�^�[
//=============================================================================
God::~God()
{
	for (int i = 0; i < SCENE_MAX; i++) {
		delete Scenes[i];
	}

	delete m_pSkymanager;
	delete m_pRoller;
	delete m_pQuestBoardManager;
	delete m_pSlot;
	delete m_pFlyingCrowManager;
}

//=============================================================================
// �X�V����
//=============================================================================
void God::Update(void)
{
	// ���݂̃V�[�����X�V
	Scenes[g_curSceneId]->Update();

	//if (GetKeyboardTrigger(DIK_F1))
	//{
	//	Scenes[m_curSceneId]->NextScene();
	//}

}

//=============================================================================
// �`�揈��
//=============================================================================
void God::Draw(void)
{
	// ���݂̃V�[�����X�V
	Scenes[g_curSceneId]->Draw();

}


//=============================================================================
// �V�[���؂�ւ�����
//=============================================================================
void God::ChangeScene(SCENE_ID sceneId)
{
	g_curSceneId = sceneId;
	Scenes[g_curSceneId]->Init();
}


//*****************************************************************************
// �V�[���̃Q�b�^�[
//*****************************************************************************
SCENE_ID GetSceneID(void)
{
	return g_curSceneId;
}
//*****************************************************************************
// �V�[���̃Z�b�^�[
//*****************************************************************************
void SetSceneID(SCENE_ID nextSceneId)
{
	g_curSceneId = nextSceneId;
}
