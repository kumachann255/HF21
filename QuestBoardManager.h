//=============================================================================
//
// �N�G�X�g�{�[�h�}�l�[�W���[���� [QuestBoardManager.h]
// Author : ������n
//
//=============================================================================
#pragma once
#include "QuestBoard.h"
#include "GodObject.h"
#include <vector>

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODEL_NAME			"model_quest_questboard.obj"	// �ǂݍ��ރ��f����

//*****************************************************************************
// �N���X��`
//*****************************************************************************

// �N���X���i�[����z��̒�`�iSTL�j
typedef std::vector<QuestBoard*> QuestBoardArray;

class QuestBoardManager :public GodObject
{
private:
	QuestBoardArray BoardArray;
	XMFLOAT3 m_StartPos{ 0.0f ,0.0f,0.0f };

	//std::vector<QuestBoard>BoardArray;

public:
	QuestBoardManager(God *god);
	~QuestBoardManager();

	// �����o�֐�
	void Update(void);
	void Draw(void);

};

